#!/bin/bash

declare -a algs=("astar" "gfs" "bfs" "dfs")

for alg in "${algs[@]}"
do
    echo "Working with $alg..."

    if [[ ! -d ./solutions/$alg ]]; then
        echo "Created directory ./solutions/$alg"
        mkdir -p ./solutions/$alg
    fi

    ./pukoban_solver ../puzzles/puzzle_7.txt $alg ./solutions/$alg/puzzle_7.solution
    ./pukoban_solver ../puzzles/puzzle_6.txt $alg ./solutions/$alg/puzzle_6.solution
    ./pukoban_solver ../puzzles/puzzle_5.txt $alg ./solutions/$alg/puzzle_5.solution
done
