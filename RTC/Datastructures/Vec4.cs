using System.Diagnostics.CodeAnalysis;
using RTC.Helpers;

namespace RTC.Datastructures;

public struct Vec4(double x, double y, double z, double w) : IEquatable<Vec4>
{
    public double X { get; set; } = x;
    public double Y { get; set; } = y;
    public double Z { get; set; } = z;
    public double W { get; set; } = w;

    public bool IsPoint => W.IsEqual(1);
    public bool IsVector => W.IsEqual(0);
    public double Magnitude => MathF.Sqrt((float)(X * X + Y * Y + Z * Z + W * W));
    public Vec4 Normalised => new(X / Magnitude, Y / Magnitude, Z / Magnitude, W / Magnitude);

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

    public static Vec4 Point(double x, double y, double z)
    {
        return new Vec4(x, y, z, 1d);
    }

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

    public double Dot(Vec4 other)
    {
        return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
    }

    public Vec4 Cross(Vec4 other)
    {
        return Vector(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
    }
}