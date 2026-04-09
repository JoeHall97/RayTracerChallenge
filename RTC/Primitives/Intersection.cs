using RTC.Objects;

namespace RTC.Primitives;

/// <summary>
/// An intersection between a ray and a shape.
/// </summary>
/// <param name="s">The shape the intersection occurred with.</param>
/// <param name="t">The tick/time when the ray intersection occurred.</param>
public readonly struct Intersection(Shape s, double t)
{
    /// <summary>
    /// The shape the intersection occurred with.
    /// </summary>
    public Shape Shape { get; } = s;
    /// <summary>
    /// The tick/time when the ray intersection occurred.
    /// </summary>
    public double T { get; } = t;
}