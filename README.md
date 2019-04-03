# n-puzzle-solver
Project #1 for Artificial Intelligence, 4th semester at Computer Science | AUTh.

## Problem representation
In order to solve the n-puzzle problem, we need a State object
that contains information such as the contents of each tile
as well as the dimensions of the puzzle, the location of the blank tile
and the previous state of the problem that produced the current one.

Within that class, I implemented a few methods that are responsible for moving
the blank tile on all 4 directions, some operator overloads that are utilised by
the data structs needed for the algorithms, a few other methods that evaluate the
current state (useful for the heuristic function) and convenience methods that determine
whether the puzzle is solved, how to print the state as well as the path of the states
we followed and how to expand the current state into all of its children.

## Depth First Search
This algorithm is implemented using a stack for the agenda.
I opted for a non-recursive solution to decrease memory allocation on the stack,
which might have caused overflows and unwanted program crashes.

I originally had issues with the implementation since during runtime, the algorithm
would explore long solution paths which had a huge memory footprint, and thus couldn't
continue the execution after a number of iterations.
This issue was solved with backtracking.

Τhe algorithm returns the following solution:

```
Solution:
[...]
Completed in 58441 steps.
95585 iterations / 15986ms
```

We can easily notice that the solution is far from optimal, since this blind algorithm might
get stuck in long paths trying to solve the problem even if it's actually straying away from it.

## Breadth First Search
This algorithm is similar to [DFS](#depth-first-search), but it uses a queue for the agenda.

Although this algorithm is memory-heavy, it's always going to give us the best solution possible.
Beware that a complex staring layout may also cause the program to crash due to the aforementioned
intensiveness of this algorithm for the system's memory.

For the given starting state, we get the following results:
```
Solution:
[...]
Completed in 21 steps.
126903 iterations / 20713ms
```

We can see that the algorithm lasted a little over 20 seconds and gave us a solution that is
only 21 steps long.

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
Solution:
[...]
Completed in 41 steps.
230 iterations / 75ms
```

The solution isn't as short as the one [BFS](#best-first-search) returned, but the computation
time is orders of magnitude faster!

## Implementation Comments
A few of the things I noticed while working on this project were:
- Saving the steps we followed for each state we visit created memory issues
and had to be replaced with backtracking.
- The heuristic function "Manhattan Distance" had a slower runtime and
was replaced with "Tiles In Place".
- I used templates for the implementation of the algorithms since their
only difference is in the data structure their agenda uses.
- The check for whether the problem is solvable is based on
[this article](http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html).