f_color = 0xff0000  # red (start color)
s_color = 0x00ff00  # green (end color)
n = 10  # number of steps

for i in range(n + 1):  # include final step
    t = i / n  # interpolation factor
    # Interpolate between start and end colors
    interpolated_color = int(f_color + (s_color - f_color) * t)
    # Print the color in hexadecimal format
    print(f"Step {i}: #{interpolated_color:06x}")
