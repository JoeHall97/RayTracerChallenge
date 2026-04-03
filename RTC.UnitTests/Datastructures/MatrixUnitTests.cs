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

    [Fact]
    public void TestMatrixMultiplication()
    {
        var a = new Matrix(new double[,] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 8, 7, 6 }, { 5, 4, 3, 2 } });
        var b = new Matrix(new double[,] { { -2, 1, 2, 3 }, { 3, 2, 1, -1 }, { 4, 3, 6, 5 }, { 1, 2, 7, 8 } });
        var c = new Matrix(new double[,]
            { { 20, 22, 50, 48 }, { 44, 54, 114, 108 }, { 40, 58, 110, 102 }, { 16, 26, 46, 42 } });
        (a * b).ShouldBe(c);
    }

    [Fact]
    public void TestMatrixMultiplicationWithTuple()
    {
        var a = new Matrix(new double[,] { { 1, 2, 3, 4 }, { 2, 4, 4, 2 }, { 8, 6, 4, 1 }, { 0, 0, 0, 1 } });
        var b = new Vec4(1, 2, 3, 1);
        var c = new Vec4(18, 24, 33, 1);
        (a * b).ShouldBe(c);
    }

    [Fact]
    public void TestMatrixMultiplicationWithIdentity()
    {
        var a = new Matrix(new double[,] { { 0, 1, 2, 4 }, { 2, 4, 4, 2 }, { 8, 6, 4, 1 }, { 0, 0, 0, 1 } });
        var b = Matrix.IdentityMatrix(4);
        (a * b).ShouldBe(a);
    }

    [Fact]
    public void TestIdentityMatrixMultiplicationWithTuple()
    {
        var a = Matrix.IdentityMatrix(4);
        var b = new Vec4(1, 2, 3, 4);
        (a * b).ShouldBe(b);
    }

    [Fact]
    public void TestTransposingMatrix()
    {
        var a = new Matrix(new double[,] { { 0, 9, 3, 0 }, { 9, 8, 0, 8 }, { 1, 8, 5, 3 }, { 0, 0, 5, 8 } });
        var transposedA = new Matrix(new double[,]
            { { 0, 9, 1, 0 }, { 9, 8, 8, 0 }, { 3, 0, 5, 5 }, { 0, 8, 3, 8 } });
        a.Transpose().ShouldBe(transposedA);
    }

    [Fact]
    public void TestTransposingIdentityMatrix()
    {
        var a = Matrix.IdentityMatrix(4);
        a.Transpose().ShouldBe(a);
    }

    [Fact]
    public void TestDeterminantOf2X2Matrix()
    {
        var a = new Matrix(new double[,] { { 1, 5 }, { -3, 2 } });
        a.Determinant().ShouldBe(17);
    }

    [Fact]
    public void TestSubMatrixOf3X3Matrix()
    {
        var a = new Matrix(new double[,] { { 1, 5, 0 }, { -3, 2, 7 }, { 0, 6, -3 } });
        var subMatrix = a.SubMatrix(0, 2);
        subMatrix.ShouldBe(new Matrix(new double[,] { { -3, 2 }, { 0, 6 } }));
    }

    [Fact]
    public void TestSubMatrixOf4X4Matrix()
    {
        var a = new Matrix(new double[,] { { -6, 1, 1, 6 }, { -8, 5, 8, 6 }, { -1, 0, 8, 2 }, { -7, 1, -1, 1 } });
        var subMatrix = a.SubMatrix(2, 1);
        subMatrix.ShouldBe(new Matrix(new double[,] { { -6, 1, 6 }, { -8, 8, 6 }, { -7, -1, 1 } }));
    }

    [Fact]
    public void TestMinorOf3X3Matrix()
    {
        var a = new Matrix(new double[,] { { 3, 5, 0 }, { 2, -1, -7 }, { 6, -1, 5 } });
        var b = a.SubMatrix(1, 0);
        b.Determinant().ShouldBe(25);
        a.Minor(1, 0).ShouldBe(25);
    }

    [Fact]
    public void TestCofactorOf3X3Matrix()
    {
        var a = new Matrix(new double[,] { { 3, 5, 0 }, { 2, -1, -7 }, { 6, -1, 5 } });

        a.Minor(0, 0).ShouldBe(-12);
        a.Cofactor(0, 0).ShouldBe(-12);

        a.Minor(1, 0).ShouldBe(25);
        a.Cofactor(1, 0).ShouldBe(-25);
    }

    [Fact]
    public void TestDeterminantOf3X3Matrix()
    {
        var a = new Matrix(new double[,] { { 1, 2, 6 }, { -5, 8, -4 }, { 2, 6, 4 } });
        a.Cofactor(0, 0).ShouldBe(56);
        a.Cofactor(0, 1).ShouldBe(12);
        a.Cofactor(0, 2).ShouldBe(-46);
        a.Determinant().ShouldBe(-196);
    }

    [Fact]
    public void TestDeterminantOf4X4Matrix()
    {
        var a = new Matrix(new double[,] { { -2, -8, 3, 5 }, { -3, 1, 7, 3 }, { 1, 2, -9, 6 }, { -6, 7, 7, -9 } });
        a.Cofactor(0, 0).ShouldBe(690);
        a.Cofactor(0, 1).ShouldBe(447);
        a.Cofactor(0, 2).ShouldBe(210);
        a.Cofactor(0, 3).ShouldBe(51);
        a.Determinant().ShouldBe(-4071);
    }

    [Fact]
    public void TestInvertibleMatrix()
    {
        var a = new Matrix(new double[,] { { 6, 4, 4, 4 }, { 5, 5, 7, 6 }, { 4, -9, 3, -7 }, { 9, 1, 7, -6 } });
        a.Determinant().ShouldBe(-2120);
        a.Invertible.ShouldBeTrue();
    }

    [Fact]
    public void TestNonInvertibleMatrix()
    {
        var a = new Matrix(new double[,] { { -4, 2, -2, -3 }, { 9, 6, 2, 6 }, { 0, -5, 1, -5 }, { 0, 0, 0, 0 } });
        a.Determinant().ShouldBe(0);
        a.Invertible.ShouldBeFalse();
    }

    [Fact]
    public void TestInverseOfInvertibleMatrix()
    {
        var a = new Matrix(new double[,] { { -5, 2, 6, -8 }, { 1, -5, 1, 8 }, { 7, 7, -6, -7 }, { 1, -3, 7, 4 } });
        var b = a.Inverse();
        a.Determinant().ShouldBe(532);
        a.Cofactor(2, 3).ShouldBe(-160);
        b.Get(3, 2).ShouldBe(-160d / 532d);
        a.Cofactor(3, 2).ShouldBe(105);
        b.Get(2, 3).ShouldBe(105d / 532d);

        var expectedB = new Matrix(new[,]
        {
            { 0.21805d, 0.45113d, 0.24060d, -0.04511d },
            { -0.80827d, -1.45677d, -0.44361d, 0.52068d },
            { -0.07895d, -0.22368d, -0.05263d, 0.19737d },
            { -0.52256d, -0.81391d, -0.30075d, 0.30639d }
        });
        b.ShouldBe(expectedB);
    }

    [Fact]
    public void TestInverseOfInvertibleMatrix2()
    {
        var a = new Matrix(new double[,] { { 8, -5, 9, 2 }, { 7, 5, 6, 1 }, { -6, 0, 9, 6 }, { -3, 0, -9, -4 } });
        var b = a.Inverse();
        var expectedB = new Matrix(new[,]
        {
            { -0.15385d, -0.15385d, -0.28205d, -0.53846d },
            { -0.07692d, 0.12308d, 0.02564d, 0.03077d },
            { 0.35897d, 0.35897d, 0.43590d, 0.92308d },
            { -0.69231d, -0.69231d, -0.76923d, -1.92308d }
        });
        b.ShouldBe(expectedB);
    }

    [Fact]
    public void TestInverseOfInvertibleMatrix3()
    {
        var a = new Matrix(new double[,] { { 9, 3, 0, 9 }, { -5, -2, -6, -3 }, { -4, 9, 6, 4 }, { -7, 6, 6, 2 } });
        var b = a.Inverse();
        var expectedB = new Matrix(new[,]
        {
            { -0.04074d, -0.07778d, 0.14444d, -0.22222d },
            { -0.07778d, 0.03333d, 0.36667d, -0.33333d },
            { -0.02901d, -0.14630d, -0.10926d, 0.12963d },
            { 0.17778d, 0.06667d, -0.26667d, 0.33333d }
        });
        b.ShouldBe(expectedB);
    }
}