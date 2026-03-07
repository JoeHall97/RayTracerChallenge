#include <RayTracerChallenge/objects/material.hpp>
#include <RayTracerChallenge/objects/patterns.hpp>

rtc::Colour rtc::Material::lighting(const Object *object, const Light &light,
                                    const Vec4 &position, const Vec4 &eyeVec,
                                    const Vec4 &normalVec,
                                    const bool inShadow) const noexcept {
  Colour materialColour = colour;
  if (pattern != nullptr) {
    materialColour = pattern->colourAtObject(object, position);
  }
  // combines the light's intensity/colour with the surface colour
  const auto effectiveColour = materialColour * light.intensity;
  // find the direction of the light source
  const auto lightVec = (light.position - position).normalise();
  // compute the ambient contribution
  const auto ambientColour = effectiveColour * ambient;
  if (inShadow) {
    return ambientColour;
  }
  // lightDotNormal represents the cosine of the angle between the light
  // vector and the normal vector
  const auto lightDotNormal = lightVec.dot(normalVec);
  Colour diffuseColour{0.0f, 0.0f, 0.0f};
  Colour specularColour{0.0f, 0.0f, 0.0f};
  if (lightDotNormal > 0.0f) {
    // diffuse contribution
    diffuseColour = effectiveColour * diffuse * lightDotNormal;
    // reflectDotEye represents the cosine of the angle between the reflection
    // vector and then eye vector
    const auto reflectVec = (-lightVec).reflect(normalVec);
    if (const auto reflectDotEye = reflectVec.dot(eyeVec);
        reflectDotEye > 0.0f) {
      const auto factor = std::pow(reflectDotEye, shininess);
      specularColour = light.intensity * specular * factor;
    }
  }
  return ambientColour + diffuseColour + specularColour;
}
