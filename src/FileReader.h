//
// Created by oem on 19/05/23.
//

#ifndef DA___2ND_PROJECT_FILEREADER_H
#define DA___2ND_PROJECT_FILEREADER_H

#include <fstream>
#include <filesystem>
#include "Graph.h"

namespace fs = std::filesystem;
using namespace std;

/**
 * @brief The FileReader class handles reading data from files.
 */

class FileReader {
private :
    bool nodes; /**< Indicates if the nodes file is present */
public :

/**
 * Constructs a FileReader object.
 *
 * @param verify A boolean value indicating whether nodes data is available.
 */

    FileReader(bool verify);

/**
 * Reads edge data from a CSV file and adds edges to the graph (small and medium graphs).
 *
 * @param graph The graph object to add the edges to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and edges were added, false otherwise.
 */

    bool readEdges1(Graph& graph, const fs::path& file_name );

/**
 * Reads edge data from a CSV file and adds edges to the graph (large graphs).
 *
 * @param graph The graph object to add the edges to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and edges were added, false otherwise.
 */

    bool readEdges2(Graph& graph, const fs::path& file_name);

/**
 * Reads node data from a CSV file and adds vertices to the graph.
 *
 * @param graph The graph object to add the vertices to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and vertices were added, false otherwise.
 */

    bool readNodes(Graph& graph, const fs::path& file_name);

/**
 * Checks if the FileReader has nodes data available.
 *
 * @return True if nodes data is available, false otherwise.
 */

    bool verify() const;
};


#endif //DA___2ND_PROJECT_FILEREADER_H
