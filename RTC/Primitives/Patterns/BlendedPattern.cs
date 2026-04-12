using RTC.Datastructures;
using RTC.Objects;

namespace RTC.Primitives.Patterns;

/// <summary>
///     Blends two patterns together.
/// </summary>
public class BlendedPattern : Pattern
{
    public BlendedPattern(Pattern a, Pattern b)
    {
        A = a;
        B = b;
        Transform = Matrix.IdentityMatrix(4);
    }

    public BlendedPattern(Pattern a, Pattern b, Matrix transform)
    {
        A = a;
        B = b;
        Transform = transform;
    }

    /// <summary>
    ///     Pattern A
    /// </summary>
    private Pattern A { get; }

    /// <summary>
    ///     Pattern B
    /// </summary>
    private Pattern B { get; }

    public override Colour PatternAt(Shape shape, Vec4 point)
    {
        throw new NotImplementedException();
    }

    public override Colour PatternAtObject(Shape shape, Vec4 worldPoint)
    {
        return A.PatternAtObject(shape, worldPoint) + B.PatternAtObject(shape, worldPoint);
    }
}