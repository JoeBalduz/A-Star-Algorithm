#include "Node.h"



Node::Node(string name, double x, double y)
{
	m_name = name;
	m_x = x;
	m_y = y;
	m_visited = false;
}

//Used for debugging
void Node::printneighbors()
{
	for (int i = 0; i < m_neighbors.size(); i++)
	{
		cout << m_neighbors[i]->getName() << " ";
	}
	cout << endl;
}

//Find distance to neighbor
void Node::calculateDistance(Node* neighbor)
{
	double squaredX, squaredY;

	squaredX = pow(neighbor->getX() - m_x, 2);
	squaredY = pow(neighbor->getY() - m_y, 2);

	m_distanceToPrevious = sqrt(squaredX + squaredY);
}

//Finds straight line distance to endpoint
void Node::calculateStraightLine(Node* endPoint)
{
	double squaredX, squaredY;

	squaredX = pow(endPoint->getX() - m_x, 2);
	squaredY = pow(endPoint->getY() - m_y, 2);

	m_straightLine = sqrt(squaredX + squaredY);
}

//Finds the distance traveled by actual distance
void Node::calculateDistanceTraveled(Node* prevNode)
{
	m_totalDistanceTraveled = m_distanceToPrevious + prevNode->getDistanceTraveled();

	m_estimatedDistance = m_totalDistanceTraveled + m_straightLine;
}

//Finds the distance traveled by city number
void Node::calculateDistanceTraveledBFS(double prevDistance)
{
	m_totalDistanceTraveled = prevDistance + 1;

	m_distanceToPrevious = 1;
}

//Sets the previous node
void Node::setPreviousNode(Node* node)
{
	m_previousNode = node;
}

//Initializes the starting node
void Node::setStartingNode()
{
	m_totalDistanceTraveled = 0;
}

//Returns name
string Node::getName()
{
	return m_name;
}

//Returns distance to neighbor
double Node::getDistance()
{
	return m_distanceToPrevious;
}

//Returns distance to endpoint
double Node::getStraightLine()
{
	return m_straightLine;
}

//Returns the previous node
Node* Node::getPreviousNode()
{
	return m_previousNode;
}

//Returns the distance traveled
double Node::getDistanceTraveled()
{
	return m_totalDistanceTraveled;
}

//Returns the estimated distance
double Node::getEstimatedDistance()
{
	return m_estimatedDistance;
}

//Returns the x coordinate
double Node::getX()
{
	return m_x;
}

//Returns the y coordinate
double Node::getY()
{
	return m_y;
}

//Returns a new estimated distance. For use when an open path is reached from a different location
double Node::getNewEstimatedDistance(Node* prevNode)
{
	double squaredX, squaredY;
	double distanceToPrevious, totalDistanceTraveled, estimatedDistance;

	squaredX = pow(prevNode->getX() - m_x, 2);
	squaredY = pow(prevNode->getY() - m_y, 2);

	distanceToPrevious = sqrt(squaredX + squaredY);

	totalDistanceTraveled = distanceToPrevious + prevNode->getDistanceTraveled();

	estimatedDistance = totalDistanceTraveled + m_straightLine;

	return estimatedDistance;
}