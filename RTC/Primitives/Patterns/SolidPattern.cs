using RTC.Datastructures;
using RTC.Objects;

namespace RTC.Primitives.Patterns;

/// <summary>
///     A pattern that is always the same colour.
/// </summary>
public class SolidPattern : Pattern
{
    public SolidPattern(Colour colour)
    {
        Colour = colour;
        Transform = Matrix.IdentityMatrix(4);
    }

    public SolidPattern(Colour colour, Matrix transform)
    {
        Colour = colour;
        Transform = transform;
    }

    private Colour Colour { get; }

    public override Colour PatternAt(Shape shape, Vec4 point)
    {
        return Colour;
    }
}