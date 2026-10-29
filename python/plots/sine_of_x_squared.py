import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-20, 20, 500)
y = np.sin(x**2)

fig, ax = plt.subplots(figsize=(10,10))
ax.plot(x, y, linewidth=2)

plt.show()
