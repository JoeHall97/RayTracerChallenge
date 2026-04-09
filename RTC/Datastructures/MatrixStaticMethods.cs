namespace RTC.Datastructures;

public partial struct Matrix
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

    /// <summary>
    /// Creates a 4x4 matrix that transforms the world relative to your eye.
    /// </summary>
    /// <param name="from">Where you want your eye to be in the scene.</param>
    /// <param name="to">The point in the scene you want to look at.</param>
    /// <param name="up">The vector indicating which direction is up.</param>
    /// <returns>The created view transformation matrix.</returns>
    public static Matrix ViewTransform(Vec4 from, Vec4 to, Vec4 up)
    {
        var forward = (to - from).Normalise();
        var upNormal = up.Normalise();
        var left = forward.Cross(upNormal);
        var trueUp = left.Cross(forward);
        
        var orientation = new Matrix(new[,]
            {
                { left.X, left.Y, left.Z, 0 },
                { trueUp.X, trueUp.Y, trueUp.Z, 0 },
                { -forward.X, -forward.Y, -forward.Z, 0 },
                { 0, 0, 0, 1 }
            }
        );
        
        return orientation * TranslationMatrix(-from.X, -from.Y, -from.Z);
    }
}