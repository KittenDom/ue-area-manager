// TwoCoins subajat1 Copyright 2026

#pragma once

DECLARE_DELEGATE(FTC_AreaLoadedSignature);
DECLARE_DELEGATE(FTC_AreaUnloadedSignature);
DECLARE_DELEGATE_OneParam(FTC_StreamSourceProcessingCompletedSignature, const bool bIsInterrupted);
DECLARE_DELEGATE_OneParam(FTC_DataLayerProcessingCompletedSignature, const bool bIsInterrupted);
