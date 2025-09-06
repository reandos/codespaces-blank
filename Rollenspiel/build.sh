#!/bin/bash
set -e
gcc -std=c11 -Wall -Wextra -Werror -O2 -g -o Rollenspiel *.c
./Rollenspiel