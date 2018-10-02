# A-Star-Algorithm

This program is an implementation of the A* algorithm. It is used to find the shortest distance between any two points in a smarter
way.

Inside of AStarAlgorithm/AStarAlgorithm/ there is a locations.txt file and a connections.txt. The locations.txt file holds the locations
of every point on the map. It is formated in the following way.

POINT_NAME X-COORDINATE Y-COORDINATE

As long as that format is kept, points can be added, removed, or changed. The connections.txt holds the connections between points. It is
formatted in the following way.

POINT_NAME NUMBER_OF_NEIGHBORS NEIGHBOR_1 NEIGHBOR_2 ... NEIGHBOR_N

As long as that format is kept, neighbors can be added, removed, or changed. All source code can be found in
AStarAlgorithm/AStarAlgorithm/.

# Running the Program
This program can be run in both Windows and Linux. In Windows, the project can be loaded into visual studio and run there. For Linux,
navigate to AStarAlgorithm/AStarAlgorithm/. There, you'll find a makefile that can be used to compile to program. Use ./astar to run
the program.

$ make

$ ./astar

Once the program has started, it will ask you to enter in a starting point and an ending point. All point names are case-sensitive so
make sure to enter the point names exactly as they appear in locations.txt. After that, you can choose to exclude cities from the path.
If you do choose to exclude cities, remember to make sure that their name is entered in exacltly as they appear in locations.txt. You'll
then be given a choice of choosing from step-by-step or no step-by-step. Step-by-step means that the algorithm will print out all of the
moves it makes in the process of finding the shortest path, which was useful in debugging. It will show the current "city" it has
selected, the possible "cities" where to travel to, and the "cities" at the end of all possible paths along with the distance assigned
to that "city".Choosing no step-by-step will only give you the end result, which is the shortest path.

# Example Run of the Program

Enter in the starting point: A1

Enter in the ending point: C4

Enter in the name of a city to exclude or 0 to stop: 0

Enter 1 for step-by-step or 0 for no step-by-step: 1

City selected: A1

Possible cities where to travel: B1 A2

Cities at the end of possible paths: A2(459.014) B1(572.41)

City selected: A2

Possible cities where to travel: B2 A4

Cities at the end of possible paths: B1(572.41) B2(590.388) A4(634.06)

City selected: B1

Possible cities where to travel: D1 B2

Cities at the end of possible paths: B2(572.574) A4(634.06) D1(856.769)

City selected: B2

Possible cities where to travel: C2 C3 A2

Cities at the end of possible paths: C3(576.941) C2(623.941) A4(634.06) D1(856.769)

City selected: C3

Possible cities where to travel: C2 C4

Cities at the end of possible paths: C4(576.941) C2(623.941) A4(634.06) D1(856.769)

City selected: C4

The final solution path is:

A1 to B1 length 177

B1 to B2 length 113

B2 to C3 length 131.217

C3 to C4 length 155.724

Total distance is 576.941
