import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data/ucbvi.csv')
print(data)

nb_episodes = data['episode'].max()
horizon= (data['episode'] == 0).sum()
regret = data['regret'].values
regret = regret[range(0, nb_episodes*horizon+1, horizon)]
plt.plot(np.cumsum(regret))
plt.show()
