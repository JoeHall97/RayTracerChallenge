using System.Text;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace RTC.Objects;

/// <summary>
/// A 2D array of colours.
/// </summary>
/// <param name="width">The width of the canvas.</param>
/// <param name="height">The height of the canvas.</param>
public class Canvas(int width, int height)
{
    private Colour[][] _pixels = Enumerable.Range(0, Math.Max(0, height))
        .Select(_ => new Colour[Math.Max(0, width)])
        .ToArray();

    /// <summary>
    /// The width of the canvas.
    /// </summary>
    public int Width => _pixels.Length > 0 ? _pixels[0].Length : 0;
    /// <summary>
    /// The height of the canvas.
    /// </summary>
    public int Height => _pixels.Length;

    /// <summary>
    /// Writes a colour to the given position on the canvas.
    /// </summary>
    /// <param name="x">The x-coordinate of the pixel to write to.</param>
    /// <param name="y">The y-coordinate of the pixel to write to.</param>
    /// <param name="colour">The colour to write.</param>
    /// <returns><c>true</c> if the pixel was successfully written, else <c>false</c></returns>
    public bool WritePixel(int x, int y, Colour colour)
    {
        if (x < 0 || x >= Width || y < 0 || y >= Height) return false;
        _pixels[y][x] = colour;
        return true;
    }

    /// <summary>
    /// Gets the colour at the given position on the canvas.
    /// </summary>
    /// <param name="x">The x-coordinate of the pixel.</param>
    /// <param name="y">The y-coordinate of the pixel.</param>
    /// <returns>The colour at the given position.</returns>
    public Colour GetPixel(int x, int y)
    {
        return _pixels[y][x];
    }

    /// <summary>
    /// Sets the pixels of the canvas.
    /// </summary>
    /// <param name="pixels">The pixels to set.</param>
    public void SetCanvas(Colour[][] pixels)
    {
        _pixels = pixels;
    }

    /// <summary>
    /// Converts the canvas to a PPM string.
    /// </summary>
    /// <returns>The PPM string.</returns>
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
    /// Saves the canvas to a PPM file.
    /// </summary>
    /// <param name="fileName">The name of the file to save.<br/><b>NOTE:</b> should end in <i>.ppm</i></param>
    /// <param name="path">The file path to save to.</param>
    public void SavePpm(string fileName, string? path = null)
    {
        File.WriteAllText(path == null ? fileName : Path.Combine(path, fileName), ToPpm());
    }

    /// <summary>
    /// Generates and saves a png image of the canvas.
    /// </summary>
    /// <param name="fileName">The name of the file to save.<br/><b>NOTE:</b> should end in <i>.png</i></param>
    /// <param name="path">The file path to save to.</param>
    public void SavePng(string fileName, string? path = null)
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

        image.SaveAsPng(path == null ? fileName : Path.Combine(path, fileName));
    }

    /// <summary>
    /// Gets the PPM value of a colour, updating the current width to keep the line length under 70 characters.
    /// </summary>
    /// <param name="colourValue">The colour value to convert to PPM format.</param>
    /// <param name="currentWidth">The current width of the PPM string.</param>
    /// <returns>The PPM string representation of the colour value.</returns>
    private static string GetPixelPpmValue(float colourValue, ref int currentWidth)
    {
        var value = Math.Max(0, Math.Min(255, Math.Round(colourValue * 255)));
        var stringDigitCount = value == 0 ? 1 : (int)Math.Log10(value) + 1;
        if (currentWidth + stringDigitCount + 1 >= 70)
        {
            currentWidth = stringDigitCount;
            return $"{System.Environment.NewLine}{value}";
        }

        var res = currentWidth == 0 ? $"{value}" : $" {value}";
        currentWidth += res.Length;
        return res;
    }
}