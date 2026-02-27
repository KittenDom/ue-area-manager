// TwoCoins subajat1 Copyright 2026

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "TC_AreaManagementUtil.generated.h"

enum class EDataLayerRuntimeState : uint8;
enum class EWorldPartitionRuntimeCellState : uint8;

/**
 * 
 */
UCLASS()
class AREAMANAGEMENT_API UTC_AreaManagementUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @param dataLayerState 
	 * @return 'Unloaded' as default
	 */
	static EWorldPartitionRuntimeCellState GetWPCellState(const EDataLayerRuntimeState dataLayerState);
};
