using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;
using RTC.Primitives.Patterns;

namespace RTC.Console.Exercises;

public class Chapter12 : IChapterExercise
{
    public void Run()
    {
        var world = new World();

        var floor = new Plane
        {
            Material = new Material(Colour.White)
            {
                Transparency = 0.9d,
                Reflective = 0.9d
            }
        };
        world.Shapes.Add(floor);

        var leftWall = new Plane
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 5) *
                             Matrix.RotationYMatrix(-Math.PI / 4) *
                             Matrix.RotationXMatrix(Math.PI / 2) *
                             Matrix.ScalingMatrix(10, 0.01d, 10),
            Material = new Material(new CheckerPattern(Colour.White, Colour.Black,
                Matrix.ScalingMatrix(0.06d, 0.06d, 0.06d)))
        };
        world.Shapes.Add(leftWall);

        var rightWall = new Plane
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 5) *
                             Matrix.RotationYMatrix(Math.PI / 4) *
                             Matrix.RotationXMatrix(Math.PI / 2) *
                             Matrix.ScalingMatrix(10, 0.01d, 10),
            Material = new Material(new CheckerPattern(Colour.White, Colour.Black,
                Matrix.ScalingMatrix(0.06d, 0.06d, 0.06d)))
        };
        world.Shapes.Add(rightWall);

        var middle = new Cube(Matrix.TranslationMatrix(0, 1, 1));
        world.Shapes.Add(middle);
        
        var left = new Cube(Matrix.TranslationMatrix(-2, 0.4d, 0.5d) * Matrix.ScalingMatrix(0.4d, 0.4d, 0.4d));
        left.Material = left.Material with { Colour = new Colour(0.8d, 0.8d, 0.2d) };
        world.Shapes.Add(left);
        
        var right = new Cube(Matrix.TranslationMatrix(2, 0.7d, 0) * Matrix.ScalingMatrix(0.7d, 0.7d, 0.7d));
        right.Material = right.Material with { Colour = new Colour(0.2d, 0.8d, 0.8d) };
        world.Shapes.Add(right);

        world.Lights.Add(new PointLight(Colour.White, Vec4.Point(-10, 10, -10)));

        var camera = new Camera(300, 300, Math.PI / 3)
        {
            Transformation = Matrix.ViewTransform(Vec4.Point(0, 2.5d, -4), Vec4.Point(0, 1, 0), Vec4.Vector(0, 1, 0))
        };

        var image = camera.Render(world);
        image.SavePng("Chapter12.png");
    }
}