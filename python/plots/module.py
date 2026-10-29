import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator

x = np.linspace(-10, 10, 500)
y = abs(x)

fig, ax = plt.subplots(figsize=(7, 7))

ax.plot(x, y, linewidth=2)

for a in range(-2,10,2):
    ax.axhline(y=a, color="#FF007F", linewidth=2)

ax.spines["left"].set_position("zero")
ax.spines["bottom"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["top"].set_color("none")

ax.set_xlim(-10, 10)
ax.set_ylim(-10, 10)

ax.set_aspect("equal", adjustable="box")

# Major ticks every 1, minor ticks every 0.2
ax.xaxis.set_major_locator(MultipleLocator(1))
ax.yaxis.set_major_locator(MultipleLocator(1))
ax.xaxis.set_minor_locator(MultipleLocator(0.2))
ax.yaxis.set_minor_locator(MultipleLocator(0.2))

ax.grid(which="major", linewidth=0.8)
ax.grid(which="minor", linewidth=0.3, alpha=0.5)

#plt.show()
plt.savefig('foo.png', bbox_inches='tight')
