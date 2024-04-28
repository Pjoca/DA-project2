//
// Created by oem on 23/05/23.
//

#ifndef DA___2ND_PROJECT_SERVICES_H
#define DA___2ND_PROJECT_SERVICES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <chrono>
#include <random>
#include "Graph.h"

using namespace std;

/**
 * @brief The Services class provides various algorithms for solving optimization problems on graphs.
 */

class Services {
private:
    int size; /**< The size of the graph */
    double **distMatrix = nullptr; /**< The distance matrix of the graph */
    chrono::high_resolution_clock::time_point start;  /**< The start time for algorithm execution */

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
 * @complexity The time complexity in the worst case is O(2^n).
 */

    void BTRec(Graph& graph, int curIndex, double curDist, int curPath[], double& minDist,int path[]);

/**
 * Sets the distance matrix in the Services class.
 *
 * @brief Sets the distance matrix.
 * @param res The distance matrix.
 * @param n The size of the distance matrix.
 */

    void setDistMatrix(double **res, int n);

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

    void preorderTraversal(Vertex* vertex, std::unordered_set<Vertex*>& visited, std::unordered_map<Vertex*, Edge*>& mst, int path[], int& index, double& minDist);

/**
 * Generates a nearest neighbor solution to the Traveling Salesman Problem in a given graph.
 *
 * @brief Generates a nearest neighbor solution to the Traveling Salesman Problem.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the generated path.
 * @param minDist Reference to the minimum distance found.
 * @complexity This function has a time complexity of O(|V|^2), where |V| is the number of vertices in the graph.
 */

    void NN(const Graph& graph, int path[], double& minDist);

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

    bool geneticMutation(unordered_map<double, int*> &candidates, int const candidate[], double upperBound, double &minDist);

/**
 * Calculates the cost of a given path in the graph.
 *
 * @brief Calculates the cost of a given path.
 * @param path The path to calculate the cost for.
 * @return The cost of the path.
 * @complexity This function has a time complexity of O(|V|), where |V| is the number of vertices in the path.
 */

    double pathCost(const int path []);

public:

/**
 * Destructor for the Services class.
 *
 * @brief Destructor for the Services class.
 * @note This function deallocates the memory occupied by the distance matrix.
 */

    ~Services();

/**
 * Default constructor for the Services class.
 *
 * @brief Default constructor for the Services class.
 */

    Services();

 /**
 * Calculates the shortest path using the Backtracking algorithm in a given graph.
 *
 * @brief Calculates the shortest path using the Backtracking algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the shortest path found.
 * @return The minimum distance of the shortest path.
 * @complexity This function has an exponential time complexity of O(2^n).
 */

    double BT(Graph& graph, int path[]);

/**
 * Calculates the minimum spanning tree using the Prim's algorithm in a given graph.
 *
 * @brief Calculates the minimum spanning tree using Prim's algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the traversal path of the minimum spanning tree.
 * @return The total weight of the minimum spanning tree.
 * @complexity This function has a time complexity of O(|V|^2), where |V| is the number of vertices in the graph.
 */

    double TAH(Graph &graph, int path[]);

/**
 * Solves the Traveling Salesman Problem using a Genetic Algorithm in a given graph.
 *
 * @brief Solves the Traveling Salesman Problem using a Genetic Algorithm.
 * @param graph The graph object representing the vertices and edges.
 * @param path An array to store the generated path.
 * @return The minimum distance of the TSP solution.
 */

    double GA(Graph &graph, int path[]);

};



#endif //DA___2ND_PROJECT_SERVICES_H
