using RTC.Console.Exercises.Structs;
using RTC.Datastructures;
using RTC.Objects;
using Environment = RTC.Console.Exercises.Structs.Environment;

namespace RTC.Console.Exercises;

public class Chapter2 : IChapterExercise
{
    public void Run()
    {
        var proj = new Projectile
        {
            Position = Vec4.Point(0, 1, 0),
            Velocity = Vec4.Vector(1, 1.8, 0).Normalised * 10.8
        };
        var env = new Environment
        {
            Gravity = Vec4.Vector(0, -0.1, 0),
            Wind = Vec4.Vector(-0.01, 0, 0)
        };
        var canvas = new Canvas(960, 540);
        Colour red = new(1, 0, 0);

        while (proj.Position.Y > 0.00001)
        {
            if (!canvas.WritePixel((int)proj.Position.X, canvas.Height - (int)proj.Position.Y, red))
                System.Console.WriteLine($"Out of bounds: ({proj.Position.X}, {proj.Position.Y})");
            proj = Tick(env, proj);
        }

        canvas.SavePpm("ChapterTwo.ppm");
        canvas.SavePng("ChapterTwo.png");
    }

    private static Projectile Tick(Environment env, Projectile proj)
    {
        return new Projectile
        {
            Position = proj.Position + proj.Velocity,
            Velocity = proj.Velocity + env.Gravity + env.Wind
        };
    }
}