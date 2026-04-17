using RTC.Datastructures;
using RTC.Primitives;

namespace RTC.Objects;

/// <summary>
///     A 3D sphere.
/// </summary>
/// <param name="origin">The origin/position of the sphere.</param>
/// <param name="radius">The radius of the sphere.</param>
public class Sphere(Vec4 origin, float radius) : Shape
{
    public Sphere() : this(Vec4.Point(0, 0, 0), 1)
    {
        Transformation = Matrix.IdentityMatrix(4);
    }

    public Sphere(Matrix transformation) : this(Vec4.Point(0, 0, 0), 1)
    {
        Transformation = transformation;
    }

    public Sphere(Material material) : this(Vec4.Point(0, 0, 0), 1)
    {
        Transformation = Matrix.IdentityMatrix(4);
        Material = material;
    }

    public Sphere(Material material, Matrix transform) : this(Vec4.Point(0, 0, 0), 1)
    {
        Transformation = transform;
        Material = material;
    }

    /// <summary>
    ///     The origin/position of the sphere.
    /// </summary>
    private Vec4 Origin { get; } = origin;

    /// <summary>
    ///     The radius of the sphere.
    /// </summary>
    private float Radius { get; } = radius;

    public override string ToString()
    {
        return $"Sphere(origin: {Origin}, radius: {Radius})";
    }

    /// <summary>
    ///     Creates a sphere with a glassy material.
    /// </summary>
    /// <returns></returns>
    public static Sphere GlassSphere()
    {
        return new Sphere(new Material
        {
            Transparency = 1,
            RefractiveIndex = 1.5d
        });
    }

    /// <summary>
    ///     Creates a sphere with a glassy material.
    /// </summary>
    /// <returns></returns>
    public static Sphere GlassSphere(Matrix transformation)
    {
        return new Sphere(new Material
        {
            Transparency = 1,
            RefractiveIndex = 1.5d
        }, transformation);
    }

    protected override Intersection[] LocalIntersect(Ray localRay)
    {
        var sphereToRay = localRay.Origin - Origin;

        var a = localRay.Direction.Dot(localRay.Direction);
        var b = 2 * localRay.Direction.Dot(sphereToRay);
        var c = sphereToRay.Dot(sphereToRay) - Radius;

        var discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return [];

        var t1 = (-b - Math.Sqrt(discriminant)) / (2 * a);
        var t2 = (-b + Math.Sqrt(discriminant)) / (2 * a);
        return [new Intersection(this, t1), new Intersection(this, t2)];
    }

    protected override Vec4 LocalNormalAt(Vec4 objectPoint)
    {
        return objectPoint - Origin;
    }
}