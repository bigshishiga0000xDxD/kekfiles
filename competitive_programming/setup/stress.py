#!/bin/python3

from random import randint
from random import choice
from random import shuffle
from os import popen
from os import system
from time import sleep

def generate():
    with open('input.txt', 'w') as fout:
        n = randint(1, 10)
        fout.write(str(n) + '\n')

it = 0
while True:
    generate()

    out = popen('./main.out < input.txt').read()
    ans = popen('./dumb.out < input.txt').read()

    if out != ans:
        print(popen('cat input.txt').read())
        print(out)
        print(ans)
        break

    it += 1
    print('\riteration {0}'.format(it), end='')
