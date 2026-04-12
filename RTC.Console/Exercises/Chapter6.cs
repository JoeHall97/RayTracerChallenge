using RTC.Datastructures;
using RTC.Helpers;
using RTC.Objects;
using RTC.Primitives;

namespace RTC.Console.Exercises;

public class Chapter6 : IChapterExercise
{
    public void Run()
    {
        const int pixelCount = 400;
        const double wallSize = 10.0d;
        const double pixelSize = wallSize / pixelCount;
        const double halfWallSize = wallSize / 2.0d;

        var rayOrigin = Vec4.Point(0, 0, -5);
        var shape = new Sphere
        {
            Material = new Material(new Colour(0.3d, 0.2d, 1.0d)),
            Transformation = Matrix.ScalingMatrix(1.3d, 1.4d, 1.0d)
        };
        var light = new PointLight(Colour.White, Vec4.Point(-10, 10, -10));
        var canvas = new Canvas(pixelCount, pixelCount);

        for (var y = 0; y < pixelCount; y++)
        {
            var worldY = halfWallSize - pixelSize * y;
            for (var x = 0; x < pixelCount; x++)
            {
                const double wallZ = 10.0d;
                var worldX = -halfWallSize + pixelSize * x;
                var position = Vec4.Point(worldX, worldY, wallZ);
                var ray = new Ray(rayOrigin, (position - rayOrigin).Normalise());
                var xs = shape.Intersect(ray);

                var hit = xs.Hit();
                if (hit is null) continue;

                var point = ray.Position(hit.Value.T);
                var normal = shape.NormalAt(point);
                var eye = -ray.Direction;
                var colour = shape.Material.Lighting(shape, light, point, eye, normal, false);
                canvas.WritePixel(x, y, colour);
            }
        }

        canvas.SavePpm("ChapterSix.ppm");
        canvas.SavePng("ChapterSix.png");
    }
}