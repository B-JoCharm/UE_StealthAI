#pragma once

#include "Modules/ModuleManager.h"

class FUE_StealthAIEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};