#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SketchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class USFPROJECT_API USketchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USketchComponent();

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Sketch)
	class UTextureRenderTarget2D* renderTexture;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ExecuteInRenderThread(FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* OutputRenderTargetResource);
	void DrawIndexedPrimitiveUP(
		FRHICommandList& RHICmdList,
		uint32 PrimitiveType,
		uint32 MinVertexIndex,
		uint32 NumVertices,
		uint32 NumPrimitives,
		const void* IndexData,
		uint32 IndexDataStride,
		const void* VertexData,
		uint32 VertexDataStride );
};
