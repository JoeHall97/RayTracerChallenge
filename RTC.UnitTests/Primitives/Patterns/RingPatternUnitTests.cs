using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;
using Shouldly;

namespace RTC.UnitTests.Primitives.Patterns;

public class RingPatternUnitTests
{
    [Fact]
    public void TestRingPattern()
    {
        var pattern = new RingPattern(Colour.White, Colour.Black);

        var s = new Sphere();
        pattern.PatternAt(s, Vec4.Point(0, 0, 0)).ShouldBe(Colour.White);
        pattern.PatternAt(s, Vec4.Point(1, 0, 0)).ShouldBe(Colour.Black);
        pattern.PatternAt(s, Vec4.Point(0, 0, 1)).ShouldBe(Colour.Black);
        pattern.PatternAt(s, Vec4.Point(0.708d, 0, 0.708d)).ShouldBe(Colour.Black);
    }
}