#include <RayTracerChallenge/objects/intersection.hpp>
#include <RayTracerChallenge/objects/ray.hpp>
#include <RayTracerChallenge/objects/sphere.hpp>
#include <catch2/catch_test_macros.hpp>
#include <numbers>

using rtc::Ray, rtc::point, rtc::vector, rtc::sphere;

SCENARIO("Intersecting a scaled sphere with a ray.") {
  GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1 ))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, -5), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("s.transform = scaling(2, 2, 2)")
    AND_WHEN("xs = r.intersect(s)") {
      s.transform = rtc::scalingMatrix(2, 2, 2);
      const auto xs = s.intersect(r);
      THEN("xs.count = 2") { CHECK(xs.size() == 2); }
    }
  }
}

SCENARIO("Intersecting a translated sphere with a ray.") {
  GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1 ))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, -5), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("s.transform = translation(5, 0, 0)")
    AND_WHEN("xs = r.intersect(s)") {
      s.transform = rtc::translationMatrix(5, 0, 0);
      const auto xs = s.intersect(r);
      THEN("xs.count = 0") { CHECK(xs.empty()); }
    }
  }
}

SCENARIO("A Ray intersects a sphere at two points.") {
  GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, -5), vector(0, 0, 1)};
    const auto s = sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = 4.0")
      AND_THEN("xs[1] = 6.0") {
        CHECK(xs.size() == 2);
        CHECK(xs.begin()->t == 4.0);
        CHECK((--xs.end())->t == 6.0);
      }
    }
  }
}

SCENARIO("A Ray intersects a sphere at a tangent.") {
  GIVEN("r = Ray(point(0, 1, -5), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 1, -5), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 1")
      AND_THEN("xs[0] = 5.0") {
        CHECK(xs.size() == 1);
        CHECK(xs.begin()->t == 5.0);
      }
    }
  }
}

SCENARIO("A Ray that misses a sphere.") {
  GIVEN("r = Ray(point(0, 2, -5), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 2, -5), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 0") { CHECK(xs.empty()); }
    }
  }
}

SCENARIO("A Ray originates inside a sphere.") {
  GIVEN("r = Ray(point(0, 0, 0), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, 0), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = -1.0")
      AND_THEN("xs[1] = 1.0") {
        CHECK(xs.size() == 2);
        CHECK(rtc::areFloatsEqual(xs.begin()->t, -1.0));
        CHECK((--xs.end())->t == 1.0);
      }
    }
  }
}

SCENARIO("A sphere is behind a Ray.") {
  GIVEN("r = Ray(point(0, 0, 5), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, 5), vector(0, 0, 1)};
    auto s = sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 2")
      AND_THEN("xs[0] = -6.0")
      AND_THEN("xs[1] = -4.0") {
        CHECK(xs.size() == 2);
        CHECK(rtc::areFloatsEqual(xs.begin()->t, -6.0));
        CHECK(rtc::areFloatsEqual((--xs.end())->t, -4.0));
      }
    }
  }
}

SCENARIO("Intersect sets the object on the intersection.") {
  GIVEN("r = Ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s = sphere()") {
    const Ray r{point(0, 0, -5), vector(0, 0, 1)};
    auto s = rtc::sphere();
    WHEN("xs = r.intersect(s)") {
      const auto xs = s.intersect(r);
      THEN("xs.count = 2")
      AND_THEN("xs[0].object = s")
      AND_THEN("xs[1].object = s") {
        CHECK(xs.size() == 2);
        const auto s1 = dynamic_cast<const rtc::Sphere *>(xs.begin()->object);
        CHECK(*s1 == s);
        const auto s2 = dynamic_cast<const rtc::Sphere *>((--xs.end())->object);
        CHECK(*s2 == s);
      }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the x axis.") {
  GIVEN("s = sphere()") {
    const auto s = sphere();
    WHEN("n = s.normalAt(point(1, 0, 0))") {
      const auto n = s.normalAt(point(1, 0, 0));
      THEN("n = vector(1, 0, 0)") { CHECK(n == vector(1, 0, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the y axis.") {
  GIVEN("s = sphere()") {
    const auto s = sphere();
    WHEN("n = s.normalAt(point(0, 1, 0))") {
      const auto n = s.normalAt(point(0, 1, 0));
      THEN("n = vector(0, 1, 0)") { CHECK(n == vector(0, 1, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the z axis.") {
  GIVEN("s = sphere()") {
    const auto s = sphere();
    WHEN("n = s.normalAt(point(0, 0, 1))") {
      const auto n = s.normalAt(point(0, 0, 1));
      THEN("n = vector(0, 0, 1)") { CHECK(n == vector(0, 0, 1)); }
    }
  }
}

SCENARIO("The normal on a sphere at a non-axial point.") {
  GIVEN("s = sphere()") {
    const auto s = sphere();
    WHEN("n = s.normalAt(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))") {
      const float x = static_cast<float>(std::sqrt(3)) / 3.0f;
      const auto n = s.normalAt(point(x, x, x));
      THEN("n = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)") {
        CHECK(n == vector(x, x, x));
      }
    }
  }
}

SCENARIO("The normal is a normalised vector.") {
  GIVEN("s = sphere()") {
    const auto s = sphere();
    WHEN("n = s.normalAt(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))") {
      const float x = static_cast<float>(std::sqrt(3)) / 3.0f;
      const auto n = s.normalAt(point(x, x, x));
      THEN("n = n.normalise()") { CHECK(n == n.normalise()); }
    }
  }
}

SCENARIO("Computing the normal on a translated sphere.") {
  GIVEN("s = sphere()")
  AND_GIVEN("s.transform = translate(point(0, 1, 0))") {
    auto s = sphere();
    s.transform = rtc::translationMatrix(0, 1, 0);
    WHEN("n = s.normalAt(point(0, 1.70711, -0.70711))") {
      const auto n = s.normalAt(point(0, 1.70711f, -0.70711f));
      THEN("n = vector(0, 0.70711, -0.70711)") {
        CHECK(n == vector(0, 0.70711f, -0.70711f));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed sphere.") {
  GIVEN("s = sphere()")
  AND_GIVEN("m = scaling(1, 0.5, 1) * rotationZ(pi/5)")
  AND_GIVEN("s.transform = m") {
    auto s = sphere();
    const auto m = rtc::scalingMatrix(1, 0.5, 1) *
                   rtc::rotationMatrixZ(std::numbers::pi_v<float> / 5.0f);
    s.transform = m;
    WHEN("n = s.normalAt(point(0, sqrt(2)/2, -sqrt(2)/2))") {
      const float y = static_cast<float>(std::sqrt(2)) / 2.0f;
      const float z = static_cast<float>(-std::sqrt(2)) / 2.0f;
      const auto n = s.normalAt(point(0, y, z));
      THEN("n = vector(0, 0.97014, -0.24254)") {
        CHECK(n == vector(0, 0.97014f, -0.24254f));
      }
    }
  }
}
