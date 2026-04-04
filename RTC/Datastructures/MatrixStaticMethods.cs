namespace RTC.Datastructures;

public partial class Matrix
{
    /// <summary>
    /// Creates an identity matrix of the given size.
    /// </summary>
    /// <param name="size">The size of the identity matrix.</param>
    /// <returns>The identity matrix.</returns>
    public static Matrix IdentityMatrix(uint size)
    {
        var identity = new Matrix(size);
        for (uint i = 0; i < size; i++) identity.Set(i, i, 1);
        return identity;
    }

    /// <summary>
    /// Creates a 4x4 translation matrix.
    /// </summary>
    /// <param name="x">The x value of the translation matrix.</param>
    /// <param name="y">The y value of the translation matrix.</param>
    /// <param name="z">The z value of the translation matrix.</param>
    /// <returns>The created translation matrix.</returns>
    public static Matrix TranslationMatrix(double x, double y, double z)
    {
        return new Matrix(new[,]
        {
            { 1, 0, 0, x },
            { 0, 1, 0, y },
            { 0, 0, 1, z },
            { 0, 0, 0, 1 }
        });
    }

    /// <summary>
    /// Creates a 4x4 scaling matrix.
    /// </summary>
    /// <param name="x">The x value of the scaling matrix.</param>
    /// <param name="y">The y value of the scaling matrix.</param>
    /// <param name="z">The z value of the scaling matrix.</param>
    /// <returns>The created scaling matrix.</returns>
    public static Matrix ScalingMatrix(double x, double y, double z)
    {
        return new Matrix(new[,]
        {
            { x, 0, 0, 0 },
            { 0, y, 0, 0 },
            { 0, 0, z, 0 },
            { 0, 0, 0, 1 }
        });
    }
    
    /// <summary>
    /// Creates a 4x4 rotation matrix around the x-axis.
    /// </summary>
    /// <param name="r">The radians of the rotation.</param>
    /// <returns>The created rotation matrix.</returns>
    public static Matrix RotationXMatrix(double r)
    {
        return new Matrix(new[,]
        {
            { 1, 0, 0, 0 },
            { 0, Math.Cos(r), -Math.Sin(r), 0 },
            { 0, Math.Sin(r), Math.Cos(r), 0 },
            { 0, 0, 0, 1 }
        });
    }

    /// <summary>
    /// Creates a 4x4 rotation matrix around the y-axis.
    /// </summary>
    /// <param name="r">The radians of the rotation.</param>
    /// <returns>The created rotation matrix.</returns>
    public static Matrix RotationYMatrix(double r)
    {
        return new Matrix(new[,]
        {
            { Math.Cos(r), 0, Math.Sin(r), 0 },
            { 0, 1, 0, 0 },
            { -Math.Sin(r), 0, Math.Cos(r), 0 },
            { 0, 0, 0, 1 }
        });
    }

    /// <summary>
    /// Creates a 4x4 rotation matrix around the z-axis.
    /// </summary>
    /// <param name="r">The radians of the rotation.</param>
    /// <returns>The created rotation matrix.</returns>
    public static Matrix RotationZMatrix(double r)
    {
        return new Matrix(new[,]
        {
            { Math.Cos(r), -Math.Sin(r), 0, 0 },
            { Math.Sin(r), Math.Cos(r), 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 }
        });
    }
    
    /// <summary>
    /// Creates a 4x4 shearing matrix.
    /// </summary>
    /// <param name="xy"></param>
    /// <param name="xz"></param>
    /// <param name="yx"></param>
    /// <param name="yz"></param>
    /// <param name="zx"></param>
    /// <param name="zy"></param>
    /// <returns>The created shearing matrix.</returns>
    public static Matrix ShearingMatrix(double xy, double xz, double yx, double yz, double zx, double zy)
    {
        return new Matrix(new[,]
            {
                { 1, xy, xz, 0 },
                { yx, 1, yz, 0 },
                { zx, zy, 1, 0 },
                { 0, 0, 0, 1 }
            }
        );
    }
}