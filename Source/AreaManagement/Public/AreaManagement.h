// TwoCoins subajat1 Copyright 2026

#pragma once

#include "Modules/ModuleManager.h"

class FAreaManagementModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
