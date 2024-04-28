//
// Created by oem on 19/05/23.
//

#include "FileReader.h"


/**
 * Reads edge data from a CSV file and adds edges to the graph (small and medium graphs).
 *
 * @param graph The graph object to add the edges to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and edges were added, false otherwise.
 */

bool FileReader::readEdges1(Graph& graph, const fs::path& file_name ) {
    ifstream file;
    file.open(file_name);

    if (!file) {
        cout << "File not created!" << endl;
        return false;
    }else{
        cout << "file accepted" << endl;

        string file_line;

        getline(file, file_line);

        while (getline(file, file_line)){
            if (file_line.empty()){
                continue;
            }
            string A;
            string B;
            string dis;
            string nameA;
            string nameB;
            char separation_token = ',';

            int flag = 0;

            for(auto i : file_line){
                if(i == separation_token){
                    flag ++;
                    continue;
                }

                switch (flag) {
                    case 0:
                        A += i;
                        break;
                    case 1:
                        B += i;
                        break;
                    case 2:
                        dis +=i;
                        break;
                    case 3:
                        nameA += i;
                        break;
                    case 4:
                        nameB += i;
                        break;
                    default:
                        break;
                }
            }


            if(flag > 2){
                graph.addVertex(stoi(A), nameA);
                graph.addVertex(stoi(B), nameB);
            }
            else{
                graph.addVertex(stoi(A));
                graph.addVertex(stoi(B));
            }


            graph.addBidirectionalEdge(stoi(A),stoi(B),std::stod(dis));

        }
        file.close();
        return true;
    }
}

/**
 * Reads node data from a CSV file and adds vertices to the graph.
 *
 * @param graph The graph object to add the vertices to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and vertices were added, false otherwise.
 */

bool FileReader::readNodes(Graph& graph, const fs::path& file_name) {
    ifstream file;
    file.open(file_name);

    if (!file) {
        cout << "File not created!" << endl;
        return false;
    } else {
        cout << "file accepted" << endl;

        string file_line;

        getline(file, file_line);

        while (getline(file, file_line)) {
            if (file_line.empty()){
                continue;
            }
            string id;
            string longitude;
            string latitude;
            char separation_token = ',';

            int flag = 0;

            for (auto i: file_line) {
                if (i == separation_token) {

                    flag++;
                    continue;
                }
                switch (flag) {
                    case 0:
                        id += i;
                        break;
                    case 1:
                        longitude += i;
                        break;
                    case 2:
                        latitude += i;
                        break;
                    default:
                        break;
                }
            }
            cout << "Nodes : " << stoi(id) << " - " << stod(longitude) << " - " << stod(latitude) << endl;

            graph.addVertex(stoi(id), stod(longitude), stod(latitude));
        }
        file.close();
        return true;
    }
}

/**
 * Reads edge data from a CSV file and adds edges to the graph (large graphs).
 *
 * @param graph The graph object to add the edges to.
 * @param file_name The path to the CSV file.
 * @return True if the file was successfully read and edges were added, false otherwise.
 */

bool FileReader::readEdges2(Graph& graph, const fs::path& file_name){
    ifstream file;
    file.open(file_name);

    if (!file) {
        cout << "File not created!" << endl;
        return false;
    }else{
        //cout << "file accepted" << endl;

        string file_line;

        getline(file, file_line);


        while (getline(file, file_line)){
            if (file_line.empty()){
                continue;
            }
            string A;
            string B;
            string dis;
            char separation_token = ',';

            int flag = 0;

            for(auto i : file_line){

                if(i == separation_token){

                    flag ++;
                    continue;
                }

                switch (flag) {
                    case 0:
                        A += i;
                        break;
                    case 1:
                        B += i;
                        break;
                    case 2:
                        dis +=i;
                        break;
                    default:
                        break;
                }
            }
            cout << "Edges : " << stoi(A) << " - " << stoi(B) << " - " << stod(dis) << endl;
            graph.addBidirectionalEdge(stoi(A),stoi(B),stod(dis));
        }
        file.close();
        return true;
    }
}

/**
 * Constructs a FileReader object.
 *
 * @param verify A boolean value indicating whether nodes data is available.
 */

FileReader::FileReader(bool verify) : nodes(verify) {}

/**
 * Checks if the FileReader has nodes data available.
 *
 * @return True if nodes data is available, false otherwise.
 */

bool FileReader::verify() const {
    return this->nodes;
}
