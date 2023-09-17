#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Correct usage: $0 <dfs|bfs|gfs|astar>"
    exit 1
fi

if [[ ! -d ../puzzles/solutions/$1 ]]
then
    mkdir -p ../puzzles/solutions/$1
fi

ls ../puzzles -p | grep -v / | xargs -I % ./pukoban_solver ../puzzles/% $1 ../puzzles/solutions/$1/%.out
