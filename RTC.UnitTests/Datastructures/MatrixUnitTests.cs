using RTC.Datastructures;
using Shouldly;

namespace RTC.UnitTests.Datastructures;

public class MatrixUnitTests
{
    [Fact]
    public void TestMatrixEquality()
    {
        var a = new Matrix(new double[,] { { 1, 2 }, { 3, 4 } });
        var b = new Matrix(new double[,] { { 1, 2 }, { 3, 4 } });
        a.ShouldBe(b);

        var c = new Matrix(new double[,] { { 1, 2 }, { 3, 4 } });
        var d = new Matrix(new double[,] { { 1, 2 }, { 5, 4 } });
        c.ShouldNotBe(d);
    }
}