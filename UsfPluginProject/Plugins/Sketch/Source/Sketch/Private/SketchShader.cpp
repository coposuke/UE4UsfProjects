#include "SketchShader.h"


FSketchShaderVS::FSketchShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

void FSketchShaderVS::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.CompilerFlags.Add(CFLAG_StandardOptimization);
}

bool FSketchShaderVS::Serialize(FArchive& Ar)
{
    return FGlobalShader::Serialize(Ar);
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

bool FSketchShaderPS::Serialize(FArchive& Ar)
{
    return FGlobalShader::Serialize(Ar);
}

////////////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SHADER_TYPE(, FSketchShaderVS, TEXT("/Plugins/Sketch/Shaders/SketchShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FSketchShaderPS, TEXT("/Plugins/Sketch/Shaders/SketchShader.usf"), TEXT("MainPS"), SF_Pixel);
