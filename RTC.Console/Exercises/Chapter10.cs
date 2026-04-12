using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;

namespace RTC.Console.Exercises;

public class Chapter10 : IChapterExercise
{
    public void Run()
    {
        var world = new World();

        var floor = new Plane();
        floor.Material = floor.Material with
        {
            Pattern = new BlendedPattern(
                new StripePattern(new Colour(0.2d, 0.4d, 0.2d), Colour.White,
                    Matrix.RotationXMatrix(-Math.PI / 5) * Matrix.RotationYMatrix(-Math.PI / 5)),
                new StripePattern(new Colour(0.2d, 0.4d, 0.2d), Colour.White,
                    Matrix.RotationXMatrix(Math.PI / 5) * Matrix.RotationYMatrix(Math.PI / 5) *
                    Matrix.ScalingMatrix(0.5d, 0.5d, 0.5d))
            )
        };
        world.Shapes.Add(floor);

        var middle = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(-0.5d, 1, 0.5d)
        };
        middle.Material = middle.Material with
        {
            Pattern = new RadialGradiantPattern(
                new Colour(0.6d, 0.6d, 1),
                new Colour(0.6d, 0.3d, 0.3d),
                Matrix.RotationZMatrix(-Math.PI / 3) * Matrix.ScalingMatrix(1.4d, 1.4d, 1.4d)
            ),
            Diffuse = 0.7d,
            Ambient = 0.1d,
            Specular = 0.3d
        };
        world.Shapes.Add(middle);

        var right = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(1.5d, 0.5d, -0.5d) * Matrix.ScalingMatrix(0.5d, 0.5d, 0.5d)
        };
        right.Material = right.Material with
        {
            Pattern = new RingPattern(new Colour(1d, 0.5d, 0.4d), Colour.White,
                Matrix.RotationXMatrix(Math.PI / 2) * Matrix.ScalingMatrix(0.4d, 0.4d, 0.4d)),
            Diffuse = 0.7d,
            Specular = 0.3d
        };
        world.Shapes.Add(right);

        var left = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(-1.5d, 0.63d, -1) * Matrix.ScalingMatrix(0.64d, 0.64d, 0.64d)
        };
        left.Material = left.Material with
        {
            Pattern = new StripePattern(
                new RingPattern(new Colour(0.1d, 1, 0.5d), Colour.White, Matrix.ScalingMatrix(0.33d, 0.33d, 0.33d)),
                new SolidPattern(new Colour(1, 0.1d, 0.5d), Matrix.ScalingMatrix(0.33d, 0.33d, 0.33d)),
                Matrix.ScalingMatrix(0.25d, 0.25d, 0.25d)),
            Diffuse = 0.7d,
            Specular = 0.3d
        };
        world.Shapes.Add(left);

        world.Lights.Add(new PointLight(Colour.White, Vec4.Point(-10, 10, -10)));

        var camera = new Camera(300, 300, Math.PI / 3)
        {
            Transformation = Matrix.ViewTransform(Vec4.Point(0, 1.5d, -5), Vec4.Point(0, 1, 0), Vec4.Vector(0, 1, 0))
        };

        var image = camera.Render(world);
        image.SavePng("Chapter10.png");
    }
}