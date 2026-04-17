using RTC.Datastructures;

namespace RTC.Primitives.Patterns;

public class TestPattern : Pattern
{
    public TestPattern()
    {
        Transform = Matrix.IdentityMatrix(4);
    }

    public override Colour PatternAt(Vec4 point)
    {
        return new Colour(point.X, point.Y, point.Z);
    }
}