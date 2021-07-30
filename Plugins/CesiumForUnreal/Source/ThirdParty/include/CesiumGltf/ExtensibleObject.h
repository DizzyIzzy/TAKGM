#pragma once

#include "CesiumGltf/Library.h"
#include "CesiumUtility/JsonValue.h"
#include <any>
#include <unordered_map>
#include <utility>
#include <vector>

namespace CesiumGltf {
/**
 * @brief The base class for objects in a glTF that have extensions and extras.
 */
struct CESIUMGLTF_API ExtensibleObject {
  /**
   * @brief Gets an extension given its static type.
   *
   * @tparam T The type of the extension.
   * @return A pointer to the extension, or nullptr if the extension is not
   * attached to this object.
   */
  template <typename T> const T* getExtension() const noexcept {
    auto it = this->extensions.find(T::ExtensionName);
    if (it == this->extensions.end()) {
      return nullptr;
    }

    return std::any_cast<T>(&it->second);
  }

  /** @copydoc ExtensibleObject::getExtension */
  template <typename T> T* getExtension() noexcept {
    return const_cast<T*>(std::as_const(*this).getExtension<T>());
  }

  /**
   * @brief Gets a generic extension with the given name as a
   * {@link CesiumUtility::JsonValue}.
   *
   * If the extension exists but has a static type, this method will retur
   * nullptr. Use {@link getExtension} to retrieve a statically-typed extension.
   *
   * @param extensionName The name of the extension.
   * @return The generic extension, or nullptr if the generic extension doesn't
   * exist.
   */
  const CesiumUtility::JsonValue*
  getGenericExtension(const std::string& extensionName) const noexcept;

  /** @copydoc ExtensibleObject::getGenericExtension */
  CesiumUtility::JsonValue*
  getGenericExtension(const std::string& extensionName) noexcept;

  /**
   * @brief The extensions attached to this object.
   *
   * Use {@link getExtension} to get the extension with a particular static
   * type. Use {@link getGenericExtension} to get unknown extensions as a
   * generic {@link CesiumUtility::JsonValue}.
   */
  std::unordered_map<std::string, std::any> extensions;

  /**
   * @brief Application-specific data.
   *
   * **Implementation Note:** Although extras may have any type, it is common
   * for applications to store and access custom data as key/value pairs. As
   * best practice, extras should be an Object rather than a primitive value for
   * best portability.
   */
  CesiumUtility::JsonValue::Object extras;
};
} // namespace CesiumGltf
