// TwoCoins subajat1 Copyright 2026

#pragma once

#include "TC_AreaManagementDelegates.h"
#include "Subsystems/WorldSubsystem.h"

#include "TC_AreaManagementSystem.generated.h"

enum class EDataLayerRuntimeState : uint8;

/**
 * 
 */
UCLASS()
class AREAMANAGEMENT_API UTC_AreaManagementSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool DoesSupportWorldType(const EWorldType::Type worldType) const override;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTC_BPOnDataLayerStateUpdatedSignature, const UDataLayerAsset*, dataLayerAsset, const EDataLayerRuntimeState, runtimeState);

	UPROPERTY(BlueprintAssignable)
	FTC_BPOnDataLayerStateUpdatedSignature OnDataLayerStateUpdated;

public:
	UFUNCTION(BlueprintCallable)
	bool UpdateDataLayerRuntimeState(UDataLayerAsset* dataLayerAsset, const EDataLayerRuntimeState runtimeState, const bool bIsRecursive = false);
	bool SetDataLayerRuntimeState(UDataLayerAsset* dataLayerAsset, const EDataLayerRuntimeState runtimeState, FTC_DataLayerProcessingCompletedSignature callback = nullptr, const bool bIsRecursive = false);

private:
	int32 GetTicketID();

private:
	TArray<TWeakObjectPtr<class UTC_DataLayerRequest>> _dataLayerRequests;

	UPROPERTY()
	int32 ticketIDCounter = 0;
};
