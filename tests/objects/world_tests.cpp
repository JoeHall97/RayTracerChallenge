#include "RayTracerChallenge/objects/plane.hpp"

#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <RayTracerChallenge/objects/world.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("Intersect a world with a ray.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    WHEN("xs = w.intersect(r)") {
      const auto xs = w.intersections(r);
      THEN("xs.count = 4")
      AND_THEN("xs[0].t = 4")
      AND_THEN("xs[1].t = 4.5")
      AND_THEN("xs[2].t = 5.5")
      AND_THEN("xs[3].t = 6") {
        REQUIRE(xs.size() == 4);
        auto it = xs.begin();
        CHECK(it->t == 4);
        ++it;
        CHECK(it->t == 4.5);
        ++it;
        CHECK(it->t == 5.5);
        ++it;
        CHECK(it->t == 6);
      }
    }
  }
}

SCENARIO("Shading an intersection.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0.38066, 0.47583, 0.2855)") {
        CHECK(c == rtc::Colour{0.38066f, 0.47583f, 0.2855f});
      }
    }
  }
}

SCENARIO("Shading an intersection from the side.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("w.light = pointLight(point(0, 0.25, 0), colour(1, 1, 1))")
  AND_GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))") {
    auto w = rtc::defaultWorld();
    w.light = rtc::Light{rtc::Colour{1, 1, 1}, rtc::point(0, 0.25f, 0)};
    const rtc::Ray r{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0.90498, 0.90498, 0.90498)") {
        CHECK(c == rtc::Colour{0.90498f, 0.90498f, 0.90498f});
      }
    }
  }
}

SCENARIO("The colour when a ray misses.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, -5), vector(0, 1, 0))") {
    const auto w = rtc::defaultWorld();
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 1, 0)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = colour(0, 0, 0)") { CHECK(c == rtc::Colour{0, 0, 0}); }
    }
  }
}

SCENARIO("The colour with an intersection behind the ray.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("outer = the first object in w")
  AND_GIVEN("outer.material.ambient = 1")
  AND_GIVEN("inner = the second object in w")
  AND_GIVEN("inner.material.ambient = 1")
  AND_GIVEN("r = ray(point(0, 0, 0.75), vector(0, 0, -1))") {
    const auto w = rtc::defaultWorld();
    auto obj1Material = w.objects[0]->getMaterial();
    auto obj2Material = w.objects[1]->getMaterial();
    obj1Material.ambient = 1;
    obj2Material.ambient = 1;
    w.objects[0]->setMaterial(obj1Material);
    w.objects[1]->setMaterial(obj2Material);
    const rtc::Ray r{rtc::point(0, 0, 0.75), rtc::vector(0, 0, -1)};
    WHEN("c = w.colourAt(r)") {
      const auto c = w.colourAt(r);
      THEN("c = inner.material.colour") {
        CHECK(c == w.objects[1]->getMaterial().colour);
      }
    }
  }
}

SCENARIO(
    "There is no shadow when nothing is collinear with a light and point.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("p = point(0, 10, 0)") {
    const auto w = rtc::defaultWorld();
    const auto p = rtc::point(0, 10, 0);
    THEN("w.isShadowed(p) = false") { REQUIRE(!w.isShadowed(p)); }
  }
}

SCENARIO("There is a shadow when an object is between a point and the light.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("p = point(10, -10, 10)") {
    const auto w = rtc::defaultWorld();
    const auto p = rtc::point(10, -10, 10);
    THEN("w.isShadowed(p) = true") { REQUIRE(w.isShadowed(p)); }
  }
}

SCENARIO("There is no shadow when an object is behind the light.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("p = point(-20, 20, -20)") {
    const auto w = rtc::defaultWorld();
    const auto p = rtc::point(-20, 20, -20);
    THEN("w.isShadowed(p) = false") { REQUIRE(!w.isShadowed(p)); }
  }
}

SCENARIO("There is no shadow when an object is behind the point.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("p = point(-2, 2, -2)") {
    const auto w = rtc::defaultWorld();
    const auto p = rtc::point(-2, 2, -2);
    THEN("w.isShadowed(p) = false") { REQUIRE(!w.isShadowed(p)); }
  }
}

