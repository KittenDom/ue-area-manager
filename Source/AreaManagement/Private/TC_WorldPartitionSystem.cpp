// TwoCoins subajat1 Copyright 2026

#include "TC_WorldPartitionSystem.h"

bool UTC_WorldPartitionSystem::DoesSupportWorldType(const EWorldType::Type worldType) const
{
	return worldType == EWorldType::Game || worldType == EWorldType::PIE;
}
