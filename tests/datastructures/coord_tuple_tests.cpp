#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "coord_tuple.hpp"
#include "helpers.h"

SCENARIO("A tuple with w=1.0 is a point.") {
  GIVEN("a = tuple(4.3, -4.2, 3.1, 1)") {
    CoordTuple a{4.3, -4.2, 3.1, 1};
    THEN("a.x = 4.3")
    AND_THEN("a.y = -4.2")
    AND_THEN("a.z = 3.1")
    AND_THEN("a.w = 1")
    AND_THEN("a is a point")
    AND_THEN("a is not a vector") {
      REQUIRE(areFloatsEqual(a.x, 4.3));
      REQUIRE(areFloatsEqual(a.y, -4.2));
      REQUIRE(areFloatsEqual(a.z, 3.1));
      REQUIRE(a.w == 1);
      REQUIRE(a.isPoint());
      REQUIRE(!a.isVector());
    }
  }
}

SCENARIO("A tuple with w=0 is a vector.") {
  GIVEN("a = tuple(4.3, -4.2, 3.1, 0)") {
    CoordTuple a{4.3, -4.2, 3.1, 0};
    THEN("a.x = 4.3")
    AND_THEN("a.y = -4.2")
    AND_THEN("a.z = 3.1")
    AND_THEN("a.w = 0")
    AND_THEN("a is not a point")
    AND_THEN("a is a vector") {
      REQUIRE(areFloatsEqual(a.x, 4.3));
      REQUIRE(areFloatsEqual(a.y, -4.2));
      REQUIRE(areFloatsEqual(a.z, 3.1));
      REQUIRE(a.w == 0);
      REQUIRE(!a.isPoint());
      REQUIRE(a.isVector());
    }
  }
}

SCENARIO("point() creates a tuple with w=1") {
  GIVEN("p = point(4, -4, 3)") {
    auto p = point(4, -4, 3);
    THEN("p = tuple(4, -4, 3, 1)") {
      auto expected = CoordTuple{4, -4, 3, 1};
      REQUIRE(p == expected);
    }
  }
}

SCENARIO("vector() creates a tuple with w=0") {
  GIVEN("v = vector(4, -4, 3)") {
    auto v = vector(4, -4, 3);
    THEN("v = tuple(4, -4, 3, 0)") {
      auto expected = CoordTuple{4, -4, 3, 0};
      REQUIRE(v == expected);
    }
  }
}

SCENARIO("Adding two tuples.") {
  GIVEN("a1 = tuple(3, -2, 5, 1)")
  AND_GIVEN("a2 = tuple(-2, 3, 1, 0)") {
    auto a1 = CoordTuple(3, -2, 5, 1);
    auto a2 = CoordTuple(-2, 3, 1, 0);
    THEN("a1 + a2 = tuple(1, 1, 6, 1)") {
      REQUIRE(a1 + a2 == CoordTuple(1, 1, 6, 1));
    }
  }
}

SCENARIO("Subtracting two points.") {
  GIVEN("p1 = point(3, 2, 1)")
  AND_GIVEN("p2 = point(5, 6, 7)") {
    auto p1 = point(3, 2, 1);
    auto p2 = point(5, 6, 7);
    THEN("p1 - p2 = vector(-2, -4, -6)") {
      auto res = p1 - p2;
      REQUIRE(res == vector(-2, -4, -6));
      REQUIRE(res.isVector());
    }
  }
}

SCENARIO("Subtracting a vector from a point.") {
  GIVEN("p = point(3, 2, 1)")
  AND_GIVEN("v = vector(5, 6, 7)") {
    auto p = point(3, 2, 1);
    auto v = vector(5, 6, 7);
    THEN("p - v = point(-2, -4, -6)") {
      auto res = p - v;
      REQUIRE(res == point(-2, -4, -6));
      REQUIRE(res.isPoint());
    }
  }
}

SCENARIO("Subtracting two vectors.") {
  GIVEN("v1 = vector(3, 2, 1)")
  AND_GIVEN("v2 = vector(5, 6, 7)") {
    auto v1 = vector(3, 2, 1);
    auto v2 = vector(5, 6, 7);
    THEN("v1 - v2 = vector(-2, -4, -6)") {
      auto res = v1 - v2;
      REQUIRE(res == vector(-2, -4, -6));
      REQUIRE(res.isVector());
    }
  }
}

