// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UsfProjectTarget : TargetRules
{
	public UsfProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "UsfProject" } );
		ExtraModuleNames.AddRange(new string[] { "ShaderModule" });
	}
}
