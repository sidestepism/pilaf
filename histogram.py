# encoding: utf-8

import glob
import numpy as np
from scipy.spatial import KDTree


file = open('cluster.dat')
codes = file.readlines()
file.close()

# クラスタの中心点を記述したファイルを読み込み
codes = [[float(x) for x in code.split()] for code in codes]
category_num = len(codes)

# 検索のためのKDTree を作成
tree = KDTree(codes)

# それぞれのファイルのヒストグラムを格納する配列
histograms = []

for category in ['チャーハン', '能年玲奈']:
	files = glob.glob('./surf/%s/*.surf' % category)
	for file in files:
		print("processing: %s" % file)
		# 特徴量を読み込んで配列に入れる
		f = open(file)
		features = [[float(x) for x in line.split()[3:]] for line in f.readlines()[1:]]
		f.close()

		# 最近傍のクラスタ中心点を求める．クラスタ中心までの距離が d ，クラスタ番号の配列が c に格納される
		# すべての特徴量についてまとめて計算できる
		d, c = tree.query(features);
		print(c)

		# ヒストグラムを作成して，ラベルとのタプルを格納
		histogram = np.histogram(c, range(category_num+1))[0]

		print(histogram)
		histograms.append(((1 if category == 'チャーハン' else 0), histogram))


file = open('histograms.dat', 'w')
for histogram in histograms:
	file.write(str(histogram[0]))
	file.write(" ")
	file.write(' '.join(map(lambda x: str(x), histogram[1])) + "\n")
file.close()

file = open('histograms_label.dat', 'w')
for histogram in histograms:
	file.write(str(histogram[0]) + "\n")
file.close()

file = open('histograms_data.dat', 'w')
for histogram in histograms:
	file.write(' '.join(map(lambda x: str(x), histogram[1])) + "\n")
file.close()



