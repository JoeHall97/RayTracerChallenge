using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives;
using Shouldly;

namespace RTC.UnitTests.Primitives;

public class PrecomputeUnitTests
{
    public static IEnumerable<object[]> RefractiveIndicesTestData =>
    [
        [0, 1.0d, 1.5d],
        [1, 1.5d, 2.0d],
        [2, 2.0d, 2.5d],
        [3, 2.5d, 2.5d],
        [4, 2.5d, 1.5d],
        [5, 1.5d, 1.0d]
    ];

    [Fact]
    public void TestPrecomputeConstructionWithOutsideIntersection()
    {
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var shape = new Sphere();
        var i = new Intersection(shape, 4);

        var comps = new Precompute(i, r);
        comps.T.ShouldBe(i.T);
        comps.Shape.ShouldBe(shape);
        comps.Point.ShouldBe(Vec4.Point(0, 0, -1));
        comps.EyeVec.ShouldBe(Vec4.Vector(0, 0, -1));
        comps.NormalVec.ShouldBe(Vec4.Vector(0, 0, -1));
        comps.Inside.ShouldBeFalse();
    }

    [Fact]
    public void TestPrecomputeConstructionWithInsideIntersection()
    {
        var r = new Ray(Vec4.Point(0, 0, 0), Vec4.Vector(0, 0, 1));
        var shape = new Sphere();
        var i = new Intersection(shape, 1);

        var comps = new Precompute(i, r);
        comps.T.ShouldBe(i.T);
        comps.Shape.ShouldBe(shape);
        comps.Point.ShouldBe(Vec4.Point(0, 0, 1));
        comps.EyeVec.ShouldBe(Vec4.Vector(0, 0, -1));
        comps.NormalVec.ShouldBe(Vec4.Vector(0, 0, -1));
        comps.Inside.ShouldBeTrue();
    }

    [Fact]
    public void TestPrecomputeReflectionVector()
    {
        var shape = new Plane();
        var r = new Ray(Vec4.Point(0, 1, -1), Vec4.Vector(0, -Math.Sqrt(2) / 2, Math.Sqrt(2) / 2));
        var i = new Intersection(shape, Math.Sqrt(2));
        var comps = new Precompute(i, r);
        comps.ReflectVec.ShouldBe(Vec4.Vector(0, Math.Sqrt(2) / 2, Math.Sqrt(2) / 2));
    }

    [Theory]
    [MemberData(nameof(RefractiveIndicesTestData))]
    public void TestRefractiveIndicesInitialisation(int index, double expectedN1, double expectedN2)
    {
        var a = Sphere.GlassSphere();
        a.Transformation = Matrix.ScalingMatrix(2, 2, 2);
        a.Material = a.Material with { RefractiveIndex = 1.5d };

        var b = Sphere.GlassSphere();
        b.Transformation = Matrix.TranslationMatrix(0, 0, -0.25d);
        b.Material = b.Material with { RefractiveIndex = 2.0d };

        var c = Sphere.GlassSphere();
        c.Transformation = Matrix.TranslationMatrix(0, 0, 0.25d);
        c.Material = c.Material with { RefractiveIndex = 2.5d };

        var r = new Ray(Vec4.Point(0, 0, -4), Vec4.Vector(0, 0, 1));
        var xs = new IntersectionSet(
            new Intersection(a, 2.0d),
            new Intersection(b, 2.75d),
            new Intersection(c, 3.25d),
            new Intersection(b, 4.75d),
            new Intersection(c, 5.25d),
            new Intersection(a, 6.0d)
        );

        var comps = new Precompute(xs.Values.ElementAt(index), r, xs);
        comps.N1.ShouldBe(expectedN1);
        comps.N2.ShouldBe(expectedN2);
    }

    [Fact]
    public void TestUnderPointIsOffsetBelowTheSurface()
    {
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var shape = Sphere.GlassSphere(Matrix.TranslationMatrix(0, 0, 1));
        var i = new Intersection(shape, 5);
        var xs = new IntersectionSet(i);

        var comps = new Precompute(i, r, xs);
        comps.UnderPoint.Z.ShouldBeGreaterThan(Helper.Epsilon / 2);
        comps.Point.Z.ShouldBeLessThan(comps.UnderPoint.Z);
    }

    [Fact]
    public void TestSchlickApproximationUnderTotalInternalReflection()
    {
        var shape = Sphere.GlassSphere();
        var r = new Ray(Vec4.Point(0, 0, Math.Sqrt(2) / 2), Vec4.Vector(0, 1, 0));
        var xs = new IntersectionSet(new Intersection(shape, -Math.Sqrt(2) / 2),
            new Intersection(shape, Math.Sqrt(2) / 2));

        var comps = new Precompute(xs.Values.ElementAt(1), r, xs);
        comps.Schlick().ShouldBe(1);
    }

    [Fact]
    public void TestSchlickApproximationWithAPerpendicularViewingAngle()
    {
        var shape = Sphere.GlassSphere();
        var r = new Ray(Vec4.Point(0, 0, 0), Vec4.Vector(0, 1, 0));
        var xs = new IntersectionSet(new Intersection(shape, -1), new Intersection(shape, 1));

        var comps = new Precompute(xs.Values.ElementAt(1), r, xs);
        comps.Schlick().IsEqual(0.04d).ShouldBeTrue();
    }

    [Fact]
    public void TestSchlickApproximationWithSmallAngleAnN2GreaterThanN1()
    {
        var shape = Sphere.GlassSphere();
        var r = new Ray(Vec4.Point(0, 0.99d, -2), Vec4.Vector(0, 0, 1));
        var xs = new IntersectionSet(new Intersection(shape, 1.8589d));

        var comps = new Precompute(xs.Values.ElementAt(0), r, xs);
        comps.Schlick().IsEqual(0.48873d).ShouldBeTrue();
    }
}