#!/bin/python3
import sys
import numpy as np

VEC_COUNT = 10_000
VEC_SIZE = 1_000

def get_corr(v1, v2):
    v1_dm = v1 - np.mean(v1)
    v2_dm = v2 - np.mean(v2)
    v1_norm = np.linalg.norm(v1_dm)
    v2_norm = np.linalg.norm(v2_dm)

    return np.dot(v1_dm, v2_dm) / (v1_norm * v2_norm)

def select_vectors(mat, threshold=0.05):
    selected_indices = []
    selected = []

    for i, v in enumerate(mat):
        good = True

        for j, vx in enumerate(selected):
            corr = get_corr(v, vx)
            if corr > threshold:
                print(i, j, corr)
                good = False
                break

        if good:
            selected.append(v)
            selected_indices.append(i)

    return selected_indices


if __name__ == '__main__':

    if len(sys.argv) > 1:
        seed = int(sys.argv[1])
        np.random.seed(seed)

    mat = []

    for i in range(VEC_COUNT):
        multiplier = np.random.randint(1, 1000)
        arr = np.random.rand(VEC_SIZE).astype(np.float32) * multiplier
        mat.append(arr)

    mat.sort(key=lambda x: -np.linalg.norm(x))

    with open('vectors.mat', 'w') as input_file_handle:
        for arr in mat:
            for v in arr:
                input_file_handle.write(f"{v} ")
            input_file_handle.write("\n")

    vec_indices = select_vectors(mat)

    with open('selected.arr', 'w') as out_f:
        out_f.write(' '.join(str(i) for i in vec_indices))
