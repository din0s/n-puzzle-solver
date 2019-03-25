#include <iostream>
#include <chrono>
#include "DataStructs.h"


template<typename T>
int search(State &solution, std::set<State> &closed, T &agenda, int iter) {
    while (!agenda.empty()) {
        State next = agenda.top();
        agenda.pop();

        if (next.isFinished()) {
            solution = next;
            return iter;
        }

        if (closed.empty() || closed.find(next) == closed.end()) {
            closed.insert(next);

            std::vector<State> children = next.expand();
            for (State &s : children) {
                agenda.push(s);
            }
        }

        iter++;
    }

    return -1;
}

int dfs(State &solution, std::set<State> &closed, std::stack<State> &agenda) {
    return search(solution, closed, agenda, 0);
}

int bfs(State &solution, std::set<State> &closed, my_queue &agenda) {
    return search(solution, closed, agenda, 0);
}

int bestfs(State &solution, std::set<State> &closed, my_priority_queue &agenda) {
    return search(solution, closed, agenda, 0);
}

int main() {
    int width, height, algo;
    std::cout << "Insert width: ";
    std::cin >> width;
    std::cout << "Insert height: ";
    std::cin >> height;
    std::cout << std::endl;

    State start;
    bool tryAgain;

    do {
        tryAgain = false;

        start = State(width, height);
        std::cout << "Start: " << std::endl
                  << start.toString() << std::endl;

        if (!start.isSolvable()) {
            std::cout << "Starting layout is not solvable! Try again? (y/N)" << std::endl;

            std::string in;
            std::cin >> in;
            std::cout << std::endl;

            tryAgain = std::tolower(in[0]) == 'y';
            if (!tryAgain) {
                return 0;
            }
        }
    } while (tryAgain);

    std::cout << "Select algorithm (1/2/3): " << std::endl
              << "1) Depth First Search" << std::endl
              << "2) Breadth First Search" << std::endl
              << "3) Best First Search" << std::endl;
    std::cin >> algo;
    std::cout << std::endl;

    int iterations;
    auto time0 = std::chrono::high_resolution_clock::now();

    State end;
    std::set<State> closedSet;

    switch (algo) {
        case 1: {
            std::stack<State> agenda;
            agenda.push(start);
            iterations = dfs(end, closedSet, agenda);
            break;
        }

        case 2: {
            my_queue agenda;
            agenda.push(start);
            iterations = bfs(end, closedSet, agenda);
            break;
        }

        default: {
            my_priority_queue agenda;
            agenda.push(start);
            iterations = bestfs(end, closedSet, agenda);
            break;
        }
    }

    if (iterations > 0) {
        auto time1 = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time1 - time0).count();

        std::cout << "Solution: (" << iterations << " iterations / " << ms << "ms)" << std::endl;
        for (std::string &s : end.getPath()) {
            std::cout << "- " << s << std::endl;
        }

        std::cout << "Result: " << std::endl
                  << end.toString();
    } else {
        std::cout << "No solution!" << std::endl;
    }

    return 0;
}
