using RTC.Datastructures;
using RTC.Objects;

namespace RTC.Primitives.Patterns;

/// <summary>
///     A ring pattern.
/// </summary>
public class RingPattern : Pattern
{
    public RingPattern(Colour a, Colour b)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = Matrix.IdentityMatrix(4);
    }

    public RingPattern(Colour a, Colour b, Matrix transform)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = transform;
    }

    public RingPattern(Pattern a, Pattern b)
    {
        A = a;
        B = b;
        Transform = Matrix.IdentityMatrix(4);
    }

    public RingPattern(Pattern a, Pattern b, Matrix transform)
    {
        A = a;
        B = b;
        Transform = transform;
    }

    /// <summary>
    ///     Colour A
    /// </summary>
    private Pattern A { get; }

    /// <summary>
    ///     Colour B
    /// </summary>
    private Pattern B { get; }

    public override Colour PatternAt(Shape shape, Vec4 point)
    {
        return Math.Floor(Math.Sqrt(point.X * point.X + point.Z * point.Z)) % 2 == 0
            ? A.PatternAtObject(shape, point)
            : B.PatternAtObject(shape, point);
    }
}