#ifndef AI1_DATASTRUCTS_H
#define AI1_DATASTRUCTS_H


#include <queue>
#include <set>
#include <stack>
#include "State.h"

struct compareStates {
    bool operator()(State &a, State &b) {
        return a.inPlace() < b.inPlace();
    }
};

class my_queue : public std::queue<State> {
public:
    State top() {
        return front();
    }
};

class my_priority_queue : public std::priority_queue<State, std::vector<State>, compareStates> {
};

#endif //AI1_DATASTRUCTS_H
