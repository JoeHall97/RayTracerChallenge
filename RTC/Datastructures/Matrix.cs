using RTC.Helpers;

namespace RTC.Datastructures;

public class Matrix
{
    public Matrix(uint size = 4)
    {
        Values = new double[size, size];
    }

    public Matrix(double[,] values)
    {
        Values = values;
    }

    public double[,] Values { get; }

    private bool Equals(Matrix other)
    {
        return this == other;
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != GetType()) return false;
        return Equals((Matrix)obj);
    }

    public override int GetHashCode()
    {
        return Values.GetHashCode();
    }

    public static bool operator ==(Matrix lhs, Matrix rhs)
    {
        if (lhs.Values.Rank != rhs.Values.Rank) return false;
        if (lhs.Values.Length == 0) return true;

        for (var i = 0; i < lhs.Values.GetLength(0); i++)
        for (var j = 0; j < lhs.Values.GetLength(1); j++)
            if (!lhs.Values[i, j].IsEqual(rhs.Values[i, j]))
                return false;

        return true;
    }

    public static Matrix operator *(Matrix lhs, Matrix rhs)
    {
        if (lhs.Values.Rank != rhs.Values.Rank) throw new ArgumentException("Matrices must have the same rank.");

        var res = new Matrix((uint)lhs.Values.GetLength(0));
        for (var i = 0; i < res.Values.GetLength(0); i++)
        for (var j = 0; j < res.Values.GetLength(1); j++)
            res[i, j] = 
    }

    public static bool operator !=(Matrix lhs, Matrix rhs)
    {
        return !(lhs == rhs);
    }
}