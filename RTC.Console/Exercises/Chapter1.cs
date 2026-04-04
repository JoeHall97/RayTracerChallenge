using RTC.Console.Exercises.Structs;
using RTC.Datastructures;
using Environment = RTC.Console.Exercises.Structs.Environment;

namespace RTC.Console.Exercises;

public class Chapter1 : IChapterExercise
{
    public void Run()
    {
        var p = new Projectile
        {
            Position = Vec4.Point(0, 1, 0),
            Velocity = Vec4.Vector(1, 1, 0).Normalised
        };
        var e = new Environment
        {
            Gravity = Vec4.Vector(0, -0.1, 0),
            Wind = Vec4.Vector(-0.01, 0, 0)
        };

        while (p.Position.Y > 0)
        {
            System.Console.WriteLine(p.Position.ToString());
            p = Tick(e, p);
            Thread.Sleep(TimeSpan.FromSeconds(0.5));
        }
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