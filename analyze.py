#!/usr/env/python3

import argparse

import numpy as np


def main():
    parser = argparse.ArgumentParser("This script is to analyze the output of the image complexity")
    parser.add_argument("input", help="The input file", type=str)
    parser.add_argument("--html-format", action="store_true",
                        help="Generate html format output for the convenience of copying/pasting to Excel/Google Sheet/Apple Numbers.")
    parser.add_argument("--output-cdf", type=str, default=None,
                        help="a file path shows the CDF of the data. PDF format is preferred.")
    args = parser.parse_args()

    data = []
    with open(args.input) as f:
        for line in f:
            data.extend([float(i) for i in line.strip().split(' ')])

    data = np.array(data)

    if args.html_format:
        show_html_format(data)
    else:
        show(data)
    if args.output_cdf:
        cdf(data, args.output_cdf)


def show_html_format(data):
    s = "<table>" + \
        "<tr><td>Max value</td><td>%f</td></tr>" % np.max(data) + \
        "<tr><td>Min value</td><td>%f</td></tr>" % np.min(data) + \
        "<tr><td>Average value</td><td>%f</td></tr>" % np.average(data) + \
        "<tr><td>Median value</td><td>%f</td></tr>" % np.median(data) + \
        "<tr><td>Variance</td><td>%f</td></tr>" % np.var(data) + \
        "<tr><td>Standard deviation</td><td>%f</td></tr>" % np.std(data) + \
        "</table>"
    print(s)


def show(data):
    print("Max value: %f" % np.max(data))
    print("Min value: %f" % np.min(data))
    print("Average value: %f" % np.average(data))
    print("Median value: %f" % np.median(data))
    print("Variance: %f" % np.var(data))
    print("Standard deviation: %f" % np.std(data))


def cdf(data, output):
    import matplotlib.pyplot as plt
    s_data = sorted(data)
    X = sorted(set(s_data))
    Y = [0] * len(X)
    i = 0
    j = 0
    while i < len(X):
        while j < len(s_data) and s_data[j] <= X[i]:
            j += 1
        Y[i] = j
        i += 1
    Y = [i / len(X) for i in Y]
    plt.title("CDF Distribution")
    plt.xlabel("Complexity")
    plt.ylabel("Percentage")
    plt.xlim(0, max(X))
    plt.ylim(0, 1)
    plt.plot(X, Y)
    plt.savefig(output)



if __name__ == '__main__':
    main()
