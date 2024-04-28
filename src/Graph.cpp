//
// Created by oem on 22/05/23.
//

#include "Graph.h"

/**
 * @brief Returns the number of vertices in the graph.
 *
 * @return The number of vertices in the graph.
 */

int Graph::getNumVertex() const {
    return vertexSet.size();
}

/**
 * @brief Returns a copy of the vertex set.
 *
 * @return A copy of the vertex set as an unordered map, where the key is the vertex ID and the value is a pointer to the vertex.
 */

std::unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/**
 * @brief Finds a vertex with a given ID.
 *
 * @param id The ID of the vertex to find.
 * @return Pointer to the found vertex, or nullptr if not found.
 */

Vertex * Graph::findVertex(const int &id) const {
    if(auto search = vertexSet.find(id); search != vertexSet.end()){
        return search->second;
    }
    return nullptr;
}

/**
 * @brief Adds a vertex with a given ID to the graph.
 *
 * @param id The ID of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id, new Vertex(id)});
    return true;
}

/**
 * @brief Adds a vertex with a given ID and name to the graph.
 *
 * @param id The ID of the vertex to add.
 * @param name The name of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

bool Graph::addVertex(const int &id, const string &name) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id, new Vertex(id, name)});
    return true;
}

/**
 * @brief Adds a vertex with a given ID and coordinates to the graph.
 *
 * @param id The ID of the vertex to add.
 * @param longitude The longitude coordinate of the vertex.
 * @param latitude The latitude coordinate of the vertex.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

bool Graph::addVertex(const int &id, const double &longitude, const double &latitude) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id, new Vertex(id, longitude, latitude)});
    return true;
}

/**
 * @brief Adds a bidirectional edge between two vertices in the graph with the given weight.
 *
 * @param sourc The ID of the source vertex.
 * @param dest The ID of the destination vertex.
 * @param w The weight of the edge.
 * @return True if the edge is added successfully, false otherwise.
 */

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);

   /*- if(sourc >= distMatrix.size() || dest >= distMatrix.size()){
        int maxSize = std::max(sourc, dest) + 1;
        distMatrix.resize(maxSize);
        for (int i = 0; i < maxSize; i++) {
            distMatrix[i].resize(maxSize);
        }
    }

    distMatrix[sourc][dest] = w;
    distMatrix[dest][sourc] = w;-*/
    return true;
}

/**
 * @brief Returns the distance matrix of the graph.
 *
 * @return The distance matrix of the graph.
 */

double ** Graph::getDistMatrix() const {
    return this->distMatrix;
}

/**
 * @brief Sets the optimal path for the Branch-and-Bound algorithm.
 *
 * @param path The optimal path.
 */

void Graph::setOptPathBT(int *path) {
    if(optPathBT == nullptr){
        this->optPathBT = path;
    }
    else
        for(int i=0; i<vertexSet.size(); i++){
            this->optPathBT[i]=path[i];
        }
}

/**
 * @brief Sets the distance matrix of the graph.
 *
 * The distance matrix is a 2D array representing the distances between vertices in the graph.
 * Each element distMatrix[i][j] represents the distance between vertex i and vertex j.
 */

void Graph::setDistMatrix() {
    distMatrix = new double * [vertexSet.size()];
    for(int i=0; i<vertexSet.size(); i++){
        distMatrix[i] = new double[vertexSet.size()];
        for(int j = 0; j < vertexSet.size(); j++){
            distMatrix[i][j] = 0.0;
        }
    }
    for(int i = 0; i < vertexSet.size(); i++){
        for(auto t : vertexSet.at(i)->getAdj()){
            int dest = t->getDest()->getId();
            int orig = t->getOrig()->getId();

            if(distMatrix[orig][dest] != 0){continue;}
            distMatrix[orig][dest] = t->getWeight();
            distMatrix[dest][orig] = t->getWeight();
        }

    }
}

/**
 * @brief Get the optimal path for the Branch-and-Bound algorithm.
 *
 * @return The optimal path.
 */

int * Graph::getOptPathBT() {
    return this->optPathBT;
}

/**
 * @brief Deletes a 2D matrix of integers.
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

/**
 * @brief Deletes a 2D matrix of doubles.
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

/**
 * @brief Destructor for the Graph class.
 *
 * Deletes the pathMatrix and distMatrix arrays.
 */

Graph::~Graph() {
    deleteMatrix(pathMatrix, vertexSet.size());
    deleteMatrix(distMatrix, vertexSet.size());
}
