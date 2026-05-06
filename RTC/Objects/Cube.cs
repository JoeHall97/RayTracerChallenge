using RTC.Datastructures;
using RTC.Helpers;
using RTC.Primitives;

namespace RTC.Objects;

public class Cube : Shape
{
    public Cube()
    { }
    
    public Cube(Matrix transformation)
    {
        Transformation = transformation;
        Material = new Material();
    }

    public Cube(Material material)
    {
        Transformation = Matrix.IdentityMatrix(4);
        Material = material;
    }
    
    protected override Intersection[] LocalIntersect(Ray localRay)
    {
        var (xTMin, xTMax) = Helper.CheckAxis(localRay.Origin.X, localRay.Direction.X);
        var (yTMin, yTMax) = Helper.CheckAxis(localRay.Origin.Y, localRay.Direction.Y);
        var (zTMin, zTMax) = Helper.CheckAxis(localRay.Origin.Z, localRay.Direction.Z);
        
        // the smallest maximum value of the t values
        var tMin = Math.Max(xTMin, Math.Max(yTMin, zTMin));
        // the largest minimum value of the t values
        var tMax = Math.Min(xTMax, Math.Min(yTMax, zTMax));
        
        return tMin > tMax ? [] : [new Intersection(this, tMin), new Intersection(this, tMax)];
    }

    protected override Vec4 LocalNormalAt(Vec4 objectPoint)
    {
        var absX = Math.Abs(objectPoint.X);
        var absY = Math.Abs(objectPoint.Y);
        var absZ = Math.Abs(objectPoint.Z);
        
        var maxC = Math.Max(absX, Math.Max(absY, absZ));
        
        if (maxC.IsEqual(absX)) return Vec4.Vector(objectPoint.X, 0, 0);
        if (maxC.IsEqual(absY)) return Vec4.Vector(0, objectPoint.Y, 0);
        
        return Vec4.Vector(0, 0, objectPoint.Z);
    }
}