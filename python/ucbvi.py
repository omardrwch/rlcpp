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
    mean = np.mean(data, axis=1)
    plt.plot(mean, label=k)
plt.legend()
plt.show()
