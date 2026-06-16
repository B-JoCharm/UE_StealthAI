#include "UE_StealthAIEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FUE_StealthAIEditorModule, UE_StealthAIEditor)

void FUE_StealthAIEditorModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("StealthAI Editor Module Loaded"));
}

void FUE_StealthAIEditorModule::ShutdownModule()
{
}