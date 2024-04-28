//
// Created by oem on 23/05/23.
//

#include "Services.h"
int c=0;

/**
 * Calculates the shortest path using the Backtracking algorithm in a given graph.
 *
 * @brief Calculates the shortest path using the Backtracking algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the shortest path found.
 * @return The minimum distance of the shortest path.
 * @note This function has an exponential time complexity of O(2^n).
 */

double Services::BT(Graph &graph, int path[]) {
    int curPath[10000];
    double minDist  = numeric_limits<double>::max();

    curPath[0] = 0;
    start = chrono::high_resolution_clock::now();
    BTRec(graph, 1, 0, curPath, minDist, path);

    return minDist;
}

/**
 * Recursive function to find the shortest path using Backtracking algorithm.
 *
 * @brief Recursive function to find the shortest path.
 * @param graph The graph object representing the vertices and edges.
 * @param curIndex The current index in the path being constructed.
 * @param curDist The current distance of the path.
 * @param curPath The current path being constructed.
 * @param minDist Reference to the minimum distance found so far.
 * @param path An array to store the shortest path found.
 * @note The time complexity in the worst case is O(2^n).
 */

void Services::BTRec(Graph &graph, int curIndex, double curDist, int curPath[], double &minDist, int path[]) {
    const unordered_map<int, Vertex*> nodes= graph.getVertexSet();
    double **distMatrix = graph.getDistMatrix();
    auto current_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start).count();
    if (elapsed_time > 30) {
        minDist = -1;
        return;
    }
    if (curIndex == nodes.size() && distMatrix[curPath[curIndex - 1]][curPath[0]] != 0) {
            curDist += distMatrix[curPath[curIndex - 1]][0];
            if (curDist < minDist) {
                minDist = curDist;
                for (unsigned int i = 0; i < nodes.size(); i++) {
                    path[i] = curPath[i];
                }
            }
        return;
    }

    for (int i = 1; i < nodes.size(); i++) {
        if (distMatrix[curPath[curIndex-1]][i] > 0 && curDist+distMatrix[curPath[curIndex-1]][i]<minDist && !nodes.at(i)->isVisited()){
            nodes.at(i)->setVisited(true);
            curPath[curIndex] = i;
            BTRec(graph, curIndex + 1, curDist + distMatrix[curPath[curIndex-1]][i] , curPath, minDist, path);
            nodes.at(i)->setVisited(false);
       }
    }
}

/**
 * Calculates the minimum spanning tree using the Prim's algorithm in a given graph.
 *
 * @brief Calculates the minimum spanning tree using Prim's algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the traversal path of the minimum spanning tree.
 * @return The total weight of the minimum spanning tree.
 * @note This function has a time complexity of O(|V|^2), where |V| is the number of vertices in the graph.
 */


double Services::TAH(Graph &graph, int path[]){
    MutablePriorityQueue<Vertex> aux;
    std::unordered_map<Vertex*, Edge*> mst;

    Vertex* root = graph.findVertex(0);
    root->setDist(0);
    aux.insert(root);


    for(auto v : graph.getVertexSet()){
        if(v.first != 0 && v.second->getId() != 0){
            v.second->setDist(numeric_limits<double>::max());
            aux.insert(v.second);
        }
    }

    unordered_set<Vertex*> visited;

    while(!aux.empty()){
        auto cur = aux.extractMin();
        cur->setVisited(true);

        for(auto edge : cur->getAdj()){
            auto dest = edge->getDest();
            if(!dest->isVisited() && edge->getWeight() < dest->getDist()){
                mst[dest] = edge;
                dest->setDist(edge->getWeight());
                aux.decreaseKey(dest);
            }
        }
    }
    int index = 0;
    double minDist = 0.0;
    preorderTraversal(root, visited, mst, path, index, minDist);
    return minDist;
}

/**
 * Performs a preorder traversal of the minimum spanning tree to generate a traversal path.
 *
 * @brief Performs a preorder traversal of the minimum spanning tree.
 * @param vertex The current vertex being visited in the traversal.
 * @param visited A set of visited vertices.
 * @param mst A map representing the minimum spanning tree.
 * @param path An array to store the traversal path.
 * @param index The current index in the traversal path.
 * @param minDist Reference to the total weight of the minimum spanning tree.
 */

void Services::preorderTraversal(Vertex* vertex, std::unordered_set<Vertex*>& visited, std::unordered_map<Vertex*, Edge*>& mst, int path[], int& index, double& minDist) {
    visited.insert(vertex);
    path[index++] = vertex->getId();

    for (const auto e : vertex->getAdj()) {
        auto search = mst.find(e->getDest());
        if (search != mst.end() && search->second == e) {
            cout << "Edge: " << e->getOrig()->getId() << " - " << e->getDest()->getId() << endl;
            minDist += e->getWeight();
            preorderTraversal(e->getDest(), visited, mst, path, index, minDist);
        }
    }

    // Calculate distance from the last vertex back to the root
    if (vertex->getId() != 0) {
        auto search = mst.find(vertex);
        if (search != mst.end()) {
            auto edge = search->second;
            cout << "Edge: " << edge->getOrig()->getId() << " - " << edge->getDest()->getId() << endl;
            minDist += edge->getWeight();
        }
    }
}

