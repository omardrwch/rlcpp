import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

results = {}
for bt in ["bernstein", "hoeffding"]:

    try:
        data = pd.read_csv('data/ucbvi_chain_{}.csv'.format(bt))
        print(bt)
        print(data)
        results[bt] = data
    except:
        print(bt," does not exists.")

# for k in results.keys():
#     data = results[k]
#     nb_episodes = data['episode'].max()
#     horizon= (data['episode'] == 0).sum()
#     regret = data['regret'].values
#     regret = regret[range(0, nb_episodes*horizon+1, horizon)]
#     plt.plot(np.cumsum(regret), label=k)

for k in results.keys():
    data = results[k].values
    n_ep, n_rep = data.shape
    mean = np.mean(data, axis=1)
    std = np.std(data, axis=1) / np.sqrt(n_rep)
    plt.plot(mean, label=k)
    plt.fill_between(np.arange(n_ep), mean - 2*std, mean + 2*std, alpha=0.15)
plt.legend()
plt.show()
