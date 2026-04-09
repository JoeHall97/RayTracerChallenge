using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using Shouldly;

namespace RTC.UnitTests.Primitives;

public class PrecomputeUnitTests
{
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
}