/**
 * Generates a nearest neighbor solution to the Traveling Salesman Problem in a given graph.
 *
 * @brief Generates a nearest neighbor solution to the Traveling Salesman Problem.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the generated path.
 * @param minDist Reference to the minimum distance found.
 * @note This function has a time complexity of O(|V|^2), where |V| is the number of vertices in the graph.
 */

void Services::NN(const Graph& graph, int *path, double &minDist) {
    int index = 0;
    unordered_map<int, Vertex*> vertexSet = graph.getVertexSet();
    unordered_set<int> visited;
    visited.insert(0);
    path[0] = 0;
    int cur = 0;
    while(visited.size() < vertexSet.size()){
        vertexSet.at(cur)->setDist(numeric_limits<double>::max());
        int next = -1;

        for(const auto temp : vertexSet.at(cur)->getAdj()){
            if(visited.find(temp->getDest()->getId()) == visited.end()){
                double dist = temp->getWeight();
                if(vertexSet.at(cur)->getDist() > dist){
                    vertexSet.at(cur)->setDist(dist);
                    next = temp->getDest()->getId();
                }
            }
        }
        if(next == -1){
            break;}
        minDist += vertexSet.at(cur)->getDist();
        visited.insert(next);
        index++;
        path[index] = next;
        cur = next;
    }
    for(auto e : vertexSet.at(cur)->getAdj()){
        if(e->getDest()->getId() == 0){
            minDist += e->getWeight();
            break;
        }
    }
}

/**
 * Performs a genetic mutation operation on a candidate solution.
 *
 * @brief Performs a genetic mutation operation.
 * @param candidates A map of candidate solutions.
 * @param candidate The candidate solution to mutate.
 * @param upperBound The upper bound on the distance.
 * @param minDist Reference to the minimum distance found.
 * @return True if the mutation is successful and the candidate is added to the candidates map, False otherwise.
 */

bool Services::geneticMutation(unordered_map<double, int*> &candidates, int const *candidate, double upperBound, double &minDist) {
    int path[size];
    copy(candidate, candidate+size, path);

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(1, size-1);

    int pos1 = dist(rng);
    int pos2 = dist(rng);
    while (pos2 == pos1) {
        pos2 = dist(rng);
    }

    swap(path[pos1], path[pos2]);

    double cost = pathCost(path);
    if(cost < upperBound){
        candidates.insert({cost, path});
        if(cost < minDist){
            minDist = cost;
        }
        return true;
    }
    return false;
}

/**
 * Solves the Traveling Salesman Problem using a Genetic Algorithm in a given graph.
 *
 * @brief Solves the Traveling Salesman Problem using a Genetic Algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the generated path.
 * @return The minimum distance of the TSP solution.
 * @note This function has a time complexity of O(|V|^2), where |V| is the number of vertices in the graph.
 */


double Services::GA(Graph &graph, int *path) {
    unordered_map<double, int*> candidates;
    setDistMatrix(graph.getDistMatrix(), graph.getNumVertex());
    double minDist = 0.0;
    double startDist = minDist;
    double upperBound = 0.0;
    Services::NN(graph, path, minDist);
    upperBound = minDist * 1.5;
    candidates.insert({minDist, path});
    while(candidates.size() < graph.getNumVertex()){
        geneticMutation(candidates, path, upperBound, minDist);
    }
    if(minDist != startDist){
        path = candidates.at(minDist);
    }
    return minDist;
}

/**
 * Calculates the cost of a given path in the graph.
 *
 * @brief Calculates the cost of a given path.
 * @param path The path to calculate the cost for.
 * @return The cost of the path.
 * @note This function has a time complexity of O(|V|), where |V| is the number of vertices in the path.
 */

double Services::pathCost(const int *path) {
    double dist = 0.0;
    for(int i = size-1; i > 0; i--){
        dist += distMatrix[path[i]][path[i-1]];
    }
    return dist+distMatrix[path[size-1]][0];
}

/**
 * Sets the distance matrix in the Services class.
 *
 * @brief Sets the distance matrix.
 * @param res The distance matrix.
 * @param n The size of the distance matrix.
 */

void Services::setDistMatrix(double **res, int n){
    this->size = n;
    distMatrix = new double * [n];
    for(int i=0; i<n; i++){
        distMatrix[i] = new double[n];
        for(int j = 0; j < n; j++){
            distMatrix[i][j] = res[i][j];
        }
    }
}

/**
 * Destructor for the Services class.
 *
 * @brief Destructor for the Services class.
 * @note This function deallocates the memory occupied by the distance matrix.
 */

Services::~Services() {
    deleteMatrix(distMatrix, size);
}

/**
 * Default constructor for the Services class.
 *
 * @brief Default constructor for the Services class.
 */

Services::Services() {}


