import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse, Circle, Polygon
import numpy as np

fig, ax = plt.subplots(figsize=(7, 9))

# Colors
body = "#d9d9d9"
belly = "#eeeeee"
inner_ear = "#e8b6bd"
dark = "#222222"
nose = "#9b6b70"
cheese = "#f4d35e"
background = "#ffffff"

# Outer ears
ax.add_patch(Ellipse((-2.55, 5.3), 2.16, 3.1, color=body, zorder=1))
ax.add_patch(Ellipse((2.55, 5.3), 2.16, 3.1, color=body, zorder=1))

# Inner ears
ax.add_patch(Ellipse((-2.55, 5.3), 1.1, 1.8, color=inner_ear, zorder=2))
ax.add_patch(Ellipse((2.55, 5.3), 1.1, 1.8, color=inner_ear, zorder=2))

# Body, belly, head
ax.add_patch(Ellipse((0, -1.85), 8.2, 11.9, color=body, zorder=3))
ax.add_patch(Ellipse((0, -1.55), 5.7, 8.7, color=belly, zorder=4))
ax.add_patch(Ellipse((0, 2.6), 6.5, 6.0, color=body, zorder=5))

# Eyes
ax.add_patch(Ellipse((-1.05, 3.35), 0.54, 0.9, color=dark, zorder=8))
ax.add_patch(Ellipse((1.05, 3.35), 0.54, 0.9, color=dark, zorder=8))

# Nose
ax.add_patch(Ellipse((0, 2.52), 0.84, 0.5, color=nose, zorder=9))

# Mouth
x1 = np.linspace(-0.5, 0, 100)
y1 = -1.9 * (x1 + 0.18) ** 2 + 2.14
ax.plot(x1, y1, color=dark, linewidth=2, zorder=10)

x2 = np.linspace(0, 0.5, 100)
y2 = -1.9 * (x2 - 0.18) ** 2 + 2.14
ax.plot(x2, y2, color=dark, linewidth=2, zorder=10)

# Whiskers
for m, b in [(-0.16, 2.85), (0, 2.55), (0.16, 2.25)]:
    xs = np.linspace(-3.2, -0.45, 100)
    ys = m * xs + b
    ax.plot(xs, ys, color=dark, linewidth=1.5, zorder=10)

for m, b in [(0.16, 2.85), (0, 2.55), (-0.16, 2.25)]:
    xs = np.linspace(0.45, 3.2, 100)
    ys = m * xs + b
    ax.plot(xs, ys, color=dark, linewidth=1.5, zorder=10)

# Cheese
cheese_points = [(-0.75, 0.2), (0.55, 1.15), (0.9, 0.05)]
ax.add_patch(Polygon(cheese_points, closed=True, color=cheese, zorder=11))

# Paws over cheese
ax.add_patch(Ellipse((-0.82, 0.65), 0.9, 1.44, color=body, zorder=12))
ax.add_patch(Ellipse((0.82, 0.65), 0.9, 1.44, color=body, zorder=12))

# Cheese holes
ax.add_patch(Circle((-0.18, 0.52), 0.11, color=background, zorder=13))
ax.add_patch(Circle((0.32, 0.72), 0.09, color=background, zorder=13))
ax.add_patch(Circle((0.58, 0.34), 0.08, color=background, zorder=13))

# Feet
ax.add_patch(Ellipse((-1.65, -7.1), 1.3, 0.7, color=body, zorder=6))
ax.add_patch(Ellipse((1.65, -7.1), 1.3, 0.7, color=body, zorder=6))

# Little paw/finger lines
for x in [-0.95, -0.72, 0.95, 0.72]:
    ax.plot([x, x], [0.2, 0.65], color=dark, linewidth=1.2, zorder=14)

ax.set_aspect("equal")
ax.set_xlim(-5, 5)
ax.set_ylim(-8, 7)
ax.axis("off")

plt.show()
