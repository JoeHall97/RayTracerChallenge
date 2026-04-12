using System.Reflection;
using RTC.Console.Exercises;

var implementations = Assembly.GetExecutingAssembly()
    .GetTypes()
    .Where(t => typeof(IChapterExercise).IsAssignableFrom(t) && t is { IsInterface: false, IsAbstract: false })
    .OrderBy(t => t.Name.Length)
    .ThenBy(t => t.Name)
    .ToList();

Console.WriteLine("Choose Chapter Exercise to Run:");
for (var i = 0; i < implementations.Count; i++) Console.WriteLine($"{i + 1}: {implementations[i].Name}");

// To instantiate the chosen one:
var choice = int.Parse(Console.ReadLine() ?? "1") - 1;
var exercise = (IChapterExercise)Activator.CreateInstance(implementations[choice])!;
exercise.Run();