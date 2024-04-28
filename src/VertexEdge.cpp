//
// Created by oem on 22/05/23.
//

#include "VertexEdge.h"

/**
 * @brief Constructor for the Vertex class with an ID.
 *
 * @param id The ID of the vertex.
 */

Vertex::Vertex(int id): id(id) {}

/**
 * @brief Constructor for the Vertex class with an ID, longitude, and latitude.
 *
 * @param id The ID of the vertex.
 * @param longitude The longitude coordinate of the vertex.
 * @param latitude The latitude coordinate of the vertex.
 */

Vertex::Vertex(int id, double longitude, double latitude) :
    id(id),
    longitude(longitude),
    latitude(latitude)
    {}

/**
 * @brief Constructor for the Vertex class with an ID and name.
 *
 * @param id The ID of the vertex.
 * @param name The name of the vertex.
 */

Vertex::Vertex(int id, string name): id(id), name(name) {}

/**
 * @brief Adds an outgoing edge to the vertex with the given destination vertex and weight.
 *
 * @param d The destination vertex.
 * @param w The weight of the edge.
 * @return A pointer to the created edge.
 */

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/**
 * @brief Removes an outgoing edge with the given destination ID from the vertex.
 *
 * @param destID The ID of the destination vertex.
 * @return True if the edge is successfully removed, false if the edge does not exist.
 */

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/**
 * @brief Overloaded less than operator for comparing vertices based on distance (dist).
 *
 * @param vertex The vertex to compare with.
 * @return True if this vertex's distance is less than the other vertex's distance, false otherwise.
 */

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

/**
 * @brief Gets the ID of the vertex.
 *
 * @return The ID of the vertex.
 */

int Vertex::getId() const {
    return this->id;
}

/**
 * @brief Gets the adjacent edges of the vertex.
 *
 * @return A vector of pointers to the adjacent edges.
 */

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

/**
 * @brief Checks if the vertex is visited.
 *
 * @return True if the vertex is visited, false otherwise.
 */

bool Vertex::isVisited() const {
    return this->visited;
}

/**
 * @brief Gets the distance of the vertex.
 *
 * @return The distance of the vertex.
 */

double Vertex::getDist() const {
    return this->dist;
}

/**
 * @brief Gets the path to the vertex.
 *
 * @return A pointer to the path edge.
 */

Edge *Vertex::getPath() const {
    return this->path;
}

/**
 * @brief Gets the incoming edges of the vertex.
 *
 * @return A vector of pointers to the incoming edges.
 */

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

/**
 * @brief Sets the ID of the vertex.
 *
 * @param id The ID of the vertex.
 */

void Vertex::setId(int id) {
    this->id = id;
}

/**
 * @brief Sets the visited status of the vertex.
 *
 * @param visited The visited status of the vertex.
 */

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

/**
 * @brief Sets the processing status of the vertex.
 *
 * @param processing The processing status of the vertex.
 */

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

/**
 * @brief Sets the distance of the vertex.
 *
 * @param dist The distance of the vertex.
 */

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

/**
 * @brief Sets the distance of the vertex.
 *
 * @param dist The distance of the vertex.
 */

void Vertex::setDist(double dist) {
    this->dist = dist;
}

/**
 * @brief Sets the path to the vertex.
 *
 * @param path A pointer to the path edge.
 */

void Vertex::setPath(Edge *path) {
    this->path = path;
}

/**
 * @brief Deletes an edge and updates the incoming edges of the destination vertex.
 *
 * @param edge The edge to delete.
 */

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

/**
 * @brief Constructor for the Edge class with an origin vertex, destination vertex, and weight.
 *
 * @param orig The origin vertex.
 * @param dest The destination vertex.
 * @param w The weight of the edge.
 */

Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}

/**
 * @brief Gets the destination vertex of the edge.
 *
 * @return A pointer to the destination vertex.
 */

Vertex * Edge::getDest() const {
    return this->dest;
}

/**
 * @brief Gets the weight of the edge.
 *
 * @return The weight of the edge.
 */

double Edge::getWeight() const {
    return this->weight;
}

/**
 * @brief Gets the origin vertex of the edge.
 *
 * @return A pointer to the origin vertex.
 */

Vertex * Edge::getOrig() const {
    return this->orig;
}

/**
 * @brief Gets the reverse edge of the edge.
 *
 * @return A pointer to the reverse edge.
 */

Edge *Edge::getReverse() const {
    return this->reverse;
}

/**
 * @brief Checks if the edge is selected.
 *
 * @return True if the edge is selected, false otherwise.
 */

bool Edge::isSelected() const {
    return this->selected;
}

/**
 * @brief Gets the flow of the edge.
 *
 * @return The flow of the edge.
 */

double Edge::getFlow() const {
    return flow;
}

/**
 * @brief Sets the selected status of the edge.
 *
 * @param selected The selected status of the edge.
 */

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

/**
 * @brief Sets the reverse edge of the edge.
 *
 * @param reverse A pointer to the reverse edge.
 */

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

/**
 * @brief Sets the flow of the edge.
 *
 * @param flow The flow of the edge.
 */

void Edge::setFlow(double flow) {
    this->flow = flow;
}