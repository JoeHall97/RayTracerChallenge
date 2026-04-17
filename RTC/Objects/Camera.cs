using RTC.Datastructures;
using RTC.Primitives;

namespace RTC.Objects;

/// <summary>
///     A camera that can be used to render a scene.
/// </summary>
public class Camera
{
    public Camera(uint hSize, uint vSize, double fov)
    {
        HorizontalSize = hSize;
        VerticalSize = vSize;
        FieldOfView = fov;
        Transformation = Matrix.IdentityMatrix(4);

        // calculate the tangent of half the field of view, giving us a right angle triangle between the camera and the canvas
        var halfView = Math.Tan(FieldOfView / 2);
        var aspect = (double)hSize / vSize;
        // if the vertical size is less than or equal to the horizontal size
        if (aspect >= 1)
        {
            HalfWidth = halfView;
            HalfHeight = halfView / aspect;
        }
        // if the vertical size is greater than the horizontal size
        else
        {
            HalfWidth = halfView * aspect;
            HalfHeight = halfView;
        }

        PixelSize = HalfWidth * 2 / HorizontalSize;
    }

    /// <summary>
    ///     The number of horizontal pixels.
    /// </summary>
    public uint HorizontalSize { get; }

    /// <summary>
    ///     The number of vertical pixels.
    /// </summary>
    public uint VerticalSize { get; }

    /// <summary>
    ///     The camera's field of view.
    /// </summary>
    public double FieldOfView { get; }

    /// <summary>
    ///     The transformation matrix for the camera.
    /// </summary>
    public Matrix Transformation { get; set; }

    /// <summary>
    ///     The size of a single pixel.
    /// </summary>
    public double PixelSize { get; }

    /// <summary>
    ///     Half the width of the canvas.
    /// </summary>
    private double HalfWidth { get; }

    /// <summary>
    ///     Half the height of the canvas.
    /// </summary>
    private double HalfHeight { get; }

    /// <summary>
    ///     Computes world coordinates at the center of the given pixel, then constructs a ray that passes through that point.
    /// </summary>
    /// <param name="x">The x coordinate of the pixel.</param>
    /// <param name="y">The y coordinate of the pixel.</param>
    /// <returns>A ray originating from the camera's position and pointing towards the specified pixel.</returns>
    public Ray RayForPixel(uint x, uint y)
    {
        // the offset from the edge of the canvas to the pixel's center
        var xOffset = (x + 0.5d) * PixelSize;
        var yOffset = (y + 0.5d) * PixelSize;

        // the untransformed coordinates of the pixel in world space
        // note: camera is looking towards -z, so +x is to the left
        var worldX = HalfWidth - xOffset;
        var worldY = HalfHeight - yOffset;

        // using the camera matrix, transform the canvas point and the origin, and then compute the ray's direction vector
        var pixel = Transformation.Inverse() * Vec4.Point(worldX, worldY, -1);
        var origin = Transformation.Inverse() * Vec4.Point(0, 0, 0);
        var direction = (pixel - origin).Normalise();

        return new Ray(origin, direction);
    }

    /// <summary>
    ///     Renders a scene using the camera and the given world.
    /// </summary>
    /// <param name="world">The world to render.</param>
    /// <returns>The rendered image.</returns>
    public Canvas Render(World world)
    {
        var image = new Canvas((int)HorizontalSize, (int)VerticalSize);

        for (uint y = 0; y < VerticalSize; y++)
        {
            var y1 = y;
            Parallel.For(0, HorizontalSize, x =>
            {
                var ray = RayForPixel((uint)x, y1);
                var color = world.ColourAt(ray, 4);
                image.WritePixel((int)x, (int)y1, color);
            });
        }

        return image;
    }
}