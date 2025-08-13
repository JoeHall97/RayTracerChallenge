#include <RayTracerChallenge/objects/precompute.hpp>

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
  return comp;
}
