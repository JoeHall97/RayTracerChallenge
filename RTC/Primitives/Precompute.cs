using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;

namespace RTC.Primitives;

/// <summary>
///     Precomputed values for intersection calculations.
/// </summary>
public readonly struct Precompute
{
    public Precompute(Intersection hit, Ray r)
    {
        T = hit.T;
        Shape = hit.Shape;
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
        UnderPoint = Point - NormalVec * Helper.Epsilon;
        ReflectVec = r.Direction.Reflect(NormalVec);
        N1 = 0;
        N2 = 0;
    }

    public Precompute(Intersection hit, Ray r, IntersectionSet xs) : this(hit, r)
    {
        var containers = new List<Shape>();

        foreach (var intersection in xs.Values)
        {
            if (intersection.Equals(hit))
            {
                if (containers.Count == 0)
                    N1 = 1;
                else
                    N1 = containers.Last().Material.RefractiveIndex;
            }

            if (containers.Contains(intersection.Shape))
                containers.Remove(intersection.Shape);
            else
                containers.Add(intersection.Shape);

            if (!intersection.Equals(hit)) continue;

            if (containers.Count == 0)
                N2 = 1;
            else
                N2 = containers.Last().Material.RefractiveIndex;
            break;
        }
    }

    /// <summary>
    ///     The shape that was intersected.
    /// </summary>
    public Shape Shape { get; }

    /// <summary>
    ///     The point of intersection.
    /// </summary>
    public Vec4 Point { get; }

    /// <summary>
    ///     The vector from the eye to the intersection point.
    /// </summary>
    public Vec4 EyeVec { get; }

    /// <summary>
    ///     The normal vector at the intersection point.
    /// </summary>
    public Vec4 NormalVec { get; }

    /// <summary>
    ///     The vector from the intersection point to the point of reflection.
    /// </summary>
    public Vec4 ReflectVec { get; }

    /// <summary>
    ///     The point which lies above the intersected surface.
    /// </summary>
    public Vec4 OverPoint { get; }

    /// <summary>
    ///     The point which lies beneath the intersected surface.
    /// </summary>
    public Vec4 UnderPoint { get; }

    /// <summary>
    ///     The time/tick the intersection occurred.
    /// </summary>
    public double T { get; }

    /// <summary>
    ///     The refractive index of the material being exited by the ray-object intersection.
    /// </summary>
    public double N1 { get; }

    /// <summary>
    ///     The refractive index of the material being entered by the ray-object intersection.
    /// </summary>
    public double N2 { get; }

    /// <summary>
    ///     <c>true</c> if the intersection point is inside the shape, <c>false</c> otherwise.
    /// </summary>
    public bool Inside { get; }

    public override string ToString()
    {
        return $"Precompute(t: {T}, shape: {Shape}, point: {Point}, eyeVec: {EyeVec}, normalVec: {NormalVec})";
    }

    /// <summary>
    ///     Calculates the Schlick approximation of the reflectance, representing what fraction of the light is reflected.
    /// </summary>
    /// <returns>A value between 0 and 1 representing the fraction of light reflected.</returns>
    public double Schlick()
    {
        // find the cosine of the angle between the eye and the normal vectors
        var cos = EyeVec.Dot(NormalVec);

        // total internal reflection can only occur if n1 > n2
        if (N1 > N2)
        {
            var n = N1 / N2;
            var sin2T = n * n * (1 - cos * cos);
            if (sin2T > 1)
                return 1;

            // compute cosine of thetaT using trig identity
            var cosT = Math.Sqrt(1 - sin2T);
            // when n1 > n2, use cos(thetaT) instead
            cos = cosT;
        }

        var r0 = Math.Pow((N1 - N2) / (N1 + N2), 2);
        return r0 + (1 - r0) * Math.Pow(1 - cos, 5);
    }
}