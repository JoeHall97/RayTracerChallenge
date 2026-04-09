using RTC.Primitives;

namespace RTC.Helpers;

/// <summary>
/// Helper methods.
/// </summary>
public static class Helpers
{
    /// <summary>
    /// Checks if two doubles are equal, with a tolerance of 0.00001.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns><c>true</c> if the two doubles are equal, else <c>false</c></returns>
    public static bool IsEqual(this double x, double y)
    {
        const float epsilon = 0.00001f;
        return Math.Abs(x - y) < epsilon;
    }
    
    /// <summary>
    /// Checks if two floats are equal, with a tolerance of 0.00001.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns><c>true</c> if the two floats are equal, else <c>false</c></returns>
    public static bool IsEqual(this float x, float y)
    {
        const float epsilon = 0.00001f;
        return Math.Abs(x - y) < epsilon;
    }

    /// <summary>
    /// Returns the hit intersection.
    /// </summary>
    /// <param name="intersections"></param>
    /// <returns></returns>
    public static Intersection? Hit(this Intersection[] intersections)
    {
        if (intersections.Length == 0) return null;
        if (intersections[0].T > 0) return intersections[0];
        if (intersections.Length < 1 || intersections[1].T < 0) return null;
        return intersections[1];
    } 
}