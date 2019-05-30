from fractions import Fraction


def append(b):
    order = sorted([(xs[i] * b + ys[i], i) for i in range(n)])
    orders.append([x[1] for x in order])


def calc():
    if not len(bs):
        append(Fraction(1, 1))
    else:
        append(bs[0] / 2)
        for i in range(1, len(bs)):
            if bs[i - 1] != bs[i]:
                append((bs[i - 1] + bs[i]) / 2)
        append(bs[-1] + 1)
    orders.sort()
    res = 1
    for i in range(1, len(orders)):
        if orders[i - 1] != orders[i]:
            res += 1
    return res


orders = []
for taskIdx in range(int(input())):
    n = int(input())
    xs = [0] * n
    ys = [0] * n
    for i in range(n):
        xs[i], ys[i] = map(int, input().split())
    bs = []
    for i in range(n):
        for j in  range(i + 1, n):
            if xs[i] == xs[j]:
                continue
            b = Fraction(ys[j] - ys[i], xs[i] - xs[j])
            if b > 0:
                bs.append(b)
    bs.sort()
    orders.clear()
    print('Case #%d: %d' % (taskIdx + 1, calc()))
