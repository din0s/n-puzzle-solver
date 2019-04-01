#include <chrono>
#include <algorithm>
#include <random>
#include <sstream>
#include <iostream>
#include "State.h"

/*
 * Public methods
 */

State::State() {
    tiles = nullptr;
    width = 0;
    height = 0;
    size = 0;
    blank = {0, 0};
}

State::State(int w, int h) {
    width = w;
    height = h;
    size = w * h;

    int *numbers = new int[size];
    for (int i = 0; i < size; i++) {
        numbers[i] = i;
    }

    long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::shuffle(&numbers[0], &numbers[size], std::default_random_engine(seed));

//    int numbers[] = {6, 7, 1, 0, 3, 2, 8, 5, 4};

    tiles = new int *[height];
    for (int i = 0; i < height; i++) {
        tiles[i] = new int[width];

        for (int j = 0; j < width; j++) {
            tiles[i][j] = numbers[i * width + j];

            if (tiles[i][j] == 0) {
                blank.height = i;
                blank.width = j;
            }
        }
    }

    delete[] numbers;
}

State::State(const State &s) {
    width = s.width;
    height = s.height;
    size = s.size;
    path = s.path;

    blank = s.blank;
    tiles = new int *[height];
    for (int i = 0; i < height; i++) {
        tiles[i] = new int[width];

        for (int j = 0; j < width; j++) {
            tiles[i][j] = s.tiles[i][j];
        }
    }
}

State::~State() {
    delete[] tiles;
    path.clear();
}

std::string State::toString() const {
    long maxLength = std::to_string(size - 1).length();

    std::stringstream out;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int num = tiles[i][j];
            if (num == 0) {
                for (int k = 0; k < maxLength; k++) {
                    out << "_";
                }
                out << " ";
            } else {
                long numLength = std::to_string(num).length();
                for (long k = numLength; k < maxLength; k++) {
                    out << " ";
                }
                out << num << " ";
            }
        }
        out << std::endl;
    }
    return out.str();
}

State &State::operator=(const State &o) {
    width = o.width;
    height = o.height;
    size = o.size;
    path = o.path;

    blank = o.blank;
    tiles = new int *[height];
    for (int i = 0; i < height; i++) {
        tiles[i] = new int[width];

        for (int j = 0; j < width; j++) {
            tiles[i][j] = o.tiles[i][j];
        }
    }

    return *this;
}

bool State::isSolvable() {
    int swaps = 0;
    int flatTiles[size];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            flatTiles[height * i + j] = tiles[i][j];
        }
    }

    for (int i = 0; i < size; i++) {
        int tile = flatTiles[i];
        if (tile == 0) continue;

        for (int j = i + 1; j < size; j++) {
            int nextTile = flatTiles[j];
            if (nextTile == 0) continue;

            if (tile > nextTile) {
                swaps++;
            }
        }
    }

    bool evenSwaps = swaps % 2 == 0;
    bool blankOddRow = (height - blank.height) % 2 == 1;

    // Giving credit where credit is due.
    // http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
    return width == 0 ? blankOddRow == evenSwaps : evenSwaps;
}

bool State::isFinished() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int expected = 1 + i * width + j;
            int actual = tiles[i][j];

            if (expected == size) {
                if (actual != 0) {
                    return false;
                }
            } else {
                if (actual != expected) {
                    return false;
                }
            }
        }
    }
    return true;
}

int State::manhattan() {
    int score = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int value = tiles[i][j];
            int posX = value / width;
            int posY = value % width;
            score += abs(posX - i) + abs(posY - j);
        }
    }
    return score;
}

int State::inPlace() {
    int score = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int value = tiles[i][j];
            int expected = 1 + i * width + j;
            if (value == expected || expected == size)
                score++;
        }
    }
    return score;
}

std::vector<State> State::expand() {
    std::vector<State> children;

    State s;
    if (moveUp(s))
        children.push_back(s);

    if (moveDown(s))
        children.push_back(s);

    if (moveLeft(s))
        children.push_back(s);

    if (moveRight(s))
        children.push_back(s);

    return children;
}

/*
 * Private Methods
 */

void State::moveBlank(Coords c) {
    Coords moveFrom = blank;
    blank.height += c.height;
    blank.width += c.width;

    int num = tiles[blank.height][blank.width];
    tiles[moveFrom.height][moveFrom.width] = num;
    tiles[blank.height][blank.width] = 0;
}

void State::moveX(int x) {
    moveBlank({x, 0});
}

void State::moveY(int y) {
    moveBlank({0, y});
}

bool State::moveUp(State &s) {
    if (blank.height == 0) {
        return false;
    }

    s = *this;
    s.moveX(-1);
    s.path.emplace_back("UP");
    return true;
}

bool State::moveDown(State &s) {
    if (blank.height == height - 1) {
        return false;
    }

    s = *this;
    s.moveX(+1);
    s.path.emplace_back("DOWN");
    return true;
}

bool State::moveLeft(State &s) {
    if (blank.width == 0) {
        return false;
    }

    s = *this;
    s.moveY(-1);
    s.path.emplace_back("LEFT");
    return true;
}

bool State::moveRight(State &s) {
    if (blank.width == width - 1) {
        return false;
    }

    s = *this;
    s.moveY(+1);
    s.path.emplace_back("RIGHT");
    return true;
}
