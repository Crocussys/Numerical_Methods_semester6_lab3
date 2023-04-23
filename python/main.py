import numpy as np


def f(x):
    x1, x2 = x[0], x[1]
    return np.array([x1 ** 3 - x2 ** 2 - 1, x1 * x2 ** 3 - x2 - 4])


def jacobi_1(x):
    x1, x2 = x[0], x[1]
    return np.array([[3 * x2 ** 2 * x1 - 1, -x2 ** 3], [2 * x2, 3 * x1 ** 2]]) /\
        (9 * x1 ** 3 * x2 ** 2 - 3 * x1 ** 2 + 2 * x2 ** 4)


def is_end(x_prev, x, fx, err1, err2):
    delta1, delta2 = 0, 0
    for i in range(len(fx)):
        val = abs(fx[i])
        if val > delta1:
            delta1 = val
    for i in range(len(x)):
        if abs(x[i]) < 1:
            val = abs(x[i] - x_prev[i])
        else:
            val = abs(1 - x_prev[i] / x[i])
        if val > delta2:
            delta2 = val
    print(f"delta1 = {delta1} delta2 = {delta2}")
    if delta1 > err1:
        return False
    if delta2 > err2:
        return False
    return True


def main(x, max_i=1000, err1=1e-9, err2=1e-9):
    i, fx = 1, f(x)
    x_next = x - jacobi_1(x) @ fx
    print("1:", end=" ")
    while not is_end(x, x_next, fx, err1, err2) and i <= max_i:
        fx = f(x)
        x_next, x = x - jacobi_1(x) @ fx, x_next
        i += 1
        print(f"{i}:", end=" ")
    return x_next


if __name__ == '__main__':
    x0 = np.array([1.2, 1.3])
    ans = main(x0)
    print(f"Ответ {ans}")
