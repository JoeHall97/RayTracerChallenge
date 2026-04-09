using RTC.Datastructures;
using RTC.Objects;
using RTC.Helpers;

namespace RTC.Primitives;

/// <summary>
/// Precomputed values for intersection calculations.
/// </summary>
public readonly struct Precompute
{
    public Precompute(Intersection i, Ray r) 
    {
        T = i.T;
        Shape = i.Shape;
        Point = r.Position(T);
        EyeVec = -r.Direction;
        NormalVec = Shape.NormalAt(Point);

        if (NormalVec.Dot(EyeVec) < 0)
        {
            Inside = true;
            NormalVec = -NormalVec;
        }
        else
        {
            Inside = false;
        }
        
        OverPoint = Point + NormalVec * Helper.Epsilon;
    }
    
    /// <summary>
    /// The time/tick the intersection occurred.
    /// </summary>
    public double T { get; } 
    /// <summary>
    /// The shape that was intersected.
    /// </summary>
    public Shape Shape { get; } 
    /// <summary>
    /// The point of intersection.
    /// </summary>
    public Vec4 Point { get; } 
    /// <summary>
    /// The vector from the eye to the intersection point.
    /// </summary>
    public Vec4 EyeVec { get; } 
    /// <summary>
    /// The normal vector at the intersection point.
    /// </summary>
    public Vec4 NormalVec { get; } 
    /// <summary>
    /// <c>true</c> if the intersection point is inside the shape, <c>false</c> otherwise.
    /// </summary>
    public bool Inside { get; }
    /// <summary>
    /// The vector from the intersection point to the point of reflection.
    /// </summary>
    public Vec4 OverPoint { get; }
    
    public override string ToString() => $"Precompute(t: {T}, shape: {Shape}, point: {Point}, eyeVec: {EyeVec}, normalVec: {NormalVec})";
}