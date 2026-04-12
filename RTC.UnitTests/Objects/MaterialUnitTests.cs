using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class MaterialUnitTests
{
    public static IEnumerable<object[]> LightingTestData =>
    [
        // Lighting with the eye between the light and the surface
        [
            Vec4.Vector(0, 0, -1), Vec4.Vector(0, 0, -1), new PointLight(Colour.White, Vec4.Point(0, 0, -10)),
            new Colour(1.9d, 1.9d, 1.9d)
        ],
        // Lighting with the eye between light and surface, eye offset 45 degrees
        [
            Vec4.Vector(0, Math.Sqrt(2) / 2, -Math.Sqrt(2) / 2), Vec4.Vector(0, 0, -1),
            new PointLight(Colour.White, Vec4.Point(0, 0, -10)), new Colour(1.0d, 1.0d, 1.0d)
        ],
        // Light with the eye opposite surface, light offset 45 degrees
        [
            Vec4.Vector(0, 0, -1), Vec4.Vector(0, 0, -1), new PointLight(Colour.White, Vec4.Point(0, 10, -10)),
            new Colour(0.7364d, 0.7364d, 0.7364d)
        ],
        // Light with the eye in the path of the reflection vector
        [
            Vec4.Vector(0, -Math.Sqrt(2) / 2, -Math.Sqrt(2) / 2), Vec4.Vector(0, 0, -1),
            new PointLight(Colour.White, Vec4.Point(0, 10, -10)), new Colour(1.6364d, 1.6364d, 1.6364d)
        ],
        // Light with the light behind the surface
        [
            Vec4.Vector(0, 0, -1), Vec4.Vector(0, 0, -1), new PointLight(Colour.White, Vec4.Point(0, 0, 10)),
            new Colour(0.1d, 0.1d, 0.1d)
        ]
    ];


    [Theory]
    [MemberData(nameof(LightingTestData))]
    public void TestMaterialLighting(Vec4 eyeVec, Vec4 normal, PointLight light, Colour expected)
    {
        var m = new Material();
        var position = Vec4.Point(0, 0, 0);
        var shape = new Sphere();
        m.Lighting(shape, light, position, eyeVec, normal, false).ShouldBe(expected);
    }

    [Fact]
    public void TestMaterialLightingWithShadow()
    {
        var m = new Material();
        var position = Vec4.Point(0, 0, 0);
        var eyeVec = Vec4.Vector(0, 0, -1);
        var normal = Vec4.Vector(0, 0, -1);
        var light = new PointLight(Colour.White, Vec4.Point(0, 0, -10));
        var shape = new Sphere();
        m.Lighting(shape, light, position, eyeVec, normal, true).ShouldBe(new Colour(0.1d, 0.1d, 0.1d));
    }

    [Fact]
    public void TestMaterialLightingWithPattern()
    {
        var m = new Material(new StripePattern(Colour.White, Colour.Black))
        {
            Ambient = 1,
            Diffuse = 0,
            Specular = 0
        };
        var shape = new Sphere();
        var eyeVec = Vec4.Vector(0, 0, -1);
        var normal = Vec4.Vector(0, 0, -1);
        var light = new PointLight(Colour.White, Vec4.Point(0, 0, -10));

        m.Lighting(shape, light, Vec4.Point(0.9d, 0, 0), eyeVec, normal, false).ShouldBe(Colour.White);
        m.Lighting(shape, light, Vec4.Point(1.1d, 0, 0), eyeVec, normal, false).ShouldBe(Colour.Black);
    }
}