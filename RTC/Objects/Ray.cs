using RTC.Datastructures;

namespace RTC.Objects;

/// <summary>
/// A ray of light.
/// </summary>
/// <param name="origin">The origin, or starting point, of the ray.</param>
/// <param name="direction">The directional vector of the ray.</param>
public class Ray(Vec4 origin, Vec4 direction)
{
    /// <summary>
    /// The origin, or starting point, of the ray.
    /// </summary>
    public Vec4 Origin { get; set; } = origin;
    /// <summary>
    /// The directional vector of the ray.
    /// </summary>
    public Vec4 Direction { get; set; } = direction;

    public override string ToString()
    {
        return $"Ray: Origin = {Origin}, Direction = {Direction}";
    }
    
    /// <summary>
    /// Gets the position of the ray at a given time.
    /// </summary>
    /// <param name="t">The time, or tick, at which to calculate the position.</param>
    /// <returns>The position of the ray at the specified time.</returns>
    public Vec4 Position(double t)
    {
        return Origin + Direction * t;
    }
    
    /// <summary>
    /// Transforms the ray by a given matrix, returning the result as a new Ray.
    /// </summary>
    /// <param name="m">The matrix to transform the ray by.</param>
    /// <returns>The transformed ray.</returns>
    public Ray Transform(Matrix m)
    {
        return new Ray(m * Origin, m * Direction);
    }
}