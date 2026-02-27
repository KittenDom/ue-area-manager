// TwoCoins subajat1 Copyright 2026


#include "TC_AreaManagementSystem.h"

#include "TC_AreaManagementLog.h"
#include "TC_DataLayerRequest.h"
#include "WorldPartition/DataLayer/DataLayerAsset.h"

bool UTC_AreaManagementSystem::DoesSupportWorldType(const EWorldType::Type worldType) const
{
	return worldType == EWorldType::Game || worldType == EWorldType::PIE;
}

bool UTC_AreaManagementSystem::UpdateDataLayerRuntimeState(UDataLayerAsset* dataLayerAsset, const EDataLayerRuntimeState runtimeState, const bool bIsRecursive)
{
	return SetDataLayerRuntimeState(dataLayerAsset, runtimeState, FTC_DataLayerProcessingCompletedSignature::CreateLambda([this, dataLayerAsset, runtimeState](const bool bInterrupted)
	{
		if (bInterrupted)
		{

#if !UE_BUILD_SHIPPING
			UE_LOG(LogTwoCoins_AreaManagement, Warning, TEXT("Data Layer %s was interrupted during state updating to %s! | %hs"),
			       dataLayerAsset ? *dataLayerAsset->GetName() : TEXT("null"),
			       *UEnum::GetDisplayValueAsText(runtimeState).ToString(),
			       __FUNCTION__);
#endif

			return;
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTwoCoins_AreaManagement, Log, TEXT("Data Layer %s was updated successfully to state: %s | %hs"),
		       dataLayerAsset ? *dataLayerAsset->GetName() : TEXT("null"),
		       *UEnum::GetDisplayValueAsText(runtimeState).ToString(),
		       __FUNCTION__);
#endif

		OnDataLayerStateUpdated.Broadcast(dataLayerAsset, runtimeState);
	}), bIsRecursive);
}

bool UTC_AreaManagementSystem::SetDataLayerRuntimeState(UDataLayerAsset* dataLayerAsset, const EDataLayerRuntimeState runtimeState, FTC_DataLayerProcessingCompletedSignature callback, const bool bIsRecursive)
{
	if (!dataLayerAsset)
	{
		return false;
	}

	TArray<UTC_DataLayerRequest*> interruptedRequests;
	_dataLayerRequests.RemoveAll([dataLayerAsset, runtimeState, &interruptedRequests](const TWeakObjectPtr<UTC_DataLayerRequest> request)
	{
		if (!request.IsValid())
		{
			return true;
		}
		if (request.Get()->HasAnyFlags(RF_BeginDestroyed))
		{
			return true;
		}

		if (request.Get()->GetDataLayer() == dataLayerAsset && request.Get()->GetState() != runtimeState)
		{
			interruptedRequests.Emplace(request.Get());
			return true;
		}
		return false;
	});

	for (UTC_DataLayerRequest* request : interruptedRequests)
	{
		if (request != nullptr)
		{
			request->ImmediateInterruptRequest();
		}
	}

	if (UTC_DataLayerRequest* dataLayerRequest = NewObject<UTC_DataLayerRequest>(this))
	{
		if (dataLayerRequest->InitializeRequest(dataLayerAsset, runtimeState, bIsRecursive, callback))
		{
			_dataLayerRequests.Emplace(dataLayerRequest);
			return true;
		}
	}

	return false;
}

int32 UTC_AreaManagementSystem::GetTicketID()
{
	if (ticketIDCounter == MAX_int32)
	{
		ticketIDCounter = 0;
	}
	++ticketIDCounter;

	return ticketIDCounter;
}
