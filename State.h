#ifndef AI1_STATE_H
#define AI1_STATE_H


#include <vector>
#include <string>

struct Coords {
    int height, width;
};

class State {
private:
    int **tiles;
    Coords blank;
    int width, height, size;
    std::vector<std::string> path;

    void moveBlank(Coords c);

    void moveX(int);

    void moveY(int);

    bool moveUp(State &);

    bool moveDown(State &);

    bool moveLeft(State &);

    bool moveRight(State &);

public:
    /*
     * Constructors, destructors etc.
     */

    State();

    State(int, int);

    State(const State &);

    ~State();

    /*
     * Operator overloads.
     */

    State &operator=(const State &);

    friend bool operator<(const State &a, const State &b) {
        return a.toString() < b.toString();
    }

    /*
     * Other methods.
     */

    bool isSolvable();

    bool isFinished();

    int manhattan();

    int inPlace();

    std::string toString() const;

    std::vector<State> expand();

    std::vector<std::string> getPath() { return path; }
};


#endif //AI1_STATE_H
