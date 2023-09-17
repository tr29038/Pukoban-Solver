# Pukoban-Solver
This project proposes an AI solver for pukoban (a variation of sokoban which permits pulling as well as pushing). Solution algorithms include: breadth first search, depth first search, A*, and greedy best-first search.

# Puzzle Formatting
A standalone puzzle must occupy its own file.

A puzzle can be of any size, MxN, where M > 0 and N > 0.

The following are permitted characters:
`O` denotes a wall/obstruction.
` ` denotes an empty space.
`R` denotes the robot, there must be one and only one robot.
`S` denotes a storage, there must be the same number of storages and boxes where each is > 1.
`B` denotes a box, there must be the same number of storages and boxes where each is > 1.

# Getting Started
Run the following commands:
```
git clone https://github.com/tr29038/Pukoban-Solver.git
cd <absolute-path/pukoban-solver>
```

# Compiling
Run the following commands:
```
cd ./build
./build.sh
make
```

# Running
Run the following command:
```
./pukoban_solver ../puzzles/puzzle_1.txt astar ./output.txt
```

For a list of options, run the command:
```
./pukoban_solver
```

# Algorithms
`bfs` = Breadth first search.
`dfs` = Depth first search.
`astar` = A*.
`gfs` = Greedy best-first search.
