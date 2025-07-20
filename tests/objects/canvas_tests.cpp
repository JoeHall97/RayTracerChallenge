#include <RayTracerChallenge/datastructures/colour_tuple.hpp>
#include <RayTracerChallenge/objects/canvas.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <sstream>
#include <string>

using rtc::Canvas, rtc::ColourTuple;

SCENARIO("Creating a canvas.") {
    GIVEN("c = canvas(10, 20)") {
        const auto c = Canvas{10, 20};
        THEN("c.width = 10")
        AND_THEN("c.height = 20")
        AND_THEN("Every pixel in c is colour(0, 0)") {
            CHECK(c.width == 10);
            CHECK(c.height == 20);
            for (auto &row: c.canvas) {
                for (auto &column: row) {
                    REQUIRE(column == ColourTuple{0, 0, 0});
                }
            }
        }
    }
}

SCENARIO("Writing pixels to a canvas.") {
    GIVEN("c = canvas(10, 20)")
    AND_GIVEN("red = colour(1, 0, 0)") {
        auto c = Canvas{10, 20};
        const auto red = ColourTuple{1, 0, 0};
        WHEN("writePixel(c, 2, 4, red)") {
            c.writePixel(2, 4, red);
            THEN("canvas.at(2, 4) = red") {
                REQUIRE(c.canvas[4][2] == red);
            }
        }
    }
}

SCENARIO("Constructing a PPM header") {
    GIVEN("c = canvas(5, 3)") {
        const auto c = Canvas{5, 3};
        WHEN("ppm = c.toPPM()") {
            auto ppm = c.toPPM();
            THEN("lines 1-3 of the ppm are \"\"\"\nP3\n5 3\n255\n\"\"\"") {
                std::stringstream ss{ppm};
                std::string line;
                int count = 3;
                while (!ss.eof() && count-- > 0) {
                    std::getline(ss, line);
                    switch (count) {
                        case 2:
                            CHECK(line == "P3");
                            break;
                        case 1:
                            CHECK(line == "5 3");
                            break;
                        case 0:
                            REQUIRE(line == "255");
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

SCENARIO("Constructing the PPM pixel data.") {
    GIVEN("c = canvas(5, 3)")
    AND_GIVEN("c1 = colour(1.4, 0, 0)")
    AND_GIVEN("c2 = colour(0, 0.5, 0)")
    AND_GIVEN("c2 = colour(0, -0.5, 1)") {
        auto c = Canvas{5, 3};
        const auto c1 = ColourTuple{1.4f, 0, 0};
        const auto c2 = ColourTuple{0, 0.5f, 0};
        const auto c3 = ColourTuple{-0.5f, 0, 1};

        WHEN("write_pixel(c, 0, 0, c1)")
        AND_WHEN("write_pixel(c, 2, 1, c2)")
        AND_WHEN("write_pixel(c, 4, 2, c3)")
        AND_WHEN("ppm = c.toPPM()") {
            CHECK(c.writePixel(0, 0, c1));
            CHECK(c.writePixel(2, 1, c2));
            CHECK(c.writePixel(4, 2, c3));
            const auto ppm = c.toPPM();

            THEN("lines 4-6 are the expected values") {
                std::stringstream ss{ppm};
                std::string line;
                std::vector<std::string> expected{
                        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
                        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
                        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255",
                };
                // skip header
                int count = 3;
                while (!ss.eof() && count-- > 0) {
                    std::getline(ss, line);
                }

                size_t bodyLen = 0;
                while (!ss.eof() && bodyLen < expected.size()) {
                    std::getline(ss, line);
                    CHECK(line == expected[bodyLen++]);
                }
                REQUIRE(bodyLen == expected.size());
            }
        }
    }
}

SCENARIO("Splitting long lines in PPM files.") {
    GIVEN("c = canvas(10, 2)") {
        WHEN("every pixel of c is set of colour(1, 0.8, 0.6)")
        AND_WHEN("ppm = c.toPPM()") {
            auto c = Canvas{10, 2, ColourTuple{1, 0.8f, 0.6f}};
            auto ppm = c.toPPM();

            THEN("lines 4-7 are the expected values") {
                std::stringstream ss{ppm};
                std::string line;
                const std::vector<std::string> expected{
                        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 "
                        "204",
                        "153 255 204 153 255 204 153 255 204 153 255 204 153",
                        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 "
                        "204",
                        "153 255 204 153 255 204 153 255 204 153 255 204 153",
                };
                // skip header
                int count = 3;
                while (!ss.eof() && count-- > 0) {
                    std::getline(ss, line);
                }

                size_t bodyLen = 0;
                while (!ss.eof() && bodyLen < expected.size()) {
                    std::getline(ss, line);
                    CHECK(line == expected[bodyLen++]);
                }
                REQUIRE(bodyLen == expected.size());
            }
        }
    }
}

SCENARIO("PPM files are terminated by a newline character.") {
    GIVEN("c = canvas(5, 3)") {
        const auto c = Canvas{5, 3};
        WHEN("ppm = c.toPPM()") {
            const auto ppm = c.toPPM();
            THEN("ppm ends with a newline character") {
                REQUIRE(ppm.ends_with('\n'));
            }
        }
    }
}
