using RTC.Objects;
using Shouldly;

namespace RTC.UnitTests.Objects;

public class CanvasUnitTests
{
    public static IEnumerable<object[]> PpmTestData =>
    [
        [
            Enumerable.Repeat(Enumerable.Repeat(new Colour(1, 0.8f, 0.6f), 10).ToArray(), 2).ToArray(),
            new List<string>
            {
                "P3",
                "10 2",
                "255",
                "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
                "153 255 204 153 255 204 153 255 204 153 255 204 153",
                "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204",
                "153 255 204 153 255 204 153 255 204 153 255 204 153"
            }
        ],
        [
            new Colour[][]
            {
                [
                    new Colour(1.4f, 0, 0), new Colour(0, 0, 0), new Colour(0, 0, 0),
                    new Colour(0, 0, 0), new Colour(0, 0, 0)
                ],
                [
                    new Colour(0, 0, 0), new Colour(0, 0, 0), new Colour(0, 0.5f, 0),
                    new Colour(0, 0, 0), new Colour(0, 0, 0)
                ],
                [
                    new Colour(0, 0, 0), new Colour(0, 0, 0), new Colour(0, 0, 0),
                    new Colour(0, 0, 0), new Colour(-0.5f, 0, 1)
                ]
            },
            new List<string>
            {
                "P3",
                "5 3",
                "255",
                "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
                "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
                "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255"
            }
        ]
    ];

    [Theory]
    [MemberData(nameof(PpmTestData))]
    public void TestPpmGeneration(Colour[][] pixels, List<string> expected)
    {
        var canvas = new Canvas(0, 0);
        canvas.SetCanvas(pixels);

        var ppmStrings = canvas.ToPpm().Split('\n', StringSplitOptions.RemoveEmptyEntries);
        ppmStrings.Length.ShouldBe(expected.Count);
        for (var i = 0; i < expected.Count; i++) ppmStrings[i].ShouldBe(expected[i]);
    }
}