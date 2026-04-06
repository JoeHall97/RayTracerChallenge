using RTC.Datastructures;
using RTC.Helpers;

namespace RTC.Objects;

public class Material
{
    public Colour Colour { get; set; } = new Colour(1, 1, 1);
    public double Ambient { get; set; } = 0.1d;
    public double Diffuse { get; set; } = 0.9d;
    public double Specular { get; set; } = 0.9d;
    public double Shininess { get; set; } = 200.0d;
    
    public override string ToString() => $"Colour: {Colour}, Ambient: {Ambient}, Diffuse: {Diffuse}, Specular: {Specular}, Shininess: {Shininess}";

    public bool Equals(Material other)
    {
        return Colour.Equals(other.Colour) && 
               Ambient.IsEqual(other.Ambient) && 
               Diffuse.IsEqual(other.Diffuse) && 
               Specular.IsEqual(other.Specular) && 
               Shininess.IsEqual(other.Shininess);
    }

    /// <summary>
    /// Calculates the lighting/colour of the material at the given position.
    /// </summary>
    /// <param name="light">The light source.</param>
    /// <param name="position">The position to calculate lighting for.</param>
    /// <param name="eyeVec">The vector from the eye/camera.</param>
    /// <param name="normal">The normal vector at the position.</param>
    /// <returns>The colour of the material at the given position.</returns>
    public Colour Lighting(PointLight light, Vec4 position, Vec4 eyeVec, Vec4 normal)
    {
        var effectiveColour = Colour * light.Intensity;
        var lightVec = (light.Position - position).Normalised;
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
        
        return ambient + diffuse + specular;
    }
}