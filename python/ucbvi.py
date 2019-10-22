import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

results = {}
for bt in ["bernstein", "hoeffding"]:

    try:
        data = pd.read_csv('data/ucbvi_{}.csv'.format(bt))
        print(bt)
        print(data)
        results[bt] = data
    except:
        print(bt," does not exists.")

for k in results.keys():
    data = results[k]
    nb_episodes = data['episode'].max()
    horizon= (data['episode'] == 0).sum()
    regret = data['regret'].values
    regret = regret[range(0, nb_episodes*horizon+1, horizon)]
    plt.plot(np.cumsum(regret), label=k)
plt.legend()
plt.show()
