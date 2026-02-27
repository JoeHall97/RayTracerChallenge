#include <RayTracerChallenge/objects/test_shape.hpp>
#include <catch2/catch_test_macros.hpp>

SCENARIO("The default transformation") {
  GIVEN("s = testShape()") {
    const auto s = rtc::testShape();
    THEN("s.transform = identityMatrix()") {
      REQUIRE(s.getTransformationMatrix() == rtc::identity(4));
    }
  }
}

SCENARIO("Assigning a transformation") {
  GIVEN("s = testShape()") {
    auto s = rtc::testShape();
    WHEN("s.transform = scaling(2, 2, 2)") {
      s.setTransformationMatrix(rtc::scalingMatrix(2, 2, 2));
      THEN("s.transform = scaling(2, 2, 2)") {
        REQUIRE(s.getTransformationMatrix() == rtc::scalingMatrix(2, 2, 2));
      }
    }
  }
}

SCENARIO("The default material") {
  GIVEN("s = testShape()") {
    const auto s = rtc::testShape();
    THEN("s.material = defaultMaterial()") {
      REQUIRE(s.getMaterial() == rtc::defaultMaterial());
    }
  }
}

SCENARIO("Assigning a material") {
  GIVEN("s = testShape()")
  AND_GIVEN("m = defaultMaterial()")
  AND_GIVEN("m.ambient = 1") {
    auto s = rtc::testShape();
    auto m = rtc::defaultMaterial();
    m.ambient = 1;
    WHEN("s.material = m") {
      s.setMaterial(m);
      THEN("s.material = m") { REQUIRE(s.getMaterial() == m); }
    }
  }
}

SCENARIO("Intersecting a scaled shape with a ray") {
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s = testShape()") {
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    auto s = rtc::testShape();
    WHEN("s.transform = scaling(2, 2, 2)")
    AND_WHEN("xs = s.intersect(r)") {
      s.setTransformationMatrix(rtc::scalingMatrix(2, 2, 2));
      const auto xs = s.intersect(r);
      THEN("s.savedRay.origin = point(0, 0, -2.5)")
      AND_THEN("s.savedRay.direction = vector(0, 0, 0.5)") {
        CHECK(s.getSavedRay().origin == rtc::point(0, 0, -2.5));
        CHECK(s.getSavedRay().direction == rtc::vector(0, 0, 0.5));
      }
    }
  }
}

SCENARIO("Intersecting a translated shape with a ray") {
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1))")
  AND_GIVEN("s = testShape()") {
    const rtc::Ray r{rtc::point(0, 0, -5), rtc::vector(0, 0, 1)};
    auto s = rtc::testShape();
    WHEN("s.transform = translation(5, 0, 0)")
    AND_WHEN("xs = s.intersect(r)") {
      s.setTransformationMatrix(rtc::translationMatrix(5, 0, 0));
      const auto xs = s.intersect(r);
      THEN("s.savedRay.origin = point(-5, 0, -5)")
      AND_THEN("s.savedRay.direction = vector(0, 0, 1)") {
        CHECK(s.getSavedRay().origin == rtc::point(-5, 0, -5));
        CHECK(s.getSavedRay().direction == rtc::vector(0, 0, 1));
      }
    }
  }
}

SCENARIO("Computing the normal on a translated shape") {
  GIVEN("s = testShape()") {
    auto s = rtc::testShape();
    WHEN("s.transform = translation(0, 1, 0)") {
      s.setTransformationMatrix(rtc::translationMatrix(0, 1, 0));
      THEN("s.normalAt(point(0, 1.70711, -0.70711)) = vector(0, 0.70711, "
           "-0.70711)") {
        CHECK(s.normalAt(rtc::point(0, 1.70711f, -0.70711f)) ==
              rtc::vector(0, 0.70711f, -0.70711f));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed shape.") {
  GIVEN("s = testShape()")
  AND_GIVEN("m = scaling(1, 0.5, 1) * rotationZ(pi/5)") {
    auto s = rtc::testShape();
    const auto m = rtc::scalingMatrix(1, 0.5, 1) *
                   rtc::rotationMatrixZ(std::numbers::pi_v<float> / 5);
    WHEN("s.transform = m")
    AND_WHEN("n = s.normalAt(point(0, sqrt(2)/2, -sqrt(2)/2))") {
      s.setTransformationMatrix(m);
      const auto n =
          s.normalAt(rtc::point(0, static_cast<float>(std::sqrt(2)) / 2,
                                -static_cast<float>(std::sqrt(2)) / 2));
      THEN("n = vector(0, 0.97014, -0.24254)") {
        CHECK(n == rtc::vector(0, 0.97014f, -0.24254f));
      }
    }
  }
}