#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <stack>
#include <set>
#include "Node.h"

using namespace std;

//Function declarations
vector<string> tokenizeWords(string line);

int main()
{
	string line, word;
	string start, end;
	string numberEntered;
	ifstream locations("locations.txt");
	ifstream connections("connections.txt");
	unordered_map<string, Node*> pointsMap;
	set<string> excludedCities;
	stack<Node*> optimalPath;
	string cityName;
	vector<string> tokens;
	vector<Node*> openPaths;
	bool pathFound = false;
	bool stepByStep;
	int i, j;
	Node* node;
	Node* current;
	double distance;
	double completeDistance = 0;
	double newEstimatedDistance;


	//Reads the locations file and tokenizes each line. Then creates a node and adds it to a hashmap
	if (locations.is_open())
	{
		while (getline(locations, line))
		{
			if (line != "END")
			{
				tokens = tokenizeWords(line);

				node = new Node(tokens[0], stoi(tokens[1]), stoi(tokens[2]));	//Name, X, and Y
				pointsMap[node->getName()] = node;
				tokens.clear();
			}
		}
		locations.close();
	}
	else
	{
		cout << "Locations file could not be open.\n";

		return -1;
	}

	//Reads the connections file and tokenizes each line. Then adds all neighbors to a point
	if (connections.is_open())
	{
		while (getline(connections, line))
		{
			if (line != "END")
			{
				tokens = tokenizeWords(line);

				for (i = 2; i < tokens.size(); i++)
				{

					if (tokens.size() > 2)
					{
						//This isn't a problem on windows but on linux the tokenization sometimes doesn't work correctly.
						//I don't know why that is. It will sometimes add an extra character to the end of the string
						if (pointsMap.find(tokens[i]) == pointsMap.end())
						{
							tokens[i].resize(tokens[i].length() - 1);
						}

					}
					//Adding neighbors of a point
					pointsMap[tokens[0]]->m_neighbors.push_back(pointsMap[tokens[i]]);
				}
				tokens.clear();
			}
		}
		connections.close();
	}
	else
	{
		cout << "Connections file could not be open.\n";

		return -1;
	}

	cout << "Enter in the starting point: ";
	cin >> start;

	if (pointsMap.find(start) == pointsMap.end())
	{
		cout << "Invalid starting point entered.";

		return -1;
	}

	cout << "Enter in the ending point: ";
	cin >> end;

	if (pointsMap.find(end) == pointsMap.end())
	{
		cout << "Invalid ending point entered.";

		return -1;
	}

	//Choose which cities to exclude
	while (true)
	{
		cout << "Enter in the name of a city to exclude or 0 to stop: ";
		cin >> cityName;

		if (cityName == "0")
		{
			break;
		}
		else if(pointsMap.find(cityName) == pointsMap.end())
		{
			cout << "Invalid city name entered. City not added.\n";
		}
		else
		{
			excludedCities.insert(cityName);
		}
	}

	cout << "Enter 1 for step-by-step or 0 for no step-by-step: ";
	cin >> numberEntered;

	if (numberEntered == "1")
	{
		stepByStep = true;
	}
	else if (numberEntered == "0")
	{
		stepByStep = false;
	}
	else
	{
		cout << "Invalid option chosen. Not showing step-by-step.\n";
		stepByStep = false;
	}

	//Begin A* algorithm

	//Starting point
	openPaths.push_back(pointsMap[start]);
	openPaths.front()->setStartingNode();
		
	while (!openPaths.empty())
	{
		current = openPaths.front();
		current->m_visited = true;
		openPaths.erase(openPaths.begin());

		if (stepByStep)
		{
			cout << "City selected: " << current->getName() << endl;
		}

		//End point has been found
		if (current->getName() == end)
		{
			pathFound = true;
			break;
		}

		if (stepByStep)
		{
			cout << "Possible cities where to travel: ";
			for (i = 0; i < current->m_neighbors.size(); i++)
			{
				if (excludedCities.find(current->m_neighbors[i]->getName()) == excludedCities.end())
				{
					if (current->getName() == start || current->m_neighbors[i]->getName() != current->getPreviousNode()->getName())
					{
						cout << current->m_neighbors[i]->getName() << " ";
					}
				}
			}
			cout << endl;
		}

		//Go through all neighbors and perform calculations
		for (i = 0; i < current->m_neighbors.size(); i++)
		{
			//Not in excluded cities list
			if (excludedCities.find(current->m_neighbors[i]->getName()) == excludedCities.end())
			{
				//Need to check and see if this neighbor has been visited already. If it has,
				//I need to get a new esimated distance. If this new estimated distance is lower than the current one,
				//overwrite the current one with the new one. Otherwise, nothing happens at all
				if (current->m_neighbors[i]->m_visited)
				{
					newEstimatedDistance = current->m_neighbors[i]->getNewEstimatedDistance(current);

					//New estimated distance is less than the current one. This path
					//should be used instead
					if (newEstimatedDistance < current->m_neighbors[i]->getEstimatedDistance())
					{
						current->m_neighbors[i]->calculateDistance(current);
						current->m_neighbors[i]->calculateDistanceTraveled(current);
						current->m_neighbors[i]->setPreviousNode(current);

						//Need to check if this neighbor is already an open path. If it is, it be removed and
						//then reinserted where it should go. If it's not in the list, it just needs to be inserted

						//Removes the path if it is already in the vector
						for (j = 0; j < openPaths.size(); j++)
						{
							if (openPaths[j]->getName() == current->m_neighbors[i]->getName())
							{
								openPaths.erase(openPaths.begin() + j);
								break;
							}
						}

						if (openPaths.empty())
						{
							openPaths.push_back(current->m_neighbors[i]);
						}
						else
						{
							//Insertion sort. Shortest path should be first
							for (j = 0; j < openPaths.size(); j++)
							{
								if (current->m_neighbors[i]->getEstimatedDistance() < openPaths[j]->getEstimatedDistance())
								{
									openPaths.insert(openPaths.begin() + j, current->m_neighbors[i]);
									break;
								}
								else if (j == openPaths.size() - 1)
								{
									openPaths.push_back(current->m_neighbors[i]);
									break;
								}
							}
						}
					}
				}
				else
				{
					current->m_neighbors[i]->calculateStraightLine(pointsMap[end]);
					current->m_neighbors[i]->calculateDistance(current);
					current->m_neighbors[i]->calculateDistanceTraveled(current);
					current->m_neighbors[i]->setPreviousNode(current);
					current->m_neighbors[i]->m_visited = true;

					if (openPaths.empty())
					{
						openPaths.push_back(current->m_neighbors[i]);
					}
					else
					{
						//Insertion sort. Shortest path should be first
						for (j = 0; j < openPaths.size(); j++)
						{
							if (current->m_neighbors[i]->getEstimatedDistance() < openPaths[j]->getEstimatedDistance())
							{
								openPaths.insert(openPaths.begin() + j, current->m_neighbors[i]);
								break;
							}
							else if (j == openPaths.size() - 1)
							{
								openPaths.push_back(current->m_neighbors[i]);
								break;
							}
						}
					}
				}
			}
		}
		if (stepByStep)
		{
			cout << "Cities at the end of possible paths: ";
				
			for (i = 0; i < openPaths.size(); i++)
			{
				cout << openPaths[i]->getName() << "(" << openPaths[i]->getEstimatedDistance() << ") ";
			}
			cout << endl;
		}
	}

	if (pathFound)
	{
		while (true)
		{
			optimalPath.push(current);

			if (current->getName() == start)
			{
				break;
			}

			current = current->getPreviousNode();
		}

		cout << "The final solution path is: " << endl;

		current = optimalPath.top();
		optimalPath.pop();

		while (!optimalPath.empty())
		{
			distance = optimalPath.top()->getDistance();
			completeDistance += distance;
			cout << current->getName() << " to " << optimalPath.top()->getName() << " length " << distance << endl;
			current = optimalPath.top();
			optimalPath.pop();
		}

		cout << "Total distance is " << completeDistance << endl;
	}
	else
	{
		cout << "No path could be found.\n";
	}


	//Used to keep the console open within visual studio
	cin.get();
	cin.get();

	return 0;
}

//Tokenizes the string
vector<string> tokenizeWords(string line)
{
	string word = "";
	vector<string> tokens;
	int i;

	for (i = 0; i < line.length(); i++)
	{
		if (line[i] != ' ')
		{
			word += line[i];
		}
		else
		{
			tokens.push_back(word);
			word = "";
		}

		if (i == line.length() - 1)
		{
			tokens.push_back(word);
		}
	}

	return tokens;
}
