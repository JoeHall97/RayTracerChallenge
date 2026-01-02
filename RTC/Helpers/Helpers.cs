namespace RTC.Helpers;

public static class Helpers
{
    public static bool IsEqual(this double x, double y)
    {
        const float epsilon = 0.00001f;
        return Math.Abs(x - y) < epsilon;
    }
}