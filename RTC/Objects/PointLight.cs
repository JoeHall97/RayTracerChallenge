using RTC.Datastructures;
using RTC.Primitives;

namespace RTC.Objects;

/// <summary>
/// A light source with no size, existing at a single point.
/// </summary>
/// <param name="intensity">The intensity of the light.</param>
/// <param name="position">The position of the light in 3D space.</param>
public class PointLight(Colour intensity, Vec4 position)
{
    public Colour Intensity { get; set; } = intensity;
    public Vec4 Position { get; set; } = position;
}