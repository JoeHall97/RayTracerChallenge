using System.Text;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace RTC.Objects;

public class Canvas(int width, int height)
{
    private Colour[][] _pixels = Enumerable.Range(0, Math.Max(0, height))
        .Select(_ => new Colour[Math.Max(0, width)])
        .ToArray();

    public int Width => _pixels.Length > 0 ? _pixels[0].Length : 0;
    public int Height => _pixels.Length;

    public bool WritePixel(int x, int y, Colour colour)
    {
        if (x < 0 || x >= Width || y < 0 || y >= Height) return false;
        _pixels[y][x] = colour;
        return true;
    }

    public Colour GetPixel(int x, int y)
    {
        return _pixels[y][x];
    }

    public void SetCanvas(Colour[][] pixels)
    {
        _pixels = pixels;
    }

    public string ToPpm()
    {
        StringBuilder sb = new();

        sb.AppendLine("P3");
        sb.AppendLine($"{Width} {Height}");
        sb.AppendLine("255");

        foreach (var row in _pixels)
        {
            var rowWidth = 0;
            foreach (var pixel in row)
            {
                sb.Append(GetPixelPpmValue(pixel.Red, ref rowWidth));
                sb.Append(GetPixelPpmValue(pixel.Green, ref rowWidth));
                sb.Append(GetPixelPpmValue(pixel.Blue, ref rowWidth));
            }

            sb.AppendLine();
        }

        return sb.ToString();
    }

    /// <summary>
    ///     Generates and saves a png image of the canvas.
    /// </summary>
    /// <param name="path">The path to save the png image to.</param>
    public void ToPng(string path)
    {
        using var image = new Image<Rgb24>(Width, Height);

        for (var y = 0; y < Height; y++)
        for (var x = 0; x < Width; x++)
        {
            var pixel = _pixels[y][x];
            image[x, y] = new Rgb24(
                (byte)Math.Clamp(pixel.Red * 255, 0, 255),
                (byte)Math.Clamp(pixel.Green * 255, 0, 255),
                (byte)Math.Clamp(pixel.Blue * 255, 0, 255)
            );
        }

        image.SaveAsPng(path);
    }

    private static string GetPixelPpmValue(float colourValue, ref int currentWidth)
    {
        var value = Math.Max(0, Math.Min(255, Math.Round(colourValue * 255)));
        var stringDigitCount = value == 0 ? 1 : (int)Math.Log10(value) + 1;
        if (currentWidth + stringDigitCount + 1 >= 70)
        {
            currentWidth = stringDigitCount;
            return $"\n{value}";
        }

        var res = currentWidth == 0 ? $"{value}" : $" {value}";
        currentWidth += res.Length;
        return res;
    }
}