using System.Reflection;
using RTC.Console.Exercises;

var interfaceType = typeof(IChapterExercise);
var implementations = Assembly.GetExecutingAssembly()
    .GetTypes()
    .Where(t => interfaceType.IsAssignableFrom(t) && !t.IsInterface && !t.IsAbstract)
    .ToList();

Console.WriteLine("Available Exercises:");
for (var i = 0; i < implementations.Count; i++) Console.WriteLine($"{i + 1}: {implementations[i].Name}");

// To instantiate the chosen one:
var choice = int.Parse(Console.ReadLine() ?? "1") - 1;
var exercise = (IChapterExercise)Activator.CreateInstance(implementations[choice])!;
exercise.Run();