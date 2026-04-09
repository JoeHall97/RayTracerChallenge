using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;

namespace RTC.Console.Exercises;

public class Chapter7 : IChapterExercise
{
    public void Run()
    {
        var world = new World();

        var floor = new Sphere();
        floor.Material = floor.Material with
        {
            Colour = new Colour(1, 0.9d, 0.9d),
            Specular = 0
        };
        floor.Transformation = Matrix.ScalingMatrix(10, 0.01d, 10);
        world.Shapes.Add(floor);
        
        var leftWall = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 5) * 
                             Matrix.RotationYMatrix(-Math.PI / 4) *
                             Matrix.RotationXMatrix(Math.PI / 2) *
                             Matrix.ScalingMatrix(10, 0.01d, 10)
        };
        world.Shapes.Add(leftWall);
        
        var rightWall = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(0, 0, 5) * 
                             Matrix.RotationYMatrix(Math.PI / 4) *
                             Matrix.RotationXMatrix(Math.PI / 2) *
                             Matrix.ScalingMatrix(10, 0.01d, 10)
        };
        world.Shapes.Add(rightWall);

        var middle = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(-0.5d, 1, 0.5d)
        };
        middle.Material = middle.Material with
        {
            Colour = new Colour(0.1d, 1, 0.5d),
            Diffuse = 0.7d,
            Specular = 0.3d
        };
        world.Shapes.Add(middle);

        var right = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(1.5d, 0.5d, -0.5d) * Matrix.ScalingMatrix(0.5d, 0.5d, 0.5d)
        };
        right.Material = right.Material with
        {
            Colour = new Colour(0.5d, 1, 0.1d),
            Diffuse = 0.7d,
            Specular = 0.3d
        };
        world.Shapes.Add(right);

        var left = new Sphere
        {
            Transformation = Matrix.TranslationMatrix(-1.5d, 0.33d, -0.75d) * Matrix.ScalingMatrix(0.33d, 0.33d, 0.33d)
        };
        left.Material = left.Material with
        {
            Colour = new Colour(1, 0.8d, 0.1d),
            Diffuse = 0.7d,
            Specular = 0.3d
        };
        world.Shapes.Add(left);
        
        world.Lights.Add(new PointLight(Colour.White, Vec4.Point(-10, 10, -10)));

        var camera = new Camera(300, 300, Math.PI / 3)
        {
            Transformation = Matrix.ViewTransform(Vec4.Point(0, 1.5, -5), Vec4.Point(0, 1, 0), Vec4.Vector(0, 1, 0))
        };
        
        var canvas = camera.Render(world);
        canvas.SavePng("Chapter7.png");
    }
}