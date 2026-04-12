using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives.Patterns;

namespace RTC.Primitives;

/// <summary>
///     A material for a shape's surface.
/// </summary>
/// <param name="colour">The colour of the material.</param>
/// <param name="ambient">The ambient light reflection.</param>
/// <param name="diffuse">The diffuse light reflection.</param>
/// <param name="specular">The specular light reflection.</param>
/// <param name="shininess">The shininess of the material.</param>
public struct Material(Colour colour, double ambient, double diffuse, double specular, double shininess)
{
    public Material() : this(Colour.White, 0.1d, 0.9d, 0.9d, 200.0d)
    {
    }

    public Material(StripePattern pattern) : this(Colour.White, 0.1d, 0.9d, 0.9d, 200.0d)
    {
        Pattern = pattern;
    }

    public Material(Colour colour) : this(colour, 0.1d, 0.9d, 0.9d, 200.0d)
    {
        Colour = colour;
    }

    public Material(Colour colour, StripePattern pattern) : this(colour, 0.1d, 0.9d, 0.9d, 200.0d)
    {
        Colour = colour;
        Pattern = pattern;
    }

    /// <summary>
    ///     The colour of the material.
    /// </summary>
    public Colour Colour { get; set; } = colour;

    /// <summary>
    ///     The ambient light reflection.
    /// </summary>
    public double Ambient { get; set; } = ambient;

    /// <summary>
    ///     The diffuse light reflection.
    /// </summary>
    public double Diffuse { get; set; } = diffuse;

    /// <summary>
    ///     The specular light reflection.
    /// </summary>
    public double Specular { get; set; } = specular;

    /// <summary>
    ///     The shininess of the material.
    /// </summary>
    public double Shininess { get; set; } = shininess;

    /// <summary>
    ///     The pattern of the shape.
    /// </summary>
    public Pattern? Pattern { get; set; } = null;

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
}