namespace RTC.Primitives;

/// <summary>
/// A sorted set of intersections.
/// </summary>
public readonly struct IntersectionSet
{
    /// <summary>
    /// Compares/sorts intersections by their 'T' value.
    /// </summary>
    private readonly struct IntersectionComparer : IComparer<Intersection>
    {
        public int Compare(Intersection x, Intersection y)
        {
            return x.T.CompareTo(y.T);
        }
    }

    public IntersectionSet()
    {
        Values = new SortedSet<Intersection>(new IntersectionComparer());
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
    /// Gets the first intersection that has a positive 'T' value.
    /// </summary>
    /// <returns>The first intersection that has a positive 'T' value, <c>null</c> if none found.</returns>
    public Intersection? Hit()
    {
        try
        {
            return Values.First(i => i.T > 0);
        }
        catch (InvalidOperationException)
        {
            return null;
        }
    }

    /// <summary>
    /// Adds the intersections to the set.
    /// </summary>
    /// <param name="intersections">The intersections to add.</param>
    public void AddIntersections(Intersection[] intersections)
    {
        foreach (var intersection in intersections)
        {
            Values.Add(intersection);
        }
    }
}

