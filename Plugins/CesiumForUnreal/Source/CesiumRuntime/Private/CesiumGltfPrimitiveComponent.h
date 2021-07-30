// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include <glm/mat4x4.hpp>
#include "CesiumGltfPrimitiveComponent.generated.h"

UCLASS()
class CESIUMRUNTIME_API UCesiumGltfPrimitiveComponent
    : public UStaticMeshComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UCesiumGltfPrimitiveComponent();
  virtual ~UCesiumGltfPrimitiveComponent();

  /**
   * The double-precision transformation matrix for this glTF node.
   */
  glm::dmat4x4 HighPrecisionNodeTransform;

  /**
   * Updates this component's transform from a new double-precision
   * transformation from the Cesium world to the Unreal Engine world, as well as
   * the current HighPrecisionNodeTransform.
   *
   * @param CesiumToUnrealTransform The new transformation.
   */
  void UpdateTransformFromCesium(const glm::dmat4& CesiumToUnrealTransform);
};
