//
// Created by oem on 22/05/23.
//

#ifndef DA___2ND_PROJECT_GRAPH_H
#define DA___2ND_PROJECT_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include "MutablePriorityQueue.h"

#include "VertexEdge.h"

using namespace std;

/**
 * @brief The Graph class is used to represent the graphs.
 */

class Graph {
public:

/**
 * @brief Destructor for the Graph class.
 *
 * Deletes the pathMatrix and distMatrix arrays.
 */

    ~Graph();

/**
 * @brief Finds a vertex with a given ID.
 *
 * @param id The ID of the vertex to find.
 * @return Pointer to the found vertex, or nullptr if not found.
 */

    Vertex *findVertex(const int &id) const;

/**
 * @brief Adds a vertex with a given ID to the graph.
 *
 * @param id The ID of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

    bool addVertex(const int &id);

/**
 * @brief Adds a vertex with a given ID and name to the graph.
 *
 * @param id The ID of the vertex to add.
 * @param name The name of the vertex to add.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

    bool addVertex(const int &id, const string &name);

/**
 * @brief Adds a vertex with a given ID and coordinates to the graph.
 *
 * @param id The ID of the vertex to add.
 * @param longitude The longitude coordinate of the vertex.
 * @param latitude The latitude coordinate of the vertex.
 * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
 */

    bool addVertex(const int &id, const double &longitude, const double &latitude);

/**
 * @brief Adds a bidirectional edge between two vertices in the graph with the given weight.
 *
 * @param sourc The ID of the source vertex.
 * @param dest The ID of the destination vertex.
 * @param w The weight of the edge.
 * @return True if the edge is added successfully, false otherwise.
 */

    bool addBidirectionalEdge(const int &sourc, const int &dest, double w) const;

/**
 * @brief Returns the number of vertices in the graph.
 *
 * @return The number of vertices in the graph.
 */

    int getNumVertex() const;

/**
 * @brief Returns a copy of the vertex set.
 *
 * @return A copy of the vertex set as an unordered map, where the key is the vertex ID and the value is a pointer to the vertex.
 */

    std::unordered_map<int, Vertex *> getVertexSet() const;

/**
 * @brief Returns the distance matrix of the graph.
 *
 * @return The distance matrix of the graph.
 */

    double ** getDistMatrix() const;

/**
 * @brief Sets the optimal path for the Branch-and-Bound algorithm.
 *
 * @param path The optimal path.
 */


    void setOptPathBT(int *path);

/**
 * @brief Get the optimal path for the Branch-and-Bound algorithm.
 *
 * @return The optimal path.
 */

    int * getOptPathBT();

/**
 * @brief Sets the distance matrix of the graph.
 *
 * The distance matrix is a 2D array representing the distances between vertices in the graph.
 * Each element distMatrix[i][j] represents the distance between vertex i and vertex j.
 */

    void setDistMatrix();

protected:
    unordered_map<int, Vertex*> vertexSet;    // vertex set

    //std::vector<std::vector<double>> distMatrix;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    int *optPathBT = nullptr;

    double ** distMatrix = nullptr;

    /*
     * Finds the index of the vertex with a given content.
     */
    //int findVertexIdx(const int &id) const;
};

/**
 * @brief Deletes a 2D matrix of integers.
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */

void deleteMatrix(int **m, int n);

/**
 * @brief Deletes a 2D matrix of doubles.
 *
 * @param m The matrix to delete.
 * @param n The size of the matrix.
 */

void deleteMatrix(double **m, int n);


#endif //DA___2ND_PROJECT_GRAPH_H
