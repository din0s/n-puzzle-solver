# n-puzzle-solver
Project #1 for Artificial Intelligence, 4th semester at Computer Science | AUTh.

## Problem representation
In order to solve the n-puzzle problem, we need a State object
that contains information such as the contents of each tile
as well as the dimensions of the puzzle, the location of the blank tile
and a vector that contains all steps taken from the starting layout.

Within that class, I implemented a few methods that are responsible for moving
the blank tile on all 4 directions, some operator overloads that are utilised by
the data structs needed for the algorithms, a few other methods that evaluate the
current state (useful for the heuristic function) and convenience methods that determine
whether the puzzle is solved, how to print the state as well as the path of steps taken
and how to expand the current state into all of its children.

## Depth First Search
This algorithm is implemented using a stack for the agenda.
I opted for a non-recursive solution to decrease memory allocation on the stack,
which might have caused overflows and unwanted program crashes.

However, for the given starting state, this algorithm cannot finish execution before
throwing a bad_alloc() exception, when the system runs out of memory.
The explanation for this behavior is that the algorithm gets stuck exploring a path
of steps that won't give us the solution and thus runs out of time.

Here's the starting position for posterity:

||||
|---|---|---|
| 6 | 7 | 1 |
|   | 3 | 2 |
| 8 | 5 | 4 |


## Breadth First Search
This algorithm is similar to [DFS](#depth-first-search), but it uses a queue for the agenda.

Although this algorithm is memory-heavy, it's always going to give us the best solution possible.
Beware that a complex staring layout may also cause the program to crash due to the aforementioned
intensiveness of this algorithm for the system's memory.

For the given starting state, we get the following results:
```
Solution: (126903 iterations / 109194ms)
- UP
- RIGHT
- RIGHT
- DOWN
- LEFT
- LEFT
- UP
- RIGHT
- RIGHT
- DOWN
- DOWN
- LEFT
- UP
- RIGHT
- DOWN
- LEFT
- LEFT
- UP
- RIGHT
- RIGHT
- DOWN
```

We can see that the algorithm lasted a little under 2 minutes and gave us a solution that is
only 20 steps long.

## Best First Search
This algorithm is non-recursive as well and uses a priority queue for the agenda.

It is by far the best option for this problem since the use of heuristic functions makes it
a non-blind algorithm, which means that the steps every time are carefully chosen so that we
get closer to the solution.

The heuristic function used for this problem is counting how many tiles are out of place.
A lower value means that the puzzle is closer to being completed.
Other functions that were tried but weren't as successful is the manhattan distance of
each tile from its destination position, as well as counting the length of the solution path.

Its execution bears the following results:
```
Solution: (230 iterations / 108ms)
- UP
- RIGHT
- RIGHT
- DOWN
- LEFT
- DOWN
- LEFT
- UP
- UP
- RIGHT
- RIGHT
- DOWN
- LEFT
- DOWN
- LEFT
- UP
- RIGHT
- DOWN
- RIGHT
- UP
- LEFT
- DOWN
- LEFT
- UP
- RIGHT
- DOWN
- RIGHT
- UP
- LEFT
- DOWN
- LEFT
- UP
- RIGHT
- RIGHT
- DOWN
- LEFT
- UP
- LEFT
- DOWN
- RIGHT
- RIGHT
```

The solution isn't as short as the one [BFS](#best-first-search) returned, but the computation
time is orders of magnitude faster!
