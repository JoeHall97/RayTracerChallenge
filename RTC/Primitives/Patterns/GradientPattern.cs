using RTC.Datastructures;

namespace RTC.Primitives.Patterns;

/// <summary>
///     A gradient pattern.
/// </summary>
public class GradientPattern : Pattern
{
    public GradientPattern(Colour a, Colour b)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = Matrix.IdentityMatrix(4);
    }

    public GradientPattern(Colour a, Colour b, Matrix transform)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = transform;
    }

    public GradientPattern(Pattern a, Pattern b)
    {
        A = a;
        B = b;
        Transform = Matrix.IdentityMatrix(4);
    }

    public GradientPattern(Pattern a, Pattern b, Matrix transform)
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
        var a = A.PatternAt(point);
        var distance = B.PatternAt(point) - a;
        var fraction = point.X - Math.Floor(point.X);
        return a + distance * fraction;
    }
}