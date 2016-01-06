#!/bin/sh
./push_swap `ruby -e "puts (-20..20).to_a.shuffle.join(' ')"` -md
#./push_swap -4 5 2 -3 3 4 -5 -2 -8 -9 -10 7 -7 1 10 9 6 -6 8 0 -1 -md
