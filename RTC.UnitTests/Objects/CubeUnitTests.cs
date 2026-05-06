using RTC.Datastructures;
using RTC.Objects;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class CubeUnitTests
{
    public static IEnumerable<object[]> RayCubeIntersectionTestData =>
    [
        // positive x axis
        [Vec4.Point(5, 0.5d, 0), Vec4.Vector(-1, 0, 0), 4, 6],   
        // negative x axis
        [Vec4.Point(-5, 0.5d, 0), Vec4.Vector(1, 0, 0), 4, 6],   
        // positive y axis
        [Vec4.Point(0.5d, 5, 0), Vec4.Vector(0, -1, 0), 4, 6],   
        // negative y axis
        [Vec4.Point(0.5d, -5, 0), Vec4.Vector(0, 1, 0), 4, 6],   
        // positive z axis
        [Vec4.Point(0.5d, 0, 5), Vec4.Vector(0, 0, -1), 4, 6],   
        // negative z axis
        [Vec4.Point(0.5d, 0, -5), Vec4.Vector(0, 0, 1), 4, 6],   
        // inside cube
        [Vec4.Point(0, 0.5d, 0), Vec4.Vector(0, 0, 1), -1, 1],   
    ];

    public static IEnumerable<object[]> RayMissesCubeTestData =>
    [
        [Vec4.Point(-2, 0, 0), Vec4.Vector(0.2673d, 0.5345d, 0.8018d)],
        [Vec4.Point(0, -2, 0), Vec4.Vector(0.8018d, 0.2673d, 0.5345d)],
        [Vec4.Point(0, 0, -2), Vec4.Vector(0.5345d, 0.8018d, 0.2673d)],
        [Vec4.Point(2, 0, 2), Vec4.Vector(0, 0, -1)],
        [Vec4.Point(0, 2, 2), Vec4.Vector(0, -1, 0)],
        [Vec4.Point(2, 2, 0), Vec4.Vector(-1, 0, 0)],
    ];

    public static IEnumerable<object[]> CubeSurfaceNormalTestData =>
    [
        [Vec4.Point(1, 0.5d, -0.8d), Vec4.Vector(1, 0, 0)],
        [Vec4.Point(-1, -0.2d, 0.9d), Vec4.Vector(-1, 0, 0)],
        [Vec4.Point(-0.4d, 1, -0.1d), Vec4.Vector(0, 1, 0)],
        [Vec4.Point(0.3d, -1, -0.7d), Vec4.Vector(0, -1, 0)],
        [Vec4.Point(-0.6d, 0.3d, 1), Vec4.Vector(0, 0, 1)],
        [Vec4.Point(0.4d, 0.4d, -1), Vec4.Vector(0, 0, -1)],
        [Vec4.Point(1, 1, 1), Vec4.Vector(1, 0, 0)],
        [Vec4.Point(-1, -1, -1), Vec4.Vector(-1, 0, 0)],
    ];
    
    [Theory]
    [MemberData(nameof(RayCubeIntersectionTestData))]
    public void TestRayCubeIntersection(Vec4 origin, Vec4 direction, double expectedT1, double expectedT2)
    {
        var cube = new Cube();
        
        var xs = cube.Intersect(new Ray(origin, direction));
        xs.Length.ShouldBe(2);
        xs[0].T.ShouldBe(expectedT1);
        xs[1].T.ShouldBe(expectedT2);
    }
    
    [Theory]
    [MemberData(nameof(RayMissesCubeTestData))]
    public void TestRayMissesCube(Vec4 origin, Vec4 direction)
    {
        var cube = new Cube();
        
        var xs = cube.Intersect(new Ray(origin, direction));
        xs.Length.ShouldBe(0);
    }   
    
    [Theory]
    [MemberData(nameof(CubeSurfaceNormalTestData))]
    public void TestCubeSurfaceNormal(Vec4 point, Vec4 expectedNormal)
    {
        var cube = new Cube();
        
        cube.NormalAt(point).ShouldBe(expectedNormal);
    }  
}