#include "CityController.h"

CityController* CityController::instance = nullptr;

CityController* CityController::getInstance() {
	if (!instance)
		instance = new CityController;
	return instance;
}

CityController::CityController() {

	streets = {};
	nodes = {};
}

bool CityController::isInIntervalX(Position point, Street * range) {

	int upper = range->getStartEndPositions().first.x > range->getStartEndPositions().second.x ? range->getStartEndPositions().first.x : range->getStartEndPositions().second.x;
	int lower = range->getStartEndPositions().first.x < range->getStartEndPositions().second.x ? range->getStartEndPositions().first.x : range->getStartEndPositions().second.x;
	if ((unsigned) (point.x - lower) <= (upper - lower))
		return true;
	else
		return false;
}
bool CityController::isInIntervalY(Position point, Street * range) {
	int upper = range->getStartEndPositions().first.y > range->getStartEndPositions().second.y ? range->getStartEndPositions().first.y : range->getStartEndPositions().second.y;
	int lower = range->getStartEndPositions().first.y < range->getStartEndPositions().second.y ? range->getStartEndPositions().first.y : range->getStartEndPositions().second.y;
	if ((unsigned) (point.y - lower) <= (upper - lower))
		return true;
	else
		return false;
}

bool CityController::isStreetExist(Node * start, Node * end) {
	for (Street *stre : streets) {
		if (stre->getNodes().first == start && stre->getNodes().second == end)
			return true;
	}
	return false;
}

bool CityController::addStreet(Position start, Position end, bool twoWay) {
	Node *s = findNode(start);
	Node *e = findNode(end);

	if (isStreetExist(s, e)) return false;

	if (isStreetsOverlap(start, end)) return false;

	std::map<Street*, Position> cross = isStreetsCross(start, end);
	if (cross.empty()) {
		if (s == nullptr) {
			s = new Node(start);
			nodes.push_back(s);
		}
		if (e == nullptr) {
			e = new Node(end);
			nodes.push_back(e);
		}
		createStreet(s, e, twoWay);
		return true;
	} else {
		if (handleCrossSteets(start, end, twoWay, cross))
			return true;
		else
			return false;
	}
}

bool CityController::handleCrossSteets(Position start, Position end, bool twoWay, std::map<Street*, Position> map) {
	
	Node *s = findNode(start);
	Node *e = findNode(end);
	std::list<Node*> crossingNodes = {};
	for (std::pair<Street*, Position> crossingStreet : map) {
		std::pair<Position, Position> cStreetPositions = crossingStreet.first->getStartEndPositions();
		if (cStreetPositions.first == crossingStreet.second ||
			cStreetPositions.second == crossingStreet.second)
			continue;

		Node *middle = findNode(crossingStreet.second);

		if (isStreetExist(middle, crossingStreet.first->getNodes().second))
			if (isStreetExist(crossingStreet.first->getNodes().first, middle))
				return false;

		if (middle == nullptr) {
			middle = new Node(crossingStreet.second);;
			nodes.push_back(middle);
		}

		crossingNodes.push_back(middle);
		streets.push_back(new Street(middle, crossingStreet.first->getNodes().second));
		crossingStreet.first->alterEnd(middle);
	}

	crossingNodes.sort([](const Node *a, const Node *b) {
		if (a->position.x == b->position.x)
			return a->position.y < b->position.y;
		else
			return a->position.x < b->position.x;
	});
	filterList(&crossingNodes);


	if (s == nullptr) {
		s = new Node(start);
		nodes.push_back(s);
	}
	if (e == nullptr) {
		e = new Node(end);
		nodes.push_back(e);
	}
	//TODO: Another possibility, if you like using the BOOST_FOREACH macro is to use the BOOST_REVERSE_FOREACH macro introduced in Boost 1.36.0.
	if (Street::getPredictedDirection(start, end) == E || Street::getPredictedDirection(start, end) == S) {

		createStreet(s, crossingNodes.front(), twoWay);
		createStreet(crossingNodes.back(), e, twoWay);
		if(crossingNodes.size() > 1)
			for (auto it = crossingNodes.begin(); it != crossingNodes.end(); ++it) {

				createStreet(*it, *std::next(it), twoWay);
				if (std::next(it, 2) == crossingNodes.end()) {
					break;
				}
			}
	} else if (Street::getPredictedDirection(start, end) == W || Street::getPredictedDirection(start, end) == N) {
		createStreet(s, crossingNodes.back(), twoWay);
		createStreet(crossingNodes.front(), e, twoWay);
		if (crossingNodes.size() > 1)
			for (auto it = crossingNodes.end(); it != crossingNodes.begin(); --it) {

				createStreet(*it, *std::prev(it), twoWay);

				if (std::prev(it, 2) == crossingNodes.begin()) {
					break;
				}
			}
	}
	return true;
}

