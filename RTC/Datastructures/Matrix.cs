using System.Text;
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

    private double[,] Values { get; }

    public uint Size => (uint)Values.GetLength(0);

    public bool Invertible => Determinant() != 0;

    private bool Equals(Matrix other)
    {
        return this == other;
    }

    public override string ToString()
    {
        var sb = new StringBuilder();
        for (var i = 0; i < Values.GetLength(0); i++)
        {
            sb.Append("{ ");

            var len = Values.GetLength(1);
            for (var j = 0; j < len; j++)
            {
                sb.Append(Values[i, j]);
                if (j < len - 1) sb.Append(", ");
            }

            sb.AppendLine(" }");
        }

        return sb.ToString();
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
        for (uint i = 0; i < res.Values.GetLength(0); i++)
        for (uint j = 0; j < res.Values.GetLength(1); j++)
            res.Set(i, j, MultipleRowColumn(lhs, rhs, i, j));

        return res;
    }

    public static Vec4 operator *(Matrix lhs, Vec4 rhs)
    {
        if (lhs.Size != 4) throw new ArgumentException("Matrix and vector dimensions must match.");

        return new Vec4
        {
            X = lhs.Get(0, 0) * rhs.X + lhs.Get(0, 1) * rhs.Y + lhs.Get(0, 2) * rhs.Z +
                lhs.Get(0, 3) * rhs.W,
            Y = lhs.Get(1, 0) * rhs.X + lhs.Get(1, 1) * rhs.Y + lhs.Get(1, 2) * rhs.Z +
                lhs.Get(1, 3) * rhs.W,
            Z = lhs.Get(2, 0) * rhs.X + lhs.Get(2, 1) * rhs.Y + lhs.Get(2, 2) * rhs.Z +
                lhs.Get(2, 3) * rhs.W,
            W = lhs.Get(3, 0) * rhs.X + lhs.Get(3, 1) * rhs.Y + lhs.Get(3, 2) * rhs.Z +
                lhs.Get(3, 3) * rhs.W
        };
    }

    public static bool operator !=(Matrix lhs, Matrix rhs)
    {
        return !(lhs == rhs);
    }

    public void Set(uint row, uint column, double value)
    {
        Values[row, column] = value;
    }

    public double Get(uint row, uint column)
    {
        return Values[row, column];
    }

    public Matrix Transpose()
    {
        var transposed = new Matrix(Size);
        for (uint row = 0; row < Size; row++)
        for (uint column = 0; column < Size; column++)
            transposed.Set(column, row, Get(row, column));

        return transposed;
    }

    public double Determinant()
    {
        if (Size < 2) throw new ArgumentException("Matrix must have at least 2 rows and columns.");
        if (Size == 2)
            return Get(0, 0) * Get(1, 1) - Get(0, 1) * Get(1, 0);

        double determinant = 0;
        for (uint column = 0; column < Size; column++)
            determinant += Cofactor(0, column) * Get(0, column);
        return determinant;
    }

    public Matrix SubMatrix(uint row, uint column)
    {
        if (Size <= 1) throw new ArgumentException("Matrix too small to subdivide.");
        var res = new Matrix(Size - 1);

        for (uint i = 0; i < Size; i++)
        {
            if (i == row) continue;
            for (uint j = 0; j < Size; j++)
            {
                if (j == column) continue;
                res.Set(i < row ? i : i - 1, j < column ? j : j - 1, Get(i, j));
            }
        }

        return res;
    }

    public double Minor(uint row, uint column)
    {
        return SubMatrix(row, column).Determinant();
    }

    public double Cofactor(uint row, uint column)
    {
        return (row + column) % 2 == 0 ? Minor(row, column) : -Minor(row, column);
    }

    public Matrix Inverse()
    {
        if (!Invertible) throw new ArgumentException("Matrix is not invertible.");

        var res = new Matrix(Size);

        for (uint i = 0; i < Size; i++)
        for (uint j = 0; j < Size; j++)
            res.Set(j, i, Cofactor(i, j) / Determinant());

        return res;
    }

    public static Matrix IdentityMatrix(uint size)
    {
        var identity = new Matrix(size);
        for (uint i = 0; i < size; i++) identity.Set(i, i, 1);
        return identity;
    }

    private static double MultipleRowColumn(Matrix lhs, Matrix rhs, uint row, uint column)
    {
        if (lhs.Values.Rank != rhs.Values.Rank) throw new ArgumentException("Matrices must be multiplicable.");

        double res = 0;
        for (uint i = 0; i < lhs.Size; i++) res += lhs.Get(row, i) * rhs.Get(i, column);
        return res;
    }
}