SCENARIO("Subtracting a vector from a zero vector.") {
  GIVEN("v1 = vector(0, 0, 0)")
  AND_GIVEN("v2 = vector(1, -2, 3)") {
    auto v1 = vector(0, 0, 0);
    auto v2 = vector(1, -2, 3);
    THEN("v1 - v2 = vector(-1, 2, -3)") {
      auto res = v1 - v2;
      REQUIRE(res == vector(-1, 2, -3));
      REQUIRE(res.isVector());
    }
  }
}

SCENARIO("Negating a tuple.") {
  GIVEN("t = tuple(1, -2, 3, -4)") {
    auto t = CoordTuple{1, -2, 3, -4};
    THEN("-t = tuple(-1, 2, -3, 4)") {
      auto res = -t;
      REQUIRE(res == CoordTuple{-1, 2, -3, 4});
    }
  }
}

SCENARIO("Multiple a tuple by a scalar.") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = CoordTuple{1, -2, 3, -4};
    THEN("a * 3.5 = tuple(3.5, -7, 10.5, -14)") {
      REQUIRE(a * 3.5 == CoordTuple{3.5, -7, 10.5, -14});
    }
  }
}

SCENARIO("Multiple a tuple by a fraction.") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = CoordTuple{1, -2, 3, -4};
    THEN("a * 0.5 = tuple(0.5, -1, 1.5, -2)") {
      REQUIRE(a * 0.5 == CoordTuple{0.5, -1, 1.5, -2});
    }
  }
}

SCENARIO("Divide a tuple by a scalar.") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = CoordTuple{1, -2, 3, -4};
    THEN("a / 2 = tuple(0.5, -1, 1.5, -2)") {
      REQUIRE(a / 2 == CoordTuple{0.5, -1, 1.5, -2});
    }
  }
}

SCENARIO("Computing the magnitude of vector(1, 0, 0).") {
  GIVEN("v = vector(1, 0, 0)") {
    auto v = vector(1, 0, 0);
    THEN("magnitude(v) = 1") { REQUIRE(v.magnitude() == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0).") {
  GIVEN("v = vector(0, 1, 0)") {
    auto v = vector(0, 1, 0);
    THEN("magnitude(v) = 1") { REQUIRE(v.magnitude() == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1).") {
  GIVEN("v = vector(0, 0, 1)") {
    auto v = vector(0, 0, 1);
    THEN("magnitude(v) = 1") { REQUIRE(v.magnitude() == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3).") {
  GIVEN("v = vector(1, 2, 3)") {
    auto v = vector(1, 2, 3);
    THEN("magnitude(v) = sqrt(14)") {
      REQUIRE(areFloatsEqual(v.magnitude(), std::sqrt(14)));
    }
  }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3).") {
  GIVEN("v = vector(-1, -2, -3)") {
    auto v = vector(-1, -2, -3);
    THEN("magnitude(v) = sqrt(14)") {
      REQUIRE(areFloatsEqual(v.magnitude(), std::sqrt(14)));
    }
  }
}

SCENARIO("Normalizing a vector(4, 0, 0) give (1, 0, 0)") {
  GIVEN("v = vector(4, 0, 0)") {
    auto v = vector(4, 0, 0);
    THEN("normalize(v) = vector(1, 0, 0)") {
      REQUIRE(v.normalise() == vector(1, 0, 0));
    }
  }
}

SCENARIO("Normalizing a vector(1, 2, 3)") {
  GIVEN("v = vector(1, 2, 3)") {
    auto v = vector(1, 2, 3);
    THEN("normalize(v) ~= vector(0.267261, 0.534522, 0.801784)") {
      REQUIRE(v.normalise() == vector(0.267261, 0.534522, 0.801784));
    }
  }
}

SCENARIO("dot(a, b)") {
  GIVEN("a = vector(1, 2, 3)")
  AND_GIVEN("b = vector(2, 3, 4)") {
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);
    THEN("dot(a, b) = 20") { REQUIRE(a.dot(b) == 20); }
  }
}

SCENARIO("The cross product of two vectors.") {
  GIVEN("a = vector(1, 2, 3)")
  AND_GIVEN("b = vector(2, 3, 4)") {
    auto a = vector(1, 2, 3);
    auto b = vector(2, 3, 4);
    THEN("cross(a, b) == vector(-1, 2, -1)")
    AND_THEN("cross(b, a) == vector(1, -2, 1)") {
      REQUIRE(a.cross(b) == vector(-1, 2, -1));
      REQUIRE(b.cross(a) == vector(1, -2, 1));
    }
  }
}
