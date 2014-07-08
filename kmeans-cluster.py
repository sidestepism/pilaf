# encoding: utf-8

import glob
import numpy as np
from scipy.cluster.vq import vq, kmeans, whiten

features = []

for category in ['チャーハン', 'ピラフ']:
	files = glob.glob('./surf/%s/*.surf' % category)
	for file in files:

		f = open(file)
		lines = f.readlines()
		f.close()
		vector_num = int(lines[0].split()[0])

		for i in range(vector_num):
			features.append([float(x) for x in lines[i+1].split()[3:]])
		break;

features = np.array(features)

codes = kmeans(features, 128)

file = open('cluster.dat', 'w')
for code in codes[0]:
	file.write(' '.join([str(x) for x in code.tolist()]) + "\n")
file.close()
