using RTC.Helpers;

namespace RTC.Primitives;

/// <summary>
/// A colour consisting of red, green, and blue values.
/// </summary>
/// <param name="red"></param>
/// <param name="green"></param>
/// <param name="blue"></param>
public struct Colour(double red, double green, double blue) : IEquatable<Colour>
{
    public double Red { get; set; } = red;
    public double Green { get; set; } = green;
    public double Blue { get; set; } = blue;

    public static Colour operator +(Colour lhs, Colour rhs)
        => new(lhs.Red + rhs.Red, lhs.Green + rhs.Green, lhs.Blue + rhs.Blue);

    public static Colour operator -(Colour lhs, Colour rhs)
        => new(lhs.Red - rhs.Red, lhs.Green - rhs.Green, lhs.Blue - rhs.Blue);

    public static Colour operator *(Colour lhs, double rhs)
        => new(lhs.Red * rhs, lhs.Green * rhs, lhs.Blue * rhs);

    public static Colour operator *(Colour lhs, Colour rhs)
        => new(lhs.Red * rhs.Red, lhs.Green * rhs.Green, lhs.Blue * rhs.Blue);

    public static bool operator ==(Colour lhs, Colour rhs) => lhs.Equals(rhs);
    public static bool operator !=(Colour lhs, Colour rhs) => !lhs.Equals(rhs);

    public static Colour Black => new Colour(0, 0, 0);
    public static Colour White => new Colour(1, 1, 1);

    public bool Equals(Colour other)
    {
        return Red.IsEqual(other.Red) && Green.IsEqual(other.Green) && Blue.IsEqual(other.Blue);
    }

    public override bool Equals(object? obj)
    {
        return obj is Colour other && Equals(other);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Red, Green, Blue);
    }

    public override string ToString()
    {
        return $"Colour: ({Red}, {Green}, {Blue})";
    }
}