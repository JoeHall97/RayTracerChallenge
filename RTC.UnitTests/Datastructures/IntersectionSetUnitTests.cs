using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using Shouldly;

namespace RTC.UnitTests.Datastructures;

public class IntersectionSetUnitTests
{
    public static IEnumerable<object[]> HitTestData =>
    [
        [new double[] { 1, 2 }, 1.0d],
        [new double[] { -1, 1 }, 1.0d],
        [new double[] { -2, -3 }, -1.0d],
        [new double[] { 5, 7, -3, 2 }, 2.0d],
    ];
    
    [Fact]
    public void TestAggregatingIntersections()
    {
        var s = new Sphere();
        var i1 = new Intersection(s, 2);
        var i2 = new Intersection(s, 3);
        var intersections = new IntersectionSet(i1, i2);

        intersections.Values.ElementAt(0).T.ShouldBe(2);
        intersections.Values.ElementAt(1).T.ShouldBe(3);
    }

    [Theory]
    [MemberData(nameof(HitTestData))]
    public void TestIntersectionSetHit(double[] values, double expectedValue)
    {
        var s = new Sphere();
        Intersection? expectedIntersection = null;
        
        var intersections = new IntersectionSet();
        foreach (var value in values)
        {
            var intersection = new Intersection(s, value);
            if (value.IsEqual(expectedValue)) expectedIntersection = intersection;
            intersections.Values.Add(intersection);
        }
        
        intersections.Hit.ShouldBe(expectedIntersection);
    }
}