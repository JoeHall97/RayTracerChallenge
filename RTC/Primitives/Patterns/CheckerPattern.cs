using RTC.Datastructures;

namespace RTC.Primitives.Patterns;

/// <summary>
///     A checker pattern.
/// </summary>
public class CheckerPattern : Pattern
{
    public CheckerPattern(Colour a, Colour b)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = Matrix.IdentityMatrix(4);
    }

    public CheckerPattern(Colour a, Colour b, Matrix transform)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = transform;
    }

    public CheckerPattern(Pattern a, Pattern b)
    {
        A = a;
        B = b;
        Transform = Matrix.IdentityMatrix(4);
    }

    public CheckerPattern(Pattern a, Pattern b, Matrix transform)
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

    public override Colour PatternAt(Vec4 point)
    {
        return (Math.Floor(point.X) + Math.Floor(point.Y) + Math.Floor(point.Z)) % 2 == 0
            ? A.PatternAt(point)
            : B.PatternAt(point);
    }
}