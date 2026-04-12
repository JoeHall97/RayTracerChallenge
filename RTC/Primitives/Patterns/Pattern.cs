using RTC.Datastructures;
using RTC.Objects;

namespace RTC.Primitives.Patterns;

public abstract class Pattern
{
    /// <summary>
    ///     The transformation matrix of the pattern.
    /// </summary>
    public Matrix Transform { get; init; }

    /// <summary>
    ///     Computes the colour of the pattern at the given point.
    /// </summary>
    /// <param name="shape">The shape on which the pattern is applied.</param>
    /// <param name="point">The point at which to compute the pattern colour.</param>
    /// <returns>The colour of the pattern at the given point.</returns>
    public abstract Colour PatternAt(Shape shape, Vec4 point);

    /// <summary>
    ///     Computes the colour of the pattern at the given point on the given shape.
    /// </summary>
    /// <param name="shape">The shape on which the pattern is applied.</param>
    /// <param name="worldPoint">The point in the world at which to compute the pattern colour.</param>
    /// <returns>The colour of the pattern at the given point on the given shape.</returns>
    public virtual Colour PatternAtObject(Shape shape, Vec4 worldPoint)
    {
        var objectPoint = shape.Transformation.Inverse() * worldPoint;
        var patternPoint = Transform.Inverse() * objectPoint;
        return PatternAt(shape, patternPoint);
    }
}