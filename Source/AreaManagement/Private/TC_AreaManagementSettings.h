// TwoCoins subajat1 Copyright 2026


#pragma once

#include "Engine/DeveloperSettings.h"

#include "TC_AreaManagementSettings.generated.h"

/**
 * 
 */
UCLASS(config=TwoCoinsAreaManagementSettings, defaultconfig, meta=(DisplayName="TC Area Management Settings"))
class AREAMANAGEMENT_API UTC_AreaManagementSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UTC_AreaManagementSettings();

public:
	UPROPERTY(Config, EditDefaultsOnly, Category="Area - Data Layer")
	float AreaDataLayerUpdateRequestIntervalSecs = .1f;
};
