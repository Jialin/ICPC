from sys import stdout, stderr


def max_count_range(day, lower, upper):
    return sum(100 << (day // j) for j in range(lower, upper))


def count(day, r0, r):
    return r0 << (day // r)


def calc456(day):
    print(day)
    stdout.flush()
    n = int(input())
    n %= count(day, 1, 3)
    r4 = n >> (day >> 2)
    n -= count(day, r4, 4)
    r5 = n >> (day // 5)
    n -= count(day, r5, 5)
    r6 = n >> (day // 6)
    return r4, r5, r6


def calc123(day, r4, r5, r6):
    print(day)
    stdout.flush()
    n = int(input())
    r1 = n >> day
    n -= count(day, r1, 1)
    r2 = n >> (day >> 1)
    n -= count(day, r2, 2) + count(day, r4, 4) + count(day, r5, 5) + count(day, r6, 6)
    r3 = n >> (day // 3)
    return r1, r2, r3


T, W = map(int, input().split())
for _ in range(T):
    r4, r5, r6 = calc456(185)
    r1, r2, r3 = calc123(38, r4, r5, r6)
    print(' '.join(map(str, [r1, r2, r3, r4, r5, r6])))
    stdout.flush()
    assert(int(input()) == 1)
