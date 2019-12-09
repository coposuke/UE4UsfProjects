#include "SketchComponent.h"
#include "SketchShader.h"
#include "Classes/Engine/TextureRenderTarget2D.h"  
//#include "RHICommandList.h" // RHI module
#include "RHIResources.h"


USketchComponent::USketchComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USketchComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USketchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto This = this;
	auto RenderTargetResource = this->renderTexture->GameThread_GetRenderTargetResource();
	ENQUEUE_RENDER_COMMAND(FRaymarchingPostprocess)(
		[This, RenderTargetResource](FRHICommandListImmediate& RHICmdList)
		{
			This->ExecuteInRenderThread(RHICmdList, RenderTargetResource);
		}
	);
}

void USketchComponent::ExecuteInRenderThread(FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* OutputRenderTargetResource)
{
	check(IsInRenderingThread());
	
#if WANTS_DRAW_MESH_EVENTS
    FString EventName;
	this->renderTexture->GetFName().ToString(EventName);
    SCOPED_DRAW_EVENTF(RHICmdList, SceneCapture, TEXT("SketchShader %s"), *EventName);
#else
    SCOPED_DRAW_EVENT(RHICmdList, DrawUVDisplacementToRenderTarget_RenderThread);
#endif

	// SetRenderTarget
	FRHIRenderPassInfo rpInfo(OutputRenderTargetResource->GetRenderTargetTexture(), ERenderTargetActions::DontLoad_DontStore);
	RHICmdList.BeginRenderPass(rpInfo, TEXT("Sketch"));

	// Shader setup
	auto shaderMap = GetGlobalShaderMap(ERHIFeatureLevel::SM5);
	TShaderMapRef<FSketchShaderVS> shaderVS(shaderMap);
	TShaderMapRef<FSketchShaderPS> shaderPS(shaderMap);
	
    FSketchVertexDeclaration VertexDec;
    VertexDec.InitRHI();

	//Declare a pipeline state object that holds all the rendering state
	FGraphicsPipelineStateInitializer PSOInitializer;
    RHICmdList.ApplyCachedRenderTargets(PSOInitializer);
	PSOInitializer.PrimitiveType = PT_TriangleList;
    PSOInitializer.BoundShaderState.VertexDeclarationRHI = VertexDec.VertexDeclarationRHI;
	PSOInitializer.BoundShaderState.VertexShaderRHI = GETSAFERHISHADER_VERTEX(*shaderVS);
    PSOInitializer.BoundShaderState.PixelShaderRHI = GETSAFERHISHADER_PIXEL(*shaderPS);
	PSOInitializer.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
	PSOInitializer.BlendState = TStaticBlendState<>::GetRHI();
	PSOInitializer.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	SetGraphicsPipelineState(RHICmdList, PSOInitializer);

	static const FSketchVertex Vertices[4] = {
		{ FVector4(-1.0f,  1.0f, 0.0f, 1.0f), FVector2D(0.0f, 0.0f)},
		{ FVector4( 1.0f,  1.0f, 0.0f, 1.0f), FVector2D(1.0f, 0.0f)},
		{ FVector4(-1.0f, -1.0f, 0.0f, 1.0f), FVector2D(0.0f, 1.0f)},
		{ FVector4( 1.0f, -1.0f, 0.0f, 1.0f), FVector2D(1.0f, 1.0f)},
	};
	
	static const uint16 Indices[6] =
	{
		0, 1, 2,
		2, 1, 3
	};

	DrawIndexedPrimitiveUP(RHICmdList, PT_TriangleList, 0, ARRAY_COUNT(Vertices), 2, Indices, sizeof(Indices[0]), Vertices, sizeof(Vertices[0]));

    // Resolve render target.  
    RHICmdList.CopyToResolveTarget(  
        OutputRenderTargetResource->GetRenderTargetTexture(),  
        OutputRenderTargetResource->TextureRHI,
        FResolveParams());

	RHICmdList.EndRenderPass();
}

void USketchComponent::DrawIndexedPrimitiveUP(
	FRHICommandList& RHICmdList,
	uint32 PrimitiveType,
	uint32 MinVertexIndex,
	uint32 NumVertices,
	uint32 NumPrimitives,
	const void* IndexData,
	uint32 IndexDataStride,
	const void* VertexData,
	uint32 VertexDataStride )
{
	const uint32 NumIndices = GetVertexCountForPrimitiveCount( NumPrimitives, PrimitiveType );

	FRHIResourceCreateInfo CreateInfo;
	FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(VertexDataStride * NumVertices, BUF_Volatile, CreateInfo);
	void* VoidPtr = RHILockVertexBuffer(VertexBufferRHI, 0, VertexDataStride * NumVertices, RLM_WriteOnly);
	FPlatformMemory::Memcpy(VoidPtr, VertexData, VertexDataStride * NumVertices);
	RHIUnlockVertexBuffer(VertexBufferRHI);

	FIndexBufferRHIRef IndexBufferRHI = RHICreateIndexBuffer(IndexDataStride, IndexDataStride * NumIndices, BUF_Volatile, CreateInfo);
	void* VoidPtr2 = RHILockIndexBuffer(IndexBufferRHI, 0, IndexDataStride * NumIndices, RLM_WriteOnly);
	FPlatformMemory::Memcpy(VoidPtr2, IndexData, IndexDataStride * NumIndices);
	RHIUnlockIndexBuffer(IndexBufferRHI);

	RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
	RHICmdList.DrawIndexedPrimitive(IndexBufferRHI, MinVertexIndex, 0, NumVertices, 0, NumPrimitives, 1);

	IndexBufferRHI.SafeRelease();
	VertexBufferRHI.SafeRelease();
}