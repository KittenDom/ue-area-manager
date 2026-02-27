// TwoCoins subajat1 Copyright 2026

#include "TC_DataLayerRequest.h"

#include "TC_AreaManagementSettings.h"
#include "TC_AreaManagementUtil.h"
#include "WorldPartition/WorldPartitionSubsystem.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"

bool UTC_DataLayerRequest::InitializeRequest(UDataLayerAsset* inDataLayer, const EDataLayerRuntimeState inState, const bool inIsRecursive, const FTC_DataLayerProcessingCompletedSignature& inCallback)
{
	if (!GetWorld())
	{
		DeinitializeRequest();
		return false;
	}

	UDataLayerManager* dataLayerManager = GetWorld()->GetDataLayerManager();
	if (!dataLayerManager)
	{
		DeinitializeRequest();
		return false;
	}

	const UDataLayerInstance* dataLayerInstance = dataLayerManager->GetDataLayerInstanceFromAsset(inDataLayer);
	if (!dataLayerInstance)
	{
		DeinitializeRequest();
		return false;
	}

	FWorldPartitionStreamingQuerySource querySource;
	querySource.bDataLayersOnly = true;
	querySource.bSpatialQuery = false;
	querySource.DataLayers.Add(dataLayerInstance->GetDataLayerFName());
	this->querySources = {querySource};
	this->dataLayer = inDataLayer;
	this->state = inState;
	this->callback = inCallback;

	dataLayerManager->SetDataLayerRuntimeState(inDataLayer, inState, inIsRecursive);

	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		FTimerDelegate::CreateUObject(this, &UTC_DataLayerRequest::OnStreamingCompleted),
		GetDefault<UTC_AreaManagementSettings>()->AreaDataLayerUpdateRequestIntervalSecs,
		true);

	return true;
}

void UTC_DataLayerRequest::ImmediateInterruptRequest()
{
	DeinitializeRequest();
}

void UTC_DataLayerRequest::DeinitializeRequest()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
	}

	if (!HasAnyFlags(RF_BeginDestroyed))
	{
		ConditionalBeginDestroy();
	}

	this->callback.Unbind();
}

void UTC_DataLayerRequest::OnStreamingCompleted()
{
	if (!GetWorld())
	{
		DeinitializeRequest();
		return;
	}

	const UWorldPartitionSubsystem* worldPartitionSystem = GetWorld()->GetSubsystem<UWorldPartitionSubsystem>();
	if (!worldPartitionSystem)
	{
		DeinitializeRequest();
		return;
	}

	if (worldPartitionSystem->IsStreamingCompleted(UTC_AreaManagementUtil::GetWPCellState(this->state), this->querySources, true))
	{
		this->callback.ExecuteIfBound(false);
		DeinitializeRequest();
	}
}
