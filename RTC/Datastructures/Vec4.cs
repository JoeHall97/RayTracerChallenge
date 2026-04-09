using System.Diagnostics.CodeAnalysis;
using RTC.Helpers;

namespace RTC.Datastructures;

/// <summary>
/// A 4-dimensional tuple of doubles.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <param name="w"></param>
public struct Vec4(double x, double y, double z, double w) : IEquatable<Vec4>
{
    public double X { get; set; } = x;
    public double Y { get; set; } = y;
    public double Z { get; set; } = z;
    public double W { get; set; } = w;

    /// <summary>
    /// Whether the tuple is a point or not.
    /// </summary>
    public bool IsPoint => W.IsEqual(1);
    /// <summary>
    /// Whether the tuple is a vector or not.
    /// </summary>
    public bool IsVector => W.IsEqual(0);
    /// <summary>
    /// The magnitude of the tuple.
    /// </summary>
    public double Magnitude => MathF.Sqrt((float)(X * X + Y * Y + Z * Z + W * W));

    public static Vec4 operator -(Vec4 lhs)
    {
        return new Vec4(-lhs.X, -lhs.Y, -lhs.Z, -lhs.W);
    }

    public static Vec4 operator +(Vec4 lhs, Vec4 rhs)
    {
        return new Vec4(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z, Math.Max(lhs.W, rhs.W));
    }

    public static Vec4 operator -(Vec4 lhs, Vec4 rhs)
    {
        return new Vec4(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z, lhs.W - rhs.W);
    }

    public static Vec4 operator *(Vec4 lhs, double rhs)
    {
        return new Vec4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
    }

    public static Vec4 operator /(Vec4 lhs, double rhs)
    {
        return new Vec4(lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs, lhs.W / rhs);
    }

    public static bool operator ==(Vec4 left, Vec4 right)
    {
        return left.Equals(right);
    }

    public static bool operator !=(Vec4 left, Vec4 right)
    {
        return !(left == right);
    }

    /// <summary>
    /// Creates a point from the given coordinates.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    /// <returns>The created point.</returns>
    public static Vec4 Point(double x, double y, double z)
    {
        return new Vec4(x, y, z, 1d);
    }

    /// <summary>
    /// Creates a vector from the given coordinates.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    /// <returns>The created vector.</returns>
    public static Vec4 Vector(double x, double y, double z)
    {
        return new Vec4(x, y, z, 0d);
    }

    public override string ToString()
    {
        return $"({X}, {Y}, {Z}, {W})";
    }

    public override bool Equals([NotNullWhen(true)] object? obj)
    {
        return obj is Vec4 rhs && Equals(rhs);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(X, Y, Z, W);
    }

    public bool Equals(Vec4 other)
    {
        return W.IsEqual(other.W) && X.IsEqual(other.X) && Y.IsEqual(other.Y) && Z.IsEqual(other.Z);
    }

    /// <summary>
    /// Calculates the dot product of the two tuples.
    /// </summary>
    /// <param name="other">The other tuple to calculate the dot product with.</param>
    /// <returns>The dot product of the two tuples.</returns>
    public double Dot(Vec4 other)
    {
        return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
    }

    /// <summary>
    /// Calculates the cross-product of the two tuples.
    /// </summary>
    /// <param name="other">The other tuple to calculate the cross-product with.</param>
    /// <returns>The cross-product of the two tuples.</returns>
    public Vec4 Cross(Vec4 other)
    {
        return Vector(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="normal"></param>
    /// <returns></returns>
    public Vec4 Reflect(Vec4 normal)
    {
        return this - normal * 2 * Dot(normal);
    }
    
    /// <summary>
    /// Returns the normalised version of the tuple.
    /// </summary>
    public Vec4 Normalise() => new(X / Magnitude, Y / Magnitude, Z / Magnitude, W / Magnitude);
}