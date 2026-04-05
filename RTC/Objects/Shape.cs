using RTC.Datastructures;

namespace RTC.Objects;

public abstract class Shape
{
    public Matrix Transformation { get; set; } = Matrix.IdentityMatrix(4);
}