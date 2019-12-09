// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FUsfProjectModule: public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
	virtual void PostLoadCallback() override;
	virtual bool IsGameModule() const override { return true; }
};

