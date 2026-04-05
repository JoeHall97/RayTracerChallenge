namespace RTC.Datastructures;

/// <summary>
/// A sorted set of intersections.
/// </summary>
public class IntersectionSet
{
    /// <summary>
    /// Compares/sorts intersections by their 'T' value.
    /// </summary>
    private class IntersectionComparer : IComparer<Intersection>
    {
        public int Compare(Intersection? x, Intersection? y)
        {
            if (x == null && y == null) return 0;
            if (x == null) return -1;
            if (y == null) return 1;

            if (x.T > y.T) return 1;
            if (x.T < y.T) return -1;
            return 0;
        }
    }
    
    public IntersectionSet(params Intersection[] intersections)
    {
        Values = new SortedSet<Intersection>(new IntersectionComparer());
        
        foreach (var intersection in intersections)
        {
            Values.Add(intersection);
        }
    } 
    
    /// <summary>
    /// The sorted set of intersections.
    /// </summary>
    public SortedSet<Intersection> Values { get; }

    /// <summary>
    /// The first intersection that has a positive 'T' value.
    /// </summary>
    public Intersection? Hit => Values.FirstOrDefault(i => i.T > 0);
}

