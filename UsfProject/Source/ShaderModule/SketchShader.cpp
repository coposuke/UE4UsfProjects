#include "SketchShader.h"
#include <Runtime/RenderCore/Public/ShaderCompilerCore.h>


FSketchShaderVS::FSketchShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

void FSketchShaderVS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.CompilerFlags.Add(CFLAG_StandardOptimization);
}

FSketchShaderPS::FSketchShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

void FSketchShaderPS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.CompilerFlags.Add(CFLAG_StandardOptimization);
}

////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SHADER_TYPE(, FSketchShaderVS, TEXT("/Project/SketchShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FSketchShaderPS, TEXT("/Project/SketchShader.usf"), TEXT("MainPS"), SF_Pixel);
