using RTC.Datastructures;
using RTC.Objects;

namespace RTC.Primitives;

/// <summary>
///     A world that contains collections of shapes and lights.
/// </summary>
/// <param name="shapes">The shapes contained in the world.</param>
/// <param name="lights">The lights contained in the world.</param>
public readonly struct World(List<Shape> shapes, List<PointLight> lights)
{
    public World() : this([], [])
    {
    }

    /// <summary>
    ///     The shapes contained in the world.
    /// </summary>
    public List<Shape> Shapes { get; } = shapes;

    /// <summary>
    ///     The lights contained in the world.
    /// </summary>
    public List<PointLight> Lights { get; } = lights;

    /// <summary>
    ///     Creates a default world with a single light source and two spheres.
    /// </summary>
    /// <returns></returns>
    public static World DefaultWorld()
    {
        var light = new PointLight(Colour.White, Vec4.Point(-10, 10, -10));
        var s1 = new Sphere();
        s1.Material = s1.Material with
        {
            Colour = new Colour(0.8d, 1.0d, 0.6d),
            Diffuse = 0.7d,
            Specular = 0.2d
        };
        var s2 = new Sphere(Matrix.ScalingMatrix(0.5d, 0.5d, 0.5d));
        return new World([s1, s2], [light]);
    }

    /// <summary>
    ///     Intersects the ray with all shapes in the world.
    /// </summary>
    /// <param name="r">The ray that is being intersected with.</param>
    /// <returns>The set of intersections between the ray and the shapes in the world.</returns>
    public IntersectionSet IntersectWorld(Ray r)
    {
        var intersections = new IntersectionSet();
        foreach (var shape in Shapes) intersections.AddIntersections(shape.Intersect(r));
        return intersections;
    }

    /// <summary>
    ///     Calculates the colour of the given hit.
    /// </summary>
    /// <param name="comps">The precomputed information about the hit.</param>
    /// <param name="depth">The recursion depth for reflections.</param>
    /// <returns>The colour of the hit.</returns>
    public Colour ShadeHit(Precompute comps, uint depth)
    {
        var colour = Colour.Black;

        foreach (var light in Lights)
        {
            var surface = comps.Shape.Material.Lighting(comps.Shape, light,
                comps.OverPoint,
                comps.EyeVec,
                comps.NormalVec,
                IsShadowed(light, comps.OverPoint)
            );

            var reflected = ReflectedColour(comps, depth);
            var refracted = RefractedColour(comps, depth);

            var material = comps.Shape.Material;
            if (material is { Reflective: > 0, Transparency: > 0 })
            {
                var reflectance = comps.Schlick();
                colour += surface + reflected * reflectance + refracted * (1 - reflectance);
                continue;
            }

            colour += surface + reflected + refracted;
        }

        return colour;
    }

    /// <summary>
    ///     Intersects the ray with the shapes in the world and calculates the colour of the resulting intersection.
    /// </summary>
    /// <param name="r">The ray that is being intersected with.</param>
    /// <param name="depth">The recursion depth for reflections.</param>
    /// <returns>The colour of the intersection. Black if no intersection occurs.</returns>
    public Colour ColourAt(Ray r, uint depth)
    {
        var xs = IntersectWorld(r);
        var hit = xs.Hit();
        return hit == null ? Colour.Black : ShadeHit(new Precompute(hit.Value, r, xs), depth);
    }

    /// <summary>
    ///     Checks if something intersects a shadow ray between the point and the light source.
    /// </summary>
    /// <param name="point">The point to check for shadowing.</param>
    /// <param name="light">The light source to check against.</param>
    /// <returns><c>true</c> if the point is shadowed, <c>false</c> otherwise.</returns>
    public bool IsShadowed(PointLight light, Vec4 point)
    {
        var v = light.Position - point;
        var distance = v.Magnitude;
        var direction = v.Normalise();

        var r = new Ray(point, direction);
        var intersections = IntersectWorld(r);

        var h = intersections.Hit();
        return h != null && h.Value.T < distance;
    }

    /// <summary>
    ///     Computes the reflected colour of the given computed values.
    /// </summary>
    /// <param name="comps">The computed values.</param>
    /// <param name="depth">The recursion depth for reflections.</param>
    /// <returns>The reflected colour.</returns>
    public Colour ReflectedColour(Precompute comps, uint depth)
    {
        if (comps.Shape.Material.Reflective == 0 || depth == 0) return Colour.Black;

        var reflectRay = new Ray(comps.OverPoint, comps.ReflectVec);
        var colour = ColourAt(reflectRay, depth - 1);

        return colour * comps.Shape.Material.Reflective;
    }

    /// <summary>
    ///     Computes the refracted colour of the given computed values.
    /// </summary>
    /// <param name="comps">The computed values.</param>
    /// <param name="depth">The recursion depth for refractions.</param>
    /// <returns>The refracted colour.</returns>
    public Colour RefractedColour(Precompute comps, uint depth)
    {
        if (comps.Shape.Material.Transparency == 0 || depth == 0) return Colour.Black;

        // find the ratio of the first index of refraction to the second
        var nRatio = comps.N1 / comps.N2;
        // cos(thetaI) is the same as the fot product of the two vectors
        var cosI = comps.EyeVec.Dot(comps.NormalVec);
        // find sin(thetaT)^2 via trigonometric identities
        var sin2T = nRatio * nRatio * (1 - cosI * cosI);

        if (sin2T > 1) return Colour.Black;

        // find cos(thetaT) via trigonometric identities
        var cosT = Math.Sqrt(1 - sin2T);
        // compute the direction of the refracted ray
        var direction = comps.NormalVec * (nRatio * cosI - cosT) - comps.EyeVec * nRatio;
        var refractedRay = new Ray(comps.UnderPoint, direction);
        // find the colour of the refracted ray, taking into account the transparency of the material
        return ColourAt(refractedRay, depth - 1) * comps.Shape.Material.Transparency;
    }
}