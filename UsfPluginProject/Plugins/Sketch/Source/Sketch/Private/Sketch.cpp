// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Sketch.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FSketchModule"

void FSketchModule::StartupModule()
{
#if (ENGINE_MINOR_VERSION >= 21 || ENGINE_MAJOR_VERSION >= 5)
    FString PluginDirectory = IPluginManager::Get().FindPlugin(TEXT("Sketch"))->GetBaseDir();
    if(!AllShaderSourceDirectoryMappings().Contains("/Plugins/Sketch"))
        AddShaderSourceDirectoryMapping("/Plugins/Sketch", PluginDirectory);
#endif
}

void FSketchModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSketchModule, Sketch)