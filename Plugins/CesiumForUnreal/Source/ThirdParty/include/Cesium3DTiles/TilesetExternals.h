#pragma once

#include "Cesium3DTiles/Library.h"
#include "Cesium3DTiles/spdlog-cesium.h"
#include <memory>

namespace CesiumAsync {
class IAssetAccessor;
class ITaskProcessor;
} // namespace CesiumAsync

namespace Cesium3DTiles {
class CreditSystem;
class IPrepareRendererResources;

/**
 * @brief External interfaces used by a {@link Tileset}.
 *
 * Not supposed to be used by clients.
 */
class CESIUM3DTILES_API TilesetExternals final {
public:
  /**
   * @brief An external {@link CesiumAsync::IAssetAccessor}.
   */
  std::shared_ptr<CesiumAsync::IAssetAccessor> pAssetAccessor;

  /**
   * @brief An external {@link IPrepareRendererResources}.
   */
  std::shared_ptr<IPrepareRendererResources> pPrepareRendererResources;

  /**
   * @brief The async system to use to do work in threads.
   *
   * The tileset will automatically call
   * {@link CesiumAsync::AsyncSystem::dispatchMainThreadTasks} from
   * {@link Tileset::updateView}.
   */
  CesiumAsync::AsyncSystem asyncSystem;

  /**
   * @brief An external {@link CreditSystem} that can be used to manage credit
   * strings and track which which credits to show and remove from the screen
   * each frame.
   */
  std::shared_ptr<CreditSystem> pCreditSystem;

  /**
   * @brief A spdlog logger that will receive log messages.
   *
   * If not specified, defaults to `spdlog::default_logger()`.
   */
  std::shared_ptr<spdlog::logger> pLogger = spdlog::default_logger();
};

} // namespace Cesium3DTiles
