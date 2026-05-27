#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/precompute.hpp>
#include <algorithm>
#include <vector>

rtc::Precompute rtc::prepareComputation(const Intersection &intersection,
                                        const Ray &ray) {
  Precompute comp{};
  comp.t = intersection.t;
  comp.object = intersection.object;
  comp.point = ray.position(comp.t);
  comp.eyeVec = -ray.direction;
  comp.normalVec = comp.object->normalAt(comp.point);
  if (comp.normalVec.dot(comp.eyeVec) < 0) {
    comp.inside = true;
    comp.normalVec = -comp.normalVec;
  } else {
    comp.inside = false;
  }
  comp.overPoint = comp.point + comp.normalVec * EPSILON;
  comp.underPoint = comp.point - comp.normalVec * EPSILON;
  comp.reflectVec = ray.direction.reflect(comp.normalVec);
  return comp;
}

rtc::Precompute
rtc::prepareComputation(const Intersection &intersection, const Ray &ray,
                        const SortedIntersections &intersections) {
  Precompute comp = prepareComputation(intersection, ray);
  std::vector<const Object *> container{};

  for (const auto &i : intersections) {
    if (i == intersection) {
      comp.n1 = container.empty()
                    ? 1.0f
                    : container.back()->getMaterial().refractiveIndex;
    }

    if (auto it = std::ranges::find(container, i.object);
        it != container.end()) {
      container.erase(it);
    } else {
      container.push_back(i.object);
    }

    if (i == intersection) {
      comp.n2 = container.empty()
                    ? 1.0f
                    : container.back()->getMaterial().refractiveIndex;
      break;
    }
  }

  return comp;
}

float rtc::Precompute::schlick() const noexcept {
  // find the cosine of the angle between the eye and normal vector
  float cos = eyeVec.dot(normalVec);
  // check for total internal refraction
  if (n1 > n2) {
    const float n = n1 / n2;
    const float sin2t = (n * n) * (1.0f - cos * cos);
    if (sin2t > 1.0f) {
      return 1.0f;
    }

    // compute cosine of theta_t using trig. identity
    cos = std::sqrt(1.0f - sin2t);
  }

  const float r0 = std::pow((n1 - n2) / (n1 + n2), 2);
  return r0 + (1.0f - r0) * std::pow(1.0f - cos, 5);
}
