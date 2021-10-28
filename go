#!/usr/bin/env sh
set -ex

rm -rf out
mkdir out

clang -O3 -c a.c -o out/a.o
clang -O3 -c b.c -o out/b.o

objdump -d out/a.o > out/a.S
objdump -d out/b.o > out/b.S

wc out/a.S out/b.S
diff -y out/a.S out/b.S
