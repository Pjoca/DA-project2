//
// Created by oem on 22/05/23.
//

#ifndef DA___2ND_PROJECT_VERTEXEDGE_H
#define DA___2ND_PROJECT_VERTEXEDGE_H


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include "MutablePriorityQueue.h"

using namespace std;

/**
 * @brief The Edge class is used to represent the edges of the graph.
 */

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @brief The Vertex class is used to represent the vertices of the graph.
 */

class Vertex {
public:

/**
 * @brief Constructor for the Vertex class with an ID.
 *
 * @param id The ID of the vertex.
 */

    Vertex(int id);

/**
 * @brief Constructor for the Vertex class with an ID, longitude, and latitude.
 *
 * @param id The ID of the vertex.
 * @param longitude The longitude coordinate of the vertex.
 * @param latitude The latitude coordinate of the vertex.
 */

    Vertex(int id, double longitude, double latitude);

/**
 * @brief Constructor for the Vertex class with an ID and name.
 *
 * @param id The ID of the vertex.
 * @param name The name of the vertex.
 */

    Vertex(int id, string name);

/**
 * @brief Overloaded less than operator for comparing vertices based on distance (dist).
 *
 * @param vertex The vertex to compare with.
 * @return True if this vertex's distance is less than the other vertex's distance, false otherwise.
 */

    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

/**
 * @brief Gets the ID of the vertex.
 *
 * @return The ID of the vertex.
 */

    int getId() const;

/**
 * @brief Gets the adjacent edges of the vertex.
 *
 * @return A vector of pointers to the adjacent edges.
 */

    std::vector<Edge *> getAdj() const;

/**
 * @brief Checks if the vertex is visited.
 *
 * @return True if the vertex is visited, false otherwise.
 */

    bool isVisited() const;

/**
 * @brief Gets the distance of the vertex.
 *
 * @return The distance of the vertex.
 */

    double getDist() const;

/**
 * @brief Gets the path to the vertex.
 *
 * @return A pointer to the path edge.
 */

    Edge *getPath() const;

/**
 * @brief Gets the incoming edges of the vertex.
 *
 * @return A vector of pointers to the incoming edges.
 */

    std::vector<Edge *> getIncoming() const;

/**
 * @brief Sets the ID of the vertex.
 *
 * @param id The ID of the vertex.
 */

    void setId(int info);

/**
 * @brief Sets the visited status of the vertex.
 *
 * @param visited The visited status of the vertex.
 */

    void setVisited(bool visited);

/**
 * @brief Sets the processing status of the vertex.
 *
 * @param processing The processing status of the vertex.
 */

    void setProcesssing(bool processing);

/**
 * @brief Sets the distance of the vertex.
 *
 * @param dist The distance of the vertex.
 */

    void setIndegree(unsigned int indegree);

/**
 * @brief Sets the distance of the vertex.
 *
 * @param dist The distance of the vertex.
 */

    void setDist(double dist);

/**
 * @brief Sets the path to the vertex.
 *
 * @param path A pointer to the path edge.
 */

    void setPath(Edge *path);

/**
 * @brief Adds an outgoing edge to the vertex with the given destination vertex and weight.
 *
 * @param d The destination vertex.
 * @param w The weight of the edge.
 * @return A pointer to the created edge.
 */

    Edge * addEdge(Vertex *dest, double w);

/**
 * @brief Removes an outgoing edge with the given destination ID from the vertex.
 *
 * @param destID The ID of the destination vertex.
 * @return True if the edge is successfully removed, false if the edge does not exist.
 */

    bool removeEdge(int destID);

    friend class MutablePriorityQueue<Vertex>;
protected:
    int id;                // vertex ID
    double longitude;
    double latitude;
    string name;
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0; // distance (used in algorithms)
    Edge *path = nullptr;

    vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

/**
 * @brief Deletes an edge and updates the incoming edges of the destination vertex.
 *
 * @param edge The edge to delete.
 */

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

/**
 * @brief The Edge class is used to represent the edges of the graph.
 */

class Edge {
public:

/**
 * @brief Constructor for the Edge class with an origin vertex, destination vertex, and weight.
 *
 * @param orig The origin vertex.
 * @param dest The destination vertex.
 * @param w The weight of the edge.
 */

    Edge(Vertex *orig, Vertex *dest, double w);

/**
 * @brief Gets the destination vertex of the edge.
 *
 * @return A pointer to the destination vertex.
 */

    Vertex * getDest() const;

/**
 * @brief Gets the weight of the edge.
 *
 * @return The weight of the edge.
 */

    double getWeight() const;

/**
 * @brief Checks if the edge is selected.
 *
 * @return True if the edge is selected, false otherwise.
 */

    bool isSelected() const;

/**
 * @brief Gets the origin vertex of the edge.
 *
 * @return A pointer to the origin vertex.
 */

    Vertex * getOrig() const;

/**
 * @brief Gets the reverse edge of the edge.
 *
 * @return A pointer to the reverse edge.
 */

    Edge *getReverse() const;

/**
 * @brief Gets the flow of the edge.
 *
 * @return The flow of the edge.
 */

    double getFlow() const;

/**
 * @brief Sets the selected status of the edge.
 *
 * @param selected The selected status of the edge.
 */

    void setSelected(bool selected);

/**
 * @brief Sets the reverse edge of the edge.
 *
 * @param reverse A pointer to the reverse edge.
 */

    void setReverse(Edge *reverse);

/**
 * @brief Sets the flow of the edge.
 *
 * @param flow The flow of the edge.
 */

    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig; // origin vertex
    Edge *reverse = nullptr; // reverse edge

    double flow; // for flow-related problems
};


#endif //DA___2ND_PROJECT_VERTEXEDGE_H