std::map<Street*, Position> CityController::isStreetsCross(Position start, Position end) {
	Direction d = Street::getPredictedDirection(start, end);
	std::map<Street*, Position> output;
	output = {};
	for (Street *s : streets) {
		Direction ccStreetDir = s->getDirection();
		//Streets are perpendicular
		int computedDir1 = d + 1;
		int computedDir2 = d + 3;
		if (ccStreetDir == computedDir1 % 4 || ccStreetDir == computedDir2 % 4) {
			if (d == N) {
				if (s->getStartEndPositions().first.y < start.y &&
					s->getStartEndPositions().first.y > end.y) {
					if (isInIntervalX(start, s)) {
						output[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			} else if (d == E) {
				if (s->getStartEndPositions().first.x < end.x &&
					s->getStartEndPositions().first.x > start.x) {
					if (isInIntervalY(start, s)) {
						output[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == W) {
				if (s->getStartEndPositions().first.x < start.x &&
					s->getStartEndPositions().first.x > end.x) {
					if (isInIntervalY(start, s)) {
						output[s] = Position(s->getStartEndPositions().first.x, start.y);
					}
				} else
					continue;
			} else if (d == S) {
				if (s->getStartEndPositions().first.y < end.y &&
					s->getStartEndPositions().first.y > start.y) {
					if (isInIntervalX(start, s)) {
						output[s] = Position(start.x, s->getStartEndPositions().first.y);
					}
				} else
					continue;
			}
		} else { //Streets are parallel
				 //Nothing happens
		}
	}
	return output;
}

void CityController::createStreet(Node * start, Node * end, bool twoWay) {
	streets.push_back(new Street(start, end));
	if (twoWay) {
		streets.push_back(new Street(end, start));
	}
}

Node * CityController::findNode(Position p) {
	Node *out = nullptr;

	for (Node *n : nodes) {
		if (n->getPosition() == p) {
			out = n;
			continue;
		}
		if (out != nullptr)
			break;
	}
	return out;
}

Node * CityController::findAndCraeteNode(Position p) {
	Node *out = nullptr;

	for (Node *n : nodes) {
		if (n->getPosition() == p) {
			out = n;
			continue;
		}
		if (out != nullptr)
			break;
	}
	if (out == nullptr) {
		out = new Node(p);
		nodes.push_back(out);
	}
	return out;
}

std::list<Street*> CityController::getStreets() {
	return streets;
}

std::list<Node*> CityController::getNodes() {
	return nodes;
}

std::list<std::list<Node*>> CityController::getWay(Node * start)
{
	std::list<Node*> path = {};
	std::list<Node*> neighbors = {};
	std::list<Node*> listOfWhiteNodes(nodes);
	std::list<Node*> listOfGrayNodes = {};
	std::list<Node*> listOfBlackNodes = {};
	std::list<std::list<Node*>> found = {};

	if (start == NULL)
		return found;

	listOfWhiteNodes.remove(start);
	listOfGrayNodes.push_back(start);
	path.push_back(start);
	found.push_back(path);
	while (!listOfGrayNodes.empty())
	{
		std::list<Node*> copyOflistOfGrayNodes(listOfGrayNodes);
		for(Node * nodeInCurrentStep : copyOflistOfGrayNodes)
		{
			neighbors = findNeighbors(nodeInCurrentStep);
			for(std::list<Node*> pathiInFinder : found)
			{
				if (pathiInFinder.back() == nodeInCurrentStep)
					path = pathiInFinder;
			}

			for(Node * nodeProcessing : neighbors)
			{
				if (std::find(listOfWhiteNodes.begin(), listOfWhiteNodes.end(), nodeProcessing) != listOfWhiteNodes.end())
				{
					std::list<Node*> newPath(path);
					listOfGrayNodes.push_back(nodeProcessing);
					listOfWhiteNodes.remove(nodeProcessing);
					newPath.push_back(nodeProcessing);
					found.push_back(newPath);
				}
			}
			listOfBlackNodes.push_back(nodeInCurrentStep);
			listOfGrayNodes.remove(nodeInCurrentStep);
		}
	}

	return found;
}

std::list<Node*> CityController::findNeighbors(Node * n)
{
	std::list<Node*> neighborNodes = {};
	for (Street * s : streets)
		if (s->getNodes().first == n)
			neighborNodes.push_back(s->getNodes().second);
	
	/*auto nodeConnections = std::find_if(streets.begin(), streets.end(),[n](Street * m) -> bool { return m->getNodes().first == n; });
	for (auto it = nodeConnections; it != streets.end(); ++it) {
		Street * s = *it;
		neighborNodes.push_back(s->getNodes().second);
	}*/
	return neighborNodes;
}

void CityController::filterList(std::list<Node *> *list) {
	auto it = std::unique(list->begin(), list->end(),
						  [](const Node *a, const Node *b) {
		return a->position.x == b->position.x && a->position.y == b->position.y;
	});
	list->erase(it, list->end());
}

bool CityController::isStreetsOverlap(Position start, Position end) {

	Street temp(&Node(start), &Node(end));
	if (Street::getPredictedDirection(start, end) == N || Street::getPredictedDirection(start, end) == S)
		for (Street * s : streets) {
			if (s->getStartEndPositions().first == end && s->getStartEndPositions().second == start)
				return false;
			else if (s->getDirection() == N || s->getDirection() == S)
				if (s->getStartEndPositions().first.x == start.x)
					if (isInIntervalY(start, s) ||
						isInIntervalY(end, s) ||
						isInIntervalY(s->getStartEndPositions().first, &temp) ||
						isInIntervalY(s->getStartEndPositions().second, &temp)) return true;
		} else
			for (Street * s : streets)
				if (s->getStartEndPositions().first == end && s->getStartEndPositions().second == start)
					return false;
				else if (s->getDirection() == E || s->getDirection() == W)
					if (s->getStartEndPositions().first.y == start.y) 
						if (isInIntervalX(start, s) ||
							isInIntervalX(end, s) ||
							isInIntervalX(s->getStartEndPositions().first, &temp) ||
							isInIntervalX(s->getStartEndPositions().second, &temp)) return true;
	return false;
}

/*
public List<List<String>> findPaths(Node client, bool onlyClients)
{
List<Node> path = new List<Node>();
List<Node> neighbors = new List<Node>();
List<Node> listOfWhiteNodes = new List<Node>(nodeList);
List<Node> listOfGrayNodes = new List<Node>();
List<Node> listOfBlackNodes = new List<Node>();
List<List<Node>> finder = new List<List<Node>>();
List<List<String>> found = new List<List<String>>();

if (client == null)
return null;

listOfWhiteNodes.Remove(client);
listOfGrayNodes.Add(client);
path.Add(client);
finder.Add(path);
while (listOfGrayNodes.Any())
{
List<Node> copyOflistOfGrayNodes = new List<Node>(listOfGrayNodes);
foreach (Node nodeInCurrentStep in copyOflistOfGrayNodes)
{
neighbors = findNeighborNodes(nodeInCurrentStep);
foreach(List<Node> pathiInFinder in finder)
{
if (pathiInFinder.Last().Equals(nodeInCurrentStep))
path = pathiInFinder;
}

foreach (Node nodeProcessing in neighbors)
{
if (listOfWhiteNodes.Where(i => i.Equals(nodeProcessing)).Any())
{
List<Node> newPath = new List<Node>(path);
listOfGrayNodes.Add(nodeProcessing);
listOfWhiteNodes.Remove(nodeProcessing);
newPath.Add(nodeProcessing);
finder.Add(newPath);
}
}
listOfBlackNodes.Add(nodeInCurrentStep);
listOfGrayNodes.Remove(nodeInCurrentStep);
}
}


if (onlyClients)
{
List<List<Node>> copyOfFinder = new List<List<Node>>(finder);
foreach (List<Node> nodeListPath in copyOfFinder)
{
if (!(nodeListPath.Last() is ClientNode))
finder.Remove(nodeListPath);
if (nodeListPath.Count() == 1)
finder.Remove(nodeListPath);
}
}

foreach (List<Node> nodeListPath in finder)
{
List<String> nodeName = new List<string>();
foreach (Node node in nodeListPath)
{
nodeName.Add(node.Name);
}
found.Add(nodeName);
}
return found;
}

internal void restartNode(string v)
{
Node n = nodeList.Where(s => s.Name.Equals(v)).FirstOrDefault();
if(n.ProcessHandle.HasExited)
{
//nodeList.Remove(n);
if (n is ClientNode)
n = new ClientNode((ClientNode)n);
else if (n is NetNode)
n = new NetNode((NetNode) n);

//List<string> conL = findElemAtPosition(n.Position.X, n.Position.Y);
mainWindow.updateConnections(connectionList);
sendOutInformation();
}
}

public List<List<Node>> findPathsLN(Node client, bool onlyClients)
{
List<Node> path = new List<Node>();
List<Node> neighbors = new List<Node>();
List<Node> listOfWhiteNodes = new List<Node>(nodeList);
List<Node> listOfGrayNodes = new List<Node>();
List<Node> listOfBlackNodes = new List<Node>();
List<List<Node>> finder = new List<List<Node>>();

if (client == null)
return null;

listOfWhiteNodes.Remove(client);
listOfGrayNodes.Add(client);
path.Add(client);
finder.Add(path);
while (listOfGrayNodes.Any())
{
List<Node> copyOflistOfGrayNodes = new List<Node>(listOfGrayNodes);
foreach (Node nodeInCurrentStep in copyOflistOfGrayNodes)
{
neighbors = findNeighborNodes(nodeInCurrentStep);
foreach (List<Node> pathiInFinder in finder)
{
if (pathiInFinder.Last().Equals(nodeInCurrentStep))
path = pathiInFinder;
}

foreach (Node nodeProcessing in neighbors)
{
if (listOfWhiteNodes.Where(i => i.Name.Equals(nodeProcessing.Name)).Any())
{
List<Node> newPath = new List<Node>(path);
listOfGrayNodes.Add(nodeProcessing);
listOfWhiteNodes.Remove(nodeProcessing);
newPath.Add(nodeProcessing);
finder.Add(newPath);
}
}
listOfBlackNodes.Add(nodeInCurrentStep);
listOfGrayNodes.Remove(nodeInCurrentStep);
}
}


if (onlyClients)
{
List<List<Node>> copyOfFinder = new List<List<Node>>(finder);
foreach (List<Node> nodeListPath in copyOfFinder)
{
if (!(nodeListPath.Last() is ClientNode))
finder.Remove(nodeListPath);
if (nodeListPath.Count() == 1)
finder.Remove(nodeListPath);
}
}

return finder;
}

private List<Node> findNeighbors(Node n)
{
List<Node> neighborNodes = new List<Node>();
List<NodeConnection> possibeNodesConn = connectionList.Where(i => i.From.Equals(n) || i.To.Equals(n)).ToList();
foreach (NodeConnection con in possibeNodesConn)
{
neighborNodes.Add(con.From.Equals(n) ? con.To : con.From);
}
return neighborNodes;
}

public void stopRunning()
{
run = false;
listener.Stop();
}

*/