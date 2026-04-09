using RTC.Datastructures;
using RTC.Objects;
using RTC.Primitives;

namespace RTC.Console.Exercises;

public class Chapter5 : IChapterExercise
{
    public void Run()
    {
        const int pixelCount = 400;
        const double wallSize = 10.0d;
        const double pixelSize = wallSize / pixelCount;
        const double halfWallSize = wallSize / 2.0d;
        
        var green = new Colour(0, 1, 0);
        var rayOrigin = Vec4.Point(0, 0, -5);
        var shape = new Sphere();
        var canvas = new Canvas(pixelCount, pixelCount);
        
        for (var y = 0; y < pixelCount; y++)
        {
            var worldY = halfWallSize - pixelSize * y;
            for (var x = 0; x < pixelCount; x++)
            {
                var wallZ = 10.0d;
                var worldX = -halfWallSize + pixelSize * x;
                var position = Vec4.Point(worldX, worldY, wallZ);
                var ray = new Ray(rayOrigin, (position - rayOrigin).Normalise());
                
                var xs = shape.Intersect(ray);
                if (xs.Length > 0)
                {
                    canvas.WritePixel(x, y, green);
                }
            }
        }
        
        canvas.SavePpm("ChapterFive.ppm");
        canvas.SavePng("ChapterFive.png");
    }
}