SCENARIO("shadeHit() is given an intersection with a shadow.") {
  GIVEN("w = world()")
  AND_GIVEN("w.light = light(point(0, 0, -10), colour(1, 1, 1))")
  AND_GIVEN("s1 = sphere()")
  AND_GIVEN("s1 is added to w")
  AND_GIVEN("s2 = sphere()")
  AND_GIVEN("s2.transform = translation(0, 0, 10)")
  AND_GIVEN("s2 is added to w")
  AND_GIVEN("r = ray(point(0, 0, 5), vector(0, 0, 1))")
  AND_GIVEN("i = intersection(4, s2)") {
    auto w = rtc::World();
    w.light = rtc::Light{rtc::Colour{1, 1, 1}, rtc::point(0, 0, -10)};
    const auto s1 = rtc::sphere();
    w.objects.push_back(std::make_unique<rtc::Sphere>(s1));
    auto s2 = rtc::sphere();
    s2.setTransformationMatrix(rtc::translationMatrix(0, 0, 10));
    w.objects.push_back(std::make_unique<rtc::Sphere>(s2));
    const rtc::Ray r{rtc::point(0, 0, 5), rtc::vector(0, 0, 1)};
    const rtc::Intersection i{4, &s2};
    WHEN("comps = prepareComputations(i, r)")
    AND_WHEN("c = shadeHit(w, comps)") {
      const auto comps = rtc::prepareComputation(i, r);
      const auto c = w.shadeHit(comps);
      THEN("c = colour(0.1, 0.1, 0.1)") {
        REQUIRE(c == rtc::Colour{0.1f, 0.1f, 0.1f});
      }
    }
  }
}

SCENARIO("The hit should offset the point.") {
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("shape = sphere()")
  AND_GIVEN("shape.transform = translation(0, 0, 1)")
  AND_GIVEN("i = intersection(5, shape)") {
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    auto shape = rtc::sphere();
    shape.setTransformationMatrix(rtc::translationMatrix(0, 0, 1));
    const rtc::Intersection i{5, &shape};
    WHEN("comps = prepareComputations(i, r)") {
      const auto comps = rtc::prepareComputation(i, r);
      THEN("comps.overPoint.z < -EPSILON/2")
      AND_THEN("comps.overPoint.z <= comps.point.z") {
        REQUIRE(comps.overPoint.z < -rtc::EPSILON / 2);
        REQUIRE(comps.overPoint.z <= comps.point.z);
      }
    }
  }
}

SCENARIO("The reflected colour for a non-reflective material.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1))")
  AND_GIVEN("shape = w.objects[1]")
  AND_GIVEN("shape.material.ambient = 1")
  AND_GIVEN("i = intersection(1, shape)") {
    const auto w = rtc::defaultWorld();
    const auto r = rtc::Ray{rtc::point(0, 0, 0), rtc::vector(0, 0, 1)};
    const auto shape = w.objects[1].get();
    const auto i = rtc::Intersection{1, shape};
    WHEN("comps = prepareComputations(i, r)")
    AND_WHEN("c = reflect(comps)") {
      const auto comps = rtc::prepareComputation(i, r);
      const auto c = w.reflectedColour(comps, 1);
      THEN("c = colour(0, 0, 0)") { CHECK(c == rtc::Colour{0, 0, 0}); }
    }
  }
}

SCENARIO("The reflected colour for a reflective material.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("shape = plane()")
  AND_GIVEN("shape.material.reflective = 0.5")
  AND_GIVEN("shape.transform = translation(0,-1,0)")
  AND_GIVEN("shape is added to w")
  AND_GIVEN("r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))")
  AND_GIVEN("i = intersection(sqrt(2), shape)") {
    auto w = rtc::defaultWorld();
    auto shape = rtc::plane();
    auto shapeMaterial = shape.getMaterial();
    shapeMaterial.reflective = 0.5;
    shape.setMaterial(shapeMaterial);
    shape.setTransformationMatrix(rtc::translationMatrix(0, -1, 0));
    w.objects.emplace_back(std::make_unique<rtc::Plane>(shape));
    const auto r =
        rtc::Ray{rtc::point(0, 0, -3),
                 rtc::vector(0, -std::sqrtf(2) / 2, std::sqrtf(2) / 2)};
    const auto i = rtc::Intersection{std::sqrtf(2), &shape};
    WHEN("comps = prepareComputations(i, r)")
    AND_WHEN("c = reflect(comps)") {
      const auto comps = rtc::prepareComputation(i, r);
      const auto c = w.reflectedColour(comps, 1);
      THEN("c = colour(0.19032, 0.2379, 0.14274)") {
        CHECK(c == rtc::Colour(0.19032, 0.2379, 0.14274));
      }
    }
  }
}

