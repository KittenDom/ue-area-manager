// TwoCoins subajat1 Copyright 2026


#include "TC_AreaManagementUtil.h"

#include "WorldPartition/WorldPartitionRuntimeCell.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"

EWorldPartitionRuntimeCellState UTC_AreaManagementUtil::GetWPCellState(const EDataLayerRuntimeState dataLayerState)
{
	switch (dataLayerState)
	{
		case EDataLayerRuntimeState::Unloaded:
			return EWorldPartitionRuntimeCellState::Unloaded;

		case EDataLayerRuntimeState::Loaded:
			return EWorldPartitionRuntimeCellState::Loaded;

		case EDataLayerRuntimeState::Activated:
			return EWorldPartitionRuntimeCellState::Activated;
	}
	return EWorldPartitionRuntimeCellState::Unloaded;
}
