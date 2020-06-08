// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FShaderModule: public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
    // static inline FShaderModule& Get() 
    // { 
    //     return FModuleManager::LoadModuleChecked< FShaderModule >( "FShaderModule" ); 
    // } 

    // static inline bool IsAvailable() 
    // { 
    //     return FModuleManager::Get().IsModuleLoaded( "FShaderModule" ); 
    // } 
};

