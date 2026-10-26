import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("data.csv")

x = data["km"]
y = data["price"]

fig, ax = plt.subplots()
ax.plot(x, y, "o", label="Données")

theta0 = 0
theta1 = 0
x_line = np.linspace(x.min(), x.max(), 100)
y_line = theta0 + theta1 * x_line
ax.plot(x_line, y_line, color="red", label="Régression linéaire")

ax.set_xlabel("Kilométrage (km)")
ax.set_ylabel("Prix")
ax.grid(True)
ax.legend()
plt.show()