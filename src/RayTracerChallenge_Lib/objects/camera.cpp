#include <RayTracerChallenge/objects/camera.hpp>

rtc::Ray rtc::Camera::getRayForPixel(const std::size_t x,
                                     const std::size_t y) const noexcept {
  const auto xOffset = (static_cast<float>(x) + 0.5f) * pixelSize;
  const auto yOffset = (static_cast<float>(y) + 0.5f) * pixelSize;
  const auto worldX = halfWidth - xOffset;
  const auto worldY = halfHeight - yOffset;
  const auto pixel = transform.inverse() * point(worldX, worldY, -1);
  const auto origin = transform.inverse() * point(0, 0, 0);
  const auto direction = (pixel - origin).normalise();
  return Ray{origin, direction};
}

rtc::Canvas rtc::Camera::render(const World &world) const noexcept {
  Canvas image{vSize, hSize};

  for (std::size_t y = 0; y < hSize; y++) {
    for (std::size_t x = 0; x < vSize; x++) {
      const auto ray = getRayForPixel(x, y);
      const auto colour = world.colourAt(ray);
      image.writePixel(x, y, colour);
    }
  }

  return image;
}