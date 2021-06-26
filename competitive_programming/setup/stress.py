#!/bin/python3

from random import randint
from random import choice
from random import shuffle
from os import popen
from os import system
from time import sleep

def generate_tree(n):
    e = []

    for i in range(1, n):
        p = randint(0, i - 1)
        e.append((p + 1, i + 1))
    return e

def generate_tree_p(n):
    p = []

    for i in range(1, n):
        p.append(randint(1, i))
    return p

def generate_connected_graph(n, m):
    e = generate_tree(n)
    m -= n - 1

    for i in range(m):
        u = randint(1, n)
        v = randint(1, n)

        while u == v or (u, v) in e or (v, u) in e:
            u = randint(1, n)
            v = randint(1, n)

        e.append((u, v))

    return e

def generate_string(n, alph):
    res = ''
    for i in range(n):
        res += chr(randint(0, alph - 1) + 97)
    return res

def generate_palindrome(n, alph):
    s = generate_string(n // 2, alph)

    if n % 2 == 0:
        return s + s[::-1]
    else:
        return s + chr(randint(0, alph - 1) + 97) + s[::-1]

def generate_array(n, l, r):
    return [randint(l, r) for i in range(n)]

def generate_permutation(n):
    a = [i for i in range(1, n + 1)]
    shuffle(a)
    return a

def generate():
    with open('input.txt', 'w') as fout:
        pass

def check(*args):
    if len(args) == 2:
        return args[0] == args[1]
    else:
        return args[0] == "Correct\n"

it = 0
while True:
    it += 1
    print('\riteration {0}'.format(it), end='')

    generate()

    out = popen('./main < input.txt').read().rstrip()
    ans = popen('./dumb < input.txt').read().rstrip()
    #ret = system('./main.py < input.txt > /dev/null')

    if not check(out, ans):
        break
