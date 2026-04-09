using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives;
using Shouldly;

namespace RTC.UnitTests.Primitives;

public class WorldUnitTests
{
    public static IEnumerable<object[]> ShadowingTestData =>
    [
        // there is no shadow when nothing is blocking a light source
        [Vec4.Point(0, 10, 0), false],
        // there is shadow when an object is blocking a light source
        [Vec4.Point(10, -10, 10), true],
        // there is no shadow when an object is behind the light source
        [Vec4.Point(-20, 20, -20), false],
        // there is no shadow when an object is behind the point
        [Vec4.Point(-2, 2, -2), false],
    ];
    
    public static IEnumerable<object[]> ViewTransformTestData =>
    [
        // The default orientation.
        [Vec4.Point(0, 0, 0), Vec4.Point(0, 0, -1), Vec4.Vector(0, 1, 0), Matrix.IdentityMatrix(4)],
        // A view transformation matrix looking in the positive z direction.
        [Vec4.Point(0, 0, 0), Vec4.Point(0, 0, 1), Vec4.Vector(0, 1, 0), Matrix.ScalingMatrix(-1, 1, -1)],
        // The view transformation moves the world.
        [Vec4.Point(0, 0, 8), Vec4.Point(0, 0, 0), Vec4.Vector(0, 1, 0), Matrix.TranslationMatrix(0, 0, -8)],
        // An arbitrary view transformation.
        [Vec4.Point(1, 3, 2), Vec4.Point(4, -2, 8), Vec4.Vector(1, 1, 0), new Matrix(new double[,]
        {
            {-0.50709d, 0.50709d, 0.67612d, -2.36643d},
            {0.76772d, 0.60609d, 0.12122d, -2.82843d},
            {-0.35857d, 0.59761d, -0.71714d, 0.0d},
            {0.0d, 0.0d, 0.0d, 1.0d},
        })],
    ];
    
    [Fact]
    public void TestWorldIntersections()
    {
        var w = World.DefaultWorld();
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var xs = w.IntersectWorld(r);
        
        xs.Values.Count.ShouldBe(4);
        xs.Values.ElementAt(0).T.ShouldBe(4.0d);
        xs.Values.ElementAt(1).T.ShouldBe(4.5d);
        xs.Values.ElementAt(2).T.ShouldBe(5.5d);
        xs.Values.ElementAt(3).T.ShouldBe(6.0d);
    }

    [Fact]
    public void TestShadingAnIntersection()
    {
        var w = World.DefaultWorld();
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var shape = w.Shapes.First();
        var i = new Intersection(shape, 4);
        
        var comps = new Precompute(i, r);
        var colour = w.ShadeHit(comps);
        colour.ShouldBe(new Colour(0.38066d, 0.47583d, 0.2855d));
    }

    [Fact]
    public void TestShadingAnIntersectionFromTheInside()
    {
        var w = World.DefaultWorld();
        w.Lights.RemoveAt(0);
        w.Lights.Add(new PointLight(Colour.White, Vec4.Point(0, 0.25d, 0)));
        var r = new Ray(Vec4.Point(0, 0, 0), Vec4.Vector(0, 0, 1));
        var shape = w.Shapes[1];
        var i = new Intersection(shape, 0.5);
        
        var comps = new Precompute(i, r);
        var colour = w.ShadeHit(comps);
        colour.ShouldBe(new Colour(0.90498d, 0.90498d, 0.90498d));
    }
    
    [Fact]
    public void TestColourWhenTheRayMisses()
    {
        var w = World.DefaultWorld();
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 1, 0));
        var c = w.ColourAt(r);    
        c.ShouldBe(Colour.Black);
    }
    
    [Fact]
    public void TestColourWhenTheRayHits()
    {
        var w = World.DefaultWorld();
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var c = w.ColourAt(r);
        c.ShouldBe(new Colour(0.38066d, 0.47583d, 0.2855d));
    }
    
    [Fact]
    public void TestColourWhenTheRayIntersectsBehindAnObject()
    {
        var w = World.DefaultWorld();
        
        var outer = w.Shapes[0];
        outer.Material = outer.Material with { Ambient = 1 };
        var inner = w.Shapes[1];
        inner.Material = inner.Material with { Ambient = 1 };
        
        var r = new Ray(Vec4.Point(0, 0, 0.75), Vec4.Vector(0, 0, -1));
        var c = w.ColourAt(r);
        c.ShouldBe(inner.Material.Colour);
    }
    
    [Theory]
    [MemberData(nameof(ViewTransformTestData))]
    public void TestViewTransform(Vec4 from, Vec4 to, Vec4 up, Matrix expected)
    {
        Matrix.ViewTransform(from, to, up).ShouldBe(expected);
    }

    [Theory]
    [MemberData(nameof(ShadowingTestData))]
    public void TestShadowing(Vec4 point, bool expected)
    {
        var w = World.DefaultWorld();
        w.IsShadowed(w.Lights.First(), point).ShouldBe(expected);
    }

    [Fact]
    public void TestShadeHitWithAnIntersectionInShadow()
    {
        var w = new World();
        w.Lights.Add(new PointLight(Colour.White, Vec4.Point(0, 0, -10)));
        
        var s1 = new Sphere();
        w.Shapes.Add(s1);
        var s2 = new Sphere()
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 10)
        };
        w.Shapes.Add(s2);
        
        var r = new Ray(Vec4.Point(0, 0, 5), Vec4.Vector(0, 0, 1));
        var i = new Intersection(s2, 4);
        var comps = new Precompute(i, r);
        var c = w.ShadeHit(comps);
        c.ShouldBe(new Colour(0.1d, 0.1d, 0.1d));
    }
    
    [Fact]
    public void TestShadeHitShouldOffsetThePoint()
    {
        var r = new Ray(Vec4.Point(0, 0, -5), Vec4.Vector(0, 0, 1));
        var shape = new Sphere()
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 1)
        };
        var i = new Intersection(shape, 5);
        
        var comps = new Precompute(i, r);
        comps.OverPoint.Z.ShouldBeLessThan(-Helper.Epsilon/2);
        comps.Point.Z.ShouldBeGreaterThan(comps.OverPoint.Z);
    }
}