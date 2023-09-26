#include <grid.h>

#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Correct usage: " << argv[0] << " <puzzle/file/path> <dfs|bfs|astar|gfs> <path/to/output/file>\n";
        return 1;
    }

    std::unique_ptr<Grid> grid;
    try
    {
        grid = std::make_unique<Grid>(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cout << "Error parsing puzzle: " << e.what() << '\n';
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<State> solution_path;
    try
    {
        solution_path = grid->solve(argv[2]);
    }
    catch (const std::exception& e)
    {
        std::cout << "Error solving puzzle: " << e.what() << '\n';
        return 1;
    }

    if (solution_path.empty())
    {
        std::cout << "The puzzle is unsolveable.\n";
        return 0;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout
        << "Time to solve " << argv[1]
	    << " with " << (solution_path.size() - 1) << " moves using " << argv[2] << ": "
	    << duration_s.count() << '.' << (duration_ms.count() % 100) << "s\n";

    // Output solution path.
    std::ofstream output(argv[3]);
    while (!solution_path.empty())
    {
        auto step = solution_path.back();
        grid->print(step, output);
        output << '\n';
        solution_path.pop_back();
    }

    return 0;
}
