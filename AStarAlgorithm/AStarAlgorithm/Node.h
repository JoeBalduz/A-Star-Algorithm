#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Node
{
private:
	string m_name;
	double m_distanceToPrevious;
	double m_x;
	double m_y;
	double m_straightLine;
	double m_totalDistanceTraveled;
	double m_estimatedDistance;
	Node*  m_previousNode;
public:
	vector<Node*> m_neighbors;
	bool m_visited;

	Node(string name, double x, double y);
	void printneighbors();
	void calculateDistance(Node* neighbor);
	void calculateStraightLine(Node* endPoint);
	void setPreviousNode(Node* node);
	void calculateDistanceTraveled(Node* prevNode);
	void calculateDistanceTraveledBFS(double prevDistance);
	void setStartingNode();
	string getName();
	double getDistance();
	double getStraightLine();
	Node* getPreviousNode();
	double getDistanceTraveled();
	double getEstimatedDistance();
	double getX();
	double getY();
	double getNewEstimatedDistance(Node* prevNode);


};

