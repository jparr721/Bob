import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def visualize():
    frame = pd.read_csv('./Run-2019-01-23-14:26:42.csv')
    x = frame['time']
    y = frame['glucose']
    x = list(x)
    y = list(y)

    z = np.polyfit(x, y, 3)
    f = np.poly1d(z)

    x_n = np.linspace(x[0], x[-1], 50)
    y_n = f(x_n)

    plt.plot(x, y, 'o', x_n, y_n)
    plt.show()


visualize()
