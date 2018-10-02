# A-Star-Algorithm

This program is an implementation of the A* algorithm. It is used to find the shortest distance between any two points in a smarter
way.

Inside of AStarAlgorithm/AStarAlgorithm/ there is a locations.txt file and a connections.txt. The locations.txt file holds the locations
of every point on the map. It is formated in the following way.

POINT_NAME X-COORDINATE Y-COORDINATE

As long as that format is kept, points can be added, removed, or changed. The connections.txt holds the connections between points. It is
formatted in the following way.

POINT_NAME NUMBER_OF_NEIGHBORS NEIGHBOR_1 NEIGHBOR_2 ... NEIGHBOR_N

As long as that format is kept, neighbors can be added, removed, or changed.
