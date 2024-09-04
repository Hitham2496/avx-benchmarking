import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np

def plot_files():
    f1 = np.loadtxt("normal.txt", unpack=True, dtype=float)
    f2 = np.loadtxt("avx.txt", unpack=True, dtype=float)
    f3 = np.loadtxt("avx2.txt", unpack=True, dtype=float)
    plt.xlim(3500, 3600)
    plt.ylim(1e-5, 5e-1)
    plt.ylabel("Relative proportion of runtime")
    plt.xlabel("CPU Frequency")
    plt.yscale("log")
    plt.hist([f1, f2, f3], bins=np.linspace(3500, 3600, 50), alpha=0.75, edgecolor="black", density=True)
    handles = [Rectangle((0,0),1,1,color=c,ec="k") for c in ['#1f77b4', '#ff7f0e', '#2ca02c']]
    labels= ["No vectorisation","AVX1", "AVX2"]
    plt.legend(handles, labels)
    plt.title("CPU Freq. Throttling for Matrix Multiplication in C++")
    plt.savefig(f"plot.pdf")
    plt.close()


plot_files()
