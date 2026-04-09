using RTC.Datastructures;
using RTC.Primitives;

namespace RTC.Objects;

/// <summary>
/// An abstract shape that can be placed in the scene.
/// </summary>
public abstract class Shape
{
    /// <summary>
    /// The transformation matrix of the shape.
    /// </summary>
    public Matrix Transformation { get; set; } = Matrix.IdentityMatrix(4);
    /// <summary>
    /// The material of the shape.
    /// </summary>
    public Material Material { get; set; } = new();
    
    /// <summary>
    /// Calculate the intersections of the given ray with the shape.
    /// </summary>
    /// <param name="ray">The ray that is intersecting the shape.</param>
    /// <returns>The intersection points of the ray with the shape, if any.</returns>
    public Intersection[] Intersect(Ray ray)
    {
        var transformedRay = ray.Transform(Transformation.Inverse());
        return LocalIntersect(transformedRay);
    }

    /// <summary>
    /// Calculates the shape's normal vector at the given world point.
    /// </summary>
    /// <param name="worldPoint">The world point at which to calculate the normal.</param>
    /// <returns>The normal vector at the given world point.</returns>
    public abstract Vec4 NormalAt(Vec4 worldPoint);
    
    /// <summary>
    /// Calculates the intersections of the given ray with the concrete shape.
    /// </summary>
    /// <param name="localRay">The intersecting ray, transformed to object space.</param>
    /// <returns>The intersection points of the ray with the concrete shape, if any.</returns>
    protected abstract Intersection[] LocalIntersect(Ray localRay);
}