namespace RTC.Objects;

/// <summary>
/// A colour consisting of red, green, and blue values.
/// </summary>
/// <param name="red"></param>
/// <param name="green"></param>
/// <param name="blue"></param>
public struct Colour(float red, float green, float blue)
{
    public float Red { get; set; } = red;
    public float Green { get; set; } = green;
    public float Blue { get; set; } = blue;
    
    public static Colour operator+(Colour lhs, Colour rhs) 
        => new(lhs.Red + rhs.Red, lhs.Green + rhs.Green, lhs.Blue + rhs.Blue);
    public static Colour operator-(Colour lhs, Colour rhs)
        => new(lhs.Red - rhs.Red, lhs.Green - rhs.Green, lhs.Blue - rhs.Blue);
    public static Colour operator*(Colour lhs, float rhs)
        => new(lhs.Red * rhs, lhs.Green * rhs, lhs.Blue * rhs);
    public static Colour operator*(Colour lhs, Colour rhs)
        => new(lhs.Red * rhs.Red, lhs.Green * rhs.Green, lhs.Blue * rhs.Blue);
}