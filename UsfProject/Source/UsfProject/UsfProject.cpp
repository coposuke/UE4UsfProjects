// Fill out your copyright notice in the Description page of Project Settings.

#include "UsfProject.h"
#include "Modules/ModuleManager.h"

void FUsfProjectModule::StartupModule()
{
#if (ENGINE_MINOR_VERSION >= 21)    
    FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shader"));
    if(!AllShaderSourceDirectoryMappings().Contains("/Project"))
        AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
#endif
}

void FUsfProjectModule::PostLoadCallback()
{
}

void FUsfProjectModule::ShutdownModule()
{
}

IMPLEMENT_PRIMARY_GAME_MODULE( FUsfProjectModule, UsfProject, "UsfProject" );
