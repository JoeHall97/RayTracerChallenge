using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives.Patterns;

namespace RTC.Primitives;

/// <summary>
///     A material for a shape's surface.
/// </summary>
public readonly struct Material : IEquatable<Material>
{
    public Material()
    {
    }

    public Material(Pattern pattern)
    {
        Pattern = pattern;
    }

    public Material(Colour colour)
    {
        Colour = colour;
    }

    public Material(Colour colour, Pattern pattern)
    {
        Colour = colour;
        Pattern = pattern;
    }

    /// <summary>
    ///     The colour of the material.
    /// </summary>
    public Colour Colour { get; init; } = Colour.White;

    /// <summary>
    ///     The pattern of the shape.
    /// </summary>
    public Pattern? Pattern { get; init; } = null;

    /// <summary>
    ///     The ambient light reflection.
    /// </summary>
    public double Ambient { get; init; } = 0.1d;

    /// <summary>
    ///     The diffuse light reflection.
    /// </summary>
    public double Diffuse { get; init; } = 0.9d;

    /// <summary>
    ///     The specular light reflection.
    /// </summary>
    public double Specular { get; init; } = 0.9d;

    /// <summary>
    ///     The shininess of the material.
    /// </summary>
    public double Shininess { get; init; } = 200.0d;

    /// <summary>
    ///     The reflectivity of the material.
    /// </summary>
    public double Reflective { get; init; } = 0.0d;

    /// <summary>
    ///     The transparency of the material.
    /// </summary>
    public double Transparency { get; init; } = 0.0d;

    /// <summary>
    ///     The refractive index of the material.
    /// </summary>
    public double RefractiveIndex { get; init; } = 1.0d;

    public override string ToString()
    {
        return
            $"Colour: {Colour}, Ambient: {Ambient}, Diffuse: {Diffuse}, Specular: {Specular}, Shininess: {Shininess}";
    }

    public bool Equals(Material other)
    {
        return Colour.Equals(other.Colour) &&
               Ambient.IsEqual(other.Ambient) &&
               Diffuse.IsEqual(other.Diffuse) &&
               Specular.IsEqual(other.Specular) &&
               Shininess.IsEqual(other.Shininess);
    }

    /// <summary>
    ///     Calculates the lighting/colour of the material at the given position.
    /// </summary>
    /// <param name="shape">The shape that is being lit.</param>
    /// <param name="light">The light source.</param>
    /// <param name="position">The position to calculate lighting for.</param>
    /// <param name="eyeVec">The vector from the eye/camera.</param>
    /// <param name="normal">The normal vector at the position.</param>
    /// <param name="inShadow"><c>true</c> if the position is in shadow, else <c>false</c>.</param>
    /// <returns>The colour of the material at the given position.</returns>
    public Colour Lighting(Shape shape, PointLight light, Vec4 position, Vec4 eyeVec, Vec4 normal, bool inShadow)
    {
        var colour = Pattern?.PatternAtObject(shape, position) ?? Colour;

        var effectiveColour = colour * light.Intensity;
        var lightVec = (light.Position - position).Normalise();
        var ambient = effectiveColour * Ambient;

        var lightDotNormal = lightVec.Dot(normal);
        Colour diffuse, specular;
        if (lightDotNormal < 0)
        {
            diffuse = Colour.Black;
            specular = Colour.Black;
        }
        else
        {
            diffuse = effectiveColour * Diffuse * lightDotNormal;
            var reflectVec = (-lightVec).Reflect(normal);
            var reflectDotEye = reflectVec.Dot(eyeVec);

            if (reflectDotEye <= 0)
            {
                specular = Colour.Black;
            }
            else
            {
                var factor = Math.Pow(reflectDotEye, Shininess);
                specular = light.Intensity * Specular * factor;
            }
        }

        return inShadow ? ambient : ambient + diffuse + specular;
    }

    public override bool Equals(object? obj)
    {
        return obj is Material material && Equals(material);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Colour, Ambient, Diffuse, Specular, Shininess);
    }
}