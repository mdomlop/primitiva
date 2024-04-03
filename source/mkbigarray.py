#!/usr/bin/env python

n = 100000000
print("#define N", n)
print("int a[N] = {0, ")
for i in range(1, n):
    print(i,", ")
print("};")
