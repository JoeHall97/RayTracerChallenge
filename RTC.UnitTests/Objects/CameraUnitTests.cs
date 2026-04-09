using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class CameraUnitTests
{
    public static IEnumerable<object[]> PixelSizeTestData =>
    [
        [200, 125, Math.PI / 2, 0.01d],
        [125, 200, Math.PI / 2, 0.01d],
    ];

    public static IEnumerable<object[]> RayForPixelTestData =>
    [
        // ray through the center of the canvas
        [100, 50, Matrix.IdentityMatrix(4), Vec4.Point(0, 0, 0), Vec4.Vector(0, 0, -1)],
        // ray through a corner of the canvas
        [0, 0, Matrix.IdentityMatrix(4), Vec4.Point(0, 0, 0), Vec4.Vector(0.66519d, 0.33259d, -0.66851d)],
        // ray when the camera is transformed
        [100, 50, Matrix.RotationYMatrix(Math.PI / 4) * Matrix.TranslationMatrix(0, -2, 5), Vec4.Point(0, 2, -5), Vec4.Vector(Math.Sqrt(2) / 2, 0, -Math.Sqrt(2) / 2)],
    ];

    [Theory]
    [MemberData(nameof(PixelSizeTestData))]
    public void TestCameraPixelSize(uint hSize, uint vSize, double fov, double expected)
    {
        var camera = new Camera(hSize, vSize, fov);
        camera.PixelSize.IsEqual(expected).ShouldBeTrue();
    }

    [Theory]
    [MemberData(nameof(RayForPixelTestData))]
    public void TestCameraRayForPixel(uint x, uint y, Matrix cameraTransform, Vec4 expectedOrigin, Vec4 expectedDirection)
    {
        var c = new Camera(201, 101, Math.PI / 2)
        {
            Transformation = cameraTransform
        };
        var r = c.RayForPixel(x, y);
        r.Origin.ShouldBe(expectedOrigin);
        r.Direction.ShouldBe(expectedDirection);
    }

    [Fact]
    public void TestCameraRender()
    {
        var w = World.DefaultWorld();
        var c = new Camera(11, 11, Math.PI / 2);
        var from = Vec4.Point(0, 0, -5);
        var to = Vec4.Point(0, 0, 0);
        var up = Vec4.Vector(0, 1, 0);
        c.Transformation = Matrix.ViewTransform(from, to, up);
        
        var image = c.Render(w);
        image.GetPixel(5, 5).ShouldBe(new Colour(0.38066d, 0.47583d, 0.2855d));
    }
}