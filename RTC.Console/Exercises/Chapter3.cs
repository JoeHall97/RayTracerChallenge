using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;

namespace RTC.Console.Exercises;

public class Chapter3 : IChapterExercise
{
    public void Run()
    {
        const int width = 480;
        const int height = 360;
        const float radius = width * 0.33f;
        
        Canvas canvas = new(width, height);
        var canvasOrigin = Vec4.Point(width / 2.0d, height / 2.0d, 0);
        var twelve = Vec4.Point(0, 1, 0);
        var blue = new Colour(0, 0, 1);
        
        // write to the center of the canvas
        canvas.WritePixel((int)canvasOrigin.X, height - (int)canvasOrigin.Y, blue);
        
        // starting with 12 o'clock, rotate around the circle's perimeter
        for (var i = 0; i < 12; i++)
        {
            var rotation = Matrix.RotationZMatrix(i * Math.PI / 6.0d);
            var point = rotation * twelve;
            point.X *= radius;
            point.Y *= radius;
            point += canvasOrigin;
            var hasWritten = canvas.WritePixel(
                (int)point.X, 
                height - (int)point.Y, 
                blue);
            if (!hasWritten)
            {
                System.Console.Error.WriteLine($"Could not write pixel to x = {point.X}, y = {point.Y}");
            }
        }
        
        canvas.SavePpm("ChapterThree.ppm");
        canvas.SavePng("ChapterThree.png");
    }
}