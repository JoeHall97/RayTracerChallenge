using System.Text;
using RTC.Helpers;

namespace RTC.Datastructures;

/// <summary>
/// A Matrix of doubles.
/// </summary>
public partial class Matrix
{
    /// <summary>
    /// Creates a new matrix of the given size.
    /// </summary>
    /// <param name="size">The size of the matrix. Defaults to 4.</param>
    public Matrix(uint size = 4)
    {
        Values = new double[size, size];
    }

    /// <summary>
    /// Creates a new matrix from the given values.
    /// </summary>
    /// <param name="values"></param>
    public Matrix(double[,] values)
    {
        Values = values;
    }

    /// <summary>
    /// The size of the matrix.
    /// </summary>
    public uint Size => (uint)Values.GetLength(0);

    /// <summary>
    /// Whether the matrix is invertible or not.
    /// </summary>
    public bool Invertible => Determinant() != 0;

    /// <summary>
    /// The values of the matrix.
    /// </summary>
    private double[,] Values { get; }

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

    /// <summary>
    /// Sets the value of the matrix at the given row and column. Will throw an exception if the row or column is out of bounds.
    /// </summary>
    /// <param name="row">The row index of the matrix.</param>
    /// <param name="column">The column index of the matrix.</param>
    /// <param name="value">The value to set at the specified position.</param>
    public void Set(uint row, uint column, double value)
    {
        Values[row, column] = value;
    }

    /// <summary>
    /// Gets the value of the matrix at the given row and column. Will throw an exception if the row or column is out of bounds.
    /// </summary>
    /// <param name="row">The row index of the matrix.</param>
    /// <param name="column">The column index of the matrix.</param>
    /// <returns>The value at the specified position.</returns>
    public double Get(uint row, uint column)
    {
        return Values[row, column];
    }

    /// <summary>
    /// Gets the transpose of the matrix.
    /// </summary>
    /// <returns>The transpose of the matrix.</returns>
    public Matrix Transpose()
    {
        var transposed = new Matrix(Size);
        for (uint row = 0; row < Size; row++)
        for (uint column = 0; column < Size; column++)
            transposed.Set(column, row, Get(row, column));

        return transposed;
    }

    /// <summary>
    /// Gets the determinant of the matrix.
    /// </summary>
    /// <returns>The determinant of the matrix.</returns>
    /// <exception cref="ArgumentException">Throws if the size of the Matrix is less than 2.</exception>
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

    /// <summary>
    /// Gets the given submatrix of the matrix.
    /// </summary>
    /// <param name="row">The row to exclude.</param>
    /// <param name="column">The column to exclude.</param>
    /// <returns>The submatrix.</returns>
    /// <exception cref="ArgumentException">Throws if the size of the Matrix is less than 2.</exception>
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

    /// <summary>
    /// Gets the minor of the matrix.
    /// </summary>
    /// <param name="row"></param>
    /// <param name="column"></param>
    /// <returns>The minor value.</returns>
    public double Minor(uint row, uint column)
    {
        return SubMatrix(row, column).Determinant();
    }

    /// <summary>
    /// Gets the cofactor of the matrix.
    /// </summary>
    /// <param name="row"></param>
    /// <param name="column"></param>
    /// <returns>The cofactor value.</returns>
    public double Cofactor(uint row, uint column)
    {
        return (row + column) % 2 == 0 ? Minor(row, column) : -Minor(row, column);
    }

    /// <summary>
    /// Gets the inverse of the matrix.
    /// </summary>
    /// <returns>The inverse matrix.</returns>
    /// <exception cref="ArgumentException">Throws if the matrix is not invertible.</exception>
    public Matrix Inverse()
    {
        if (!Invertible) throw new ArgumentException("Matrix is not invertible.");

        var res = new Matrix(Size);

        for (uint i = 0; i < Size; i++)
        for (uint j = 0; j < Size; j++)
            res.Set(j, i, Cofactor(i, j) / Determinant());

        return res;
    }
    
    /// <summary>
    /// Rotates the matrix around the x-axis.
    /// </summary>
    /// <param name="r">The rotation angle in radians.</param>
    /// <returns>The rotated matrix.</returns>
    public Matrix RotateX(double r)
    {
        return this * RotationXMatrix(r);
    }

    /// <summary>
    /// Rotates the matrix around the y-axis.
    /// </summary>
    /// <param name="r">The rotation angle in radians.</param>
    /// <returns>The rotated matrix.</returns>
    public Matrix RotateY(double r)
    {
        return this * RotationYMatrix(r);
    }

    /// <summary>
    /// Rotates the matrix around the z-axis.
    /// </summary>
    /// <param name="r">The rotation angle in radians.</param>
    /// <returns>The rotated matrix.</returns>
    public Matrix RotateZ(double r)
    {
        return this * RotationZMatrix(r);
    }

    /// <summary>
    /// Scales the matrix.
    /// </summary>
    /// <param name="x">The scaling factor for the x-axis.</param>
    /// <param name="y">The scaling factor for the y-axis.</param>
    /// <param name="z">The scaling factor for the z-axis.</param>
    /// <returns>The scaled matrix.</returns>
    public Matrix Scale(double x, double y, double z)
    {
        return this * ScalingMatrix(x, y, z);
    }

    /// <summary>
    /// Translates the matrix.
    /// </summary>
    /// <param name="x">The translation amount along the x-axis.</param>
    /// <param name="y">The translation amount along the y-axis.</param>
    /// <param name="z">The translation amount along the z-axis.</param>
    /// <returns>The translated matrix.</returns>
    public Matrix Translate(double x, double y, double z)
    {
        return this * TranslationMatrix(x, y, z);
    }

    /// <summary>
    /// Shears the matrix.
    /// </summary>
    /// <param name="xy">Shearing factor for the xy plane.</param>
    /// <param name="xz">Shearing factor for the xz plane.</param>
    /// <param name="yx">Shearing factor for the yx plane.</param>
    /// <param name="yz">Shearing factor for the yz plane.</param>
    /// <param name="zx">Shearing factor for the zx plane.</param>
    /// <param name="zy">Shearing factor for the zy plane.</param>
    /// <returns>The sheared matrix.</returns>
    public Matrix Shear(double xy, double xz, double yx, double yz, double zx, double zy)
    {
        return this * ShearingMatrix(xy, xz, yx, yz, zx, zy);
    }

    /// <summary>
    /// Multiples the row of the left matrix with the column of the right matrix.
    /// </summary>
    /// <param name="lhs">The left matrix.</param>
    /// <param name="rhs">The right matrix.</param>
    /// <param name="row">The row of the left matrix.</param>
    /// <param name="column">The column of the right matrix.</param>
    /// <returns>The result of the multiplication.</returns>
    /// <exception cref="ArgumentException">Thrown if the matrices are different sizes.</exception>
    private static double MultipleRowColumn(Matrix lhs, Matrix rhs, uint row, uint column)
    {
        if (lhs.Size != rhs.Size) throw new ArgumentException("Matrices must be the same size.");

        double res = 0;
        for (uint i = 0; i < lhs.Size; i++) res += lhs.Get(row, i) * rhs.Get(i, column);
        return res;
    }
}