SCENARIO("shadeHit() with a reflective material.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("shape = plane()")
  AND_GIVEN("shape.material.reflective = 0.5")
  AND_GIVEN("shape.transform = translation(0,-1,0)")
  AND_GIVEN("shape is added to w")
  AND_GIVEN("r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))")
  AND_GIVEN("i = intersection(sqrt(2), shape)") {
    auto w = rtc::defaultWorld();
    auto shape = rtc::plane();
    auto shapeMaterial = shape.getMaterial();
    shapeMaterial.reflective = 0.5;
    shape.setMaterial(shapeMaterial);
    shape.setTransformationMatrix(rtc::translationMatrix(0, -1, 0));
    w.objects.emplace_back(std::make_unique<rtc::Plane>(shape));
    const auto r =
        rtc::Ray{rtc::point(0, 0, -3),
                 rtc::vector(0, -std::sqrtf(2) / 2, std::sqrtf(2) / 2)};
    const auto i = rtc::Intersection{std::sqrtf(2), &shape};
    WHEN("comps = prepareComputations(i, r)")
    AND_WHEN("c = shadeHit(w, comps)") {
      const auto comps = rtc::prepareComputation(i, r);
      const auto c = w.shadeHitWithReflections(comps, 1);
      THEN("c = colour(0.87677, 0.92436, 0.82918)") {
        CHECK(c == rtc::Colour(0.87677f, 0.92436f, 0.82918f));
      }
    }
  }
}

SCENARIO("colourAt() with mutually reflective surfaces.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("w.light = pointLight(point(0,0,0), colour(1,1,1))")
  AND_GIVEN("lower = plane()")
  AND_GIVEN("lower.material.reflective = 1")
  AND_GIVEN("lower.transform = translation(0,-1,0)")
  AND_GIVEN("lower is added to w")
  AND_GIVEN("upper = plane()")
  AND_GIVEN("upper.material.reflective = 1")
  AND_GIVEN("upper.transform = translation(0,1,0)")
  AND_GIVEN("upper is added to w")
  AND_GIVEN("r = ray(point(0,0,0), vector(0,1,0))") {
    auto w = rtc::defaultWorld();
    auto lower = rtc::plane();
    auto lowerMaterial = lower.getMaterial();
    lowerMaterial.reflective = 1;
    lower.setMaterial(lowerMaterial);
    lower.setTransformationMatrix(rtc::translationMatrix(0, -1, 0));
    w.objects.emplace_back(std::make_unique<rtc::Plane>(lower));
    auto upper = rtc::plane();
    auto upperMaterial = upper.getMaterial();
    upperMaterial.reflective = 1;
    upper.setMaterial(upperMaterial);
    upper.setTransformationMatrix(rtc::translationMatrix(0, 1, 0));
    w.objects.emplace_back(std::make_unique<rtc::Plane>(upper));
    const auto r = rtc::Ray{rtc::point(0, 0, 0), rtc::vector(0, 1, 0)};
    THEN("w.colourAt(r) should terminate.") {
      REQUIRE_NOTHROW(w.colourAtWithReflections(r, 2));
    }
  }
}

SCENARIO("The reflected colour at the maximum recursion depth.") {
  GIVEN("w = defaultWorld()")
  AND_GIVEN("w.light = pointLight(point(0,0,0), colour(1,1,1))")
  AND_GIVEN("shape = plane()")
  AND_GIVEN("shape.material.reflective = 0.5")
  AND_GIVEN("shape.transform = translation(0,-1,0)")
  AND_GIVEN("shape is added to w")
  AND_GIVEN("r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2))")
  AND_GIVEN("i = intersection(sqrt(2), shape)") {
    auto w = rtc::defaultWorld();
    auto shape = rtc::plane();
    auto shapeMaterial = shape.getMaterial();
    shapeMaterial.reflective = 0.5;
    shape.setMaterial(shapeMaterial);
    shape.setTransformationMatrix(rtc::translationMatrix(0, -1, 0));
    w.objects.emplace_back(std::make_unique<rtc::Plane>(shape));
    const auto r =
        rtc::Ray{rtc::point(0, 0, -3),
                 rtc::vector(0, -std::sqrtf(2) / 2, std::sqrtf(2) / 2)};
    const auto i = rtc::Intersection{std::sqrtf(2), &shape};
    WHEN("comps = prepareComputations(i, r)")
    AND_WHEN("c = reflectedColour(w, comps, 0)") {
      const auto comps = rtc::prepareComputation(i, r);
      const auto c = w.reflectedColour(comps, 0);
      THEN("c = colour(0,0,0)") { CHECK(c == rtc::Colour(0, 0, 0)); }
    }
  }
}