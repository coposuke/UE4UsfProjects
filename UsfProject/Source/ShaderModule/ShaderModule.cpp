// Fill out your copyright notice in the Description page of Project Settings.

#include "ShaderModule.h"
#include "Modules/ModuleManager.h"

void FShaderModule::StartupModule()
{
#if (ENGINE_MINOR_VERSION >= 21 || ENGINE_MAJOR_VERSION >= 5)    
    FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shader"));
    if(!AllShaderSourceDirectoryMappings().Contains("/Project"))
        AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
#endif
}

void FShaderModule::ShutdownModule()
{
}

IMPLEMENT_GAME_MODULE( FShaderModule, ShaderModule );
