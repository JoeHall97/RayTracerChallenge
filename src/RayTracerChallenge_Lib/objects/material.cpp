#include <RayTracerChallenge/objects/material.h>

rtc::ColourTuple
rtc::Material::lighting(const Light &light, const CoordTuple &position,
                        const CoordTuple &eyeVec,
                        const CoordTuple &normalVec) const noexcept {
  // combines the light's intensity/colour with the surface colour
  const auto effectiveColour = colour * light.intensity;
  // find the direction of the light source
  const auto lightVec = (light.position - position).normalise();
  // compute the ambient contribution
  const auto ambientColour = effectiveColour * ambient;
  // lightDotNormal represents the cosine of the angle between the light
  // vector and the normal vector
  const auto lightDotNormal = lightVec.dot(normalVec);
  ColourTuple diffuseColour{0.0f, 0.0f, 0.0f};
  ColourTuple specularColour{0.0f, 0.0f, 0.0f};
  if (lightDotNormal > 0.0f) {
    // diffuse contribution
    diffuseColour = effectiveColour * diffuse * lightDotNormal;
    // reflectDotEye represents the cosine of the angle between the reflection
    // vector and then eye vector
    const auto reflectVec = (-lightVec).reflect(normalVec);
    const auto reflectDotEye = reflectVec.dot(eyeVec);
    if (reflectDotEye > 0.0f) {
      const auto factor = std::pow(reflectDotEye, shininess);
      specularColour = light.intensity * specular * factor;
    }
  }
  return ambientColour + diffuseColour + specularColour;
}
