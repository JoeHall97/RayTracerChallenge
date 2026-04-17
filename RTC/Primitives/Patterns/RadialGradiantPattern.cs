using RTC.Datastructures;

namespace RTC.Primitives.Patterns;

public class RadialGradiantPattern : Pattern
{
    public RadialGradiantPattern(Colour a, Colour b)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = Matrix.IdentityMatrix(4);
    }

    public RadialGradiantPattern(Colour a, Colour b, Matrix transform)
    {
        A = new SolidPattern(a);
        B = new SolidPattern(b);
        Transform = transform;
    }

    public RadialGradiantPattern(Pattern a, Pattern b)
    {
        A = a;
        B = b;
        Transform = Matrix.IdentityMatrix(4);
    }

    public RadialGradiantPattern(Pattern a, Pattern b, Matrix transform)
    {
        A = a;
        B = b;
        Transform = transform;
    }

    private Pattern A { get; }
    private Pattern B { get; }

    public override Colour PatternAt(Vec4 point)
    {
        var x = Math.Sqrt(point.X * point.X + point.Z * point.Z);
        var fraction = x - Math.Floor(x);
        var distance = B.PatternAt(point) - A.PatternAt(point);
        return A.PatternAt(point) + distance * fraction;
    }
}