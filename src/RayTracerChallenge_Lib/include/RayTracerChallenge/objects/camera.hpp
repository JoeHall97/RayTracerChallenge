#pragma once

#include <RayTracerChallenge/datastructures/matrix.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/world.hpp>

namespace rtc {
class Camera {
public:
  Camera(const Matrix &transform, const std::size_t horizontalSize,
         const std::size_t verticalSize, const float fieldOfView)
      : transform{transform}, hSize{horizontalSize}, vSize{verticalSize},
        fieldOfView{fieldOfView} {
    calculatePixelSize();
  }

  Camera(const std::size_t horizontalSize, const std::size_t verticalSize,
         const float fieldOfView)
      : transform{identity(4)}, hSize{horizontalSize}, vSize{verticalSize},
        fieldOfView{fieldOfView} {
    calculatePixelSize();
  }

  [[nodiscard]] Matrix getTransform() const noexcept { return transform; }
  [[nodiscard]] std::size_t getHSize() const noexcept { return hSize; }
  [[nodiscard]] std::size_t getVSize() const noexcept { return vSize; }
  [[nodiscard]] float getFieldOfView() const noexcept { return fieldOfView; }
  [[nodiscard]] float getPixelSize() const noexcept { return pixelSize; }
  [[nodiscard]] float getHalfWidth() const noexcept { return halfWidth; }
  [[nodiscard]] float getHalfHeight() const noexcept { return halfHeight; }

  void setTransform(const Matrix &m) noexcept { transform = m; }

  [[nodiscard]] Ray getRayForPixel(std::size_t x, std::size_t y) const noexcept;
  [[nodiscard]] Canvas render(const World &world) const noexcept;

private:
  Matrix transform;
  std::size_t hSize, vSize;
  float fieldOfView, pixelSize, halfWidth, halfHeight;

  void calculatePixelSize() noexcept {
    const auto halfView = std::tan(fieldOfView / 2);
    const auto aspect = static_cast<float>(hSize) / static_cast<float>(vSize);
    if (aspect >= 1) {
      halfWidth = halfView;
      halfHeight = halfView / aspect;
    } else {
      halfWidth = halfView * aspect;
      halfHeight = halfView;
    }
    pixelSize = (halfWidth * 2) / static_cast<float>(hSize);
  }
};
} // namespace rtc
