// TwoCoins subajat1 Copyright 2026

#pragma once

#include "Subsystems/WorldSubsystem.h"

#include "TC_WorldPartitionSystem.generated.h"

/**
 * 
 */
UCLASS()
class AREAMANAGEMENT_API UTC_WorldPartitionSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool DoesSupportWorldType(const EWorldType::Type worldType) const override;
};
