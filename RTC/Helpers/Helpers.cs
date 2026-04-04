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
}