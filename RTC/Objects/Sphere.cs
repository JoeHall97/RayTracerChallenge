using RTC.Datastructures;

namespace RTC.Objects;

/// <summary>
/// A 3D sphere.
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

    /// <summary>
    /// The origin/position of the sphere.
    /// </summary>
    public Vec4 Origin { get; init; } = origin;

    /// <summary>
    /// The radius of the sphere.
    /// </summary>
    public float Radius { get; init; } = radius;

    public override string ToString() => $"Sphere(origin: {Origin}, radius: {Radius})";
    
    /// <summary>
    /// Calculate the intersections of the given ray with the sphere.
    /// </summary>
    /// <param name="ray">The ray that is intersecting the sphere.</param>
    /// <returns>The intersection points of the ray with the sphere, if any.</returns>
    public Intersection[] Intersect(Ray ray)
    {
        var transformedRay = ray.Transform(Transformation.Inverse());
        var sphereToRay = transformedRay.Origin - Vec4.Point(0, 0, 0);
        
        var a = transformedRay.Direction.Dot(transformedRay.Direction);
        var b = 2 * transformedRay.Direction.Dot(sphereToRay);
        var c = sphereToRay.Dot(sphereToRay) - 1;
        
        var discriminant = (b * b) - (4 * a * c);
        if (discriminant < 0) return [];
        
        var t1 = (-b - Math.Sqrt(discriminant)) / (2 * a);
        var t2 = (-b + Math.Sqrt(discriminant)) / (2 * a);
        return [ new Intersection(this, t1), new Intersection(this, t2) ];
    }
}