// TwoCoins subajat1 Copyright 2026

#pragma once

#include "TC_AreaManagementDelegates.h"
#include "UObject/Object.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"

#include "TC_DataLayerRequest.generated.h"

/**
 * 
 */
UCLASS()
class UTC_DataLayerRequest : public UObject
{
	GENERATED_BODY()

public:
	bool InitializeRequest(UDataLayerAsset* inDataLayer, const EDataLayerRuntimeState inState, const bool inIsRecursive, const FTC_DataLayerProcessingCompletedSignature& inCallback);
	void ImmediateInterruptRequest();

private:
	void DeinitializeRequest();

	// handler functions
	void OnStreamingCompleted();

public:
	UDataLayerAsset* GetDataLayer() const { return dataLayer; }
	EDataLayerRuntimeState GetState() const { return state; }

private:
	FTC_DataLayerProcessingCompletedSignature callback;

	FTimerHandle timerHandle;

	UPROPERTY()
	TObjectPtr<UDataLayerAsset> dataLayer = nullptr;

	UPROPERTY()
	EDataLayerRuntimeState state = EDataLayerRuntimeState::Unloaded;

	UPROPERTY()
	TArray<FWorldPartitionStreamingQuerySource> querySources;
};
