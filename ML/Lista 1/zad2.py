import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# pandas
iris_url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
iris_df = pd.read_csv(iris_url, header=None)
iris_df.columns = ['sepal_length', 'sepal_width', 'petal_length', 'petal_width', 'target']
# print(iris_df.head(10))
# print(iris_df.describe())

# seaborn
# sns.pairplot(iris_df, hue='target')
# plt.show()
iris_df_long = pd.melt(iris_df, id_vars='target', var_name='variable', value_name='value')
# print(iris_df_long.head())
sns.catplot(data=iris_df_long, x='variable', y='value', hue='target', kind='box')
plt.show()

