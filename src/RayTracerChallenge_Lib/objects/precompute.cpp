#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/precompute.hpp>
#include <algorithm>
#include <optional>
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
