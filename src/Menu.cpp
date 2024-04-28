//
// Created by oem on 16/05/23.
//

#include <algorithm>
#include <utility>
#include "Menu.h"

/**
 * Default constructor for the Menu class.
 *
 * @brief Default constructor for the Menu class.
 *
 * @note Initializes the `entry` member with the default ".././data" path.
 */

Menu::Menu() {
    entry.assign(".././data");
}

/**
 * Sets the directory entry for the Menu class.
 *
 * @brief Sets the directory entry.
 * @param val The directory entry.
 */

void Menu::setEntry(fs::directory_entry val) {
    this->entry = std::move(val);
}

/**
 * Sets the edges path for the Menu class.
 *
 * @brief Sets the edges path.
 * @param val The edges path.
 */

void Menu::setEdges(fs::path val) {
    this->edges = std::move(val);
}

/**
 * Sets the nodes path for the Menu class.
 *
 * @brief Sets the nodes path.
 * @param val The nodes path.
 */

void Menu::setNodes(fs::path val) {
    this->nodes = std::move(val);
}

/**
 * Displays the Ocean Shipping and Urban Deliveries Management Program menu.
 *
 * @brief Displays the menu.
 */

void Menu::Display() {
    cout << "\n\t\t\tOcean Shipping and Urban Deliveries ManagementProgram " << endl;
    cout << "\n";
    Menu::selectData(entry);
}

/**
 * Selects the data based on the given directory entry.
 *
 * @brief Selects the data.
 * @param selected The directory entry.
 */

void Menu::selectData(const fs::directory_entry& selected) {
    std::vector<fs::directory_entry> entries;
    int i = 1;
    for (auto &entry: fs::directory_iterator(selected.path())) {
        if (entry.path().filename() != ".DS_Store") {  // Skip ".DS_Store" file
            entries.push_back(entry);
        }
    }
    std::sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b) {
        return a.path().filename().string() < b.path().filename().string();
    });
    for (auto &entry : entries){
        cout << "\t" << i << ")" << entry.path().filename() << endl;
        i++;
    }
    cout << "\n\t0) Exit " << endl;
    int a;
    cin >> a;
    if (a == 0) {
        exit(0);
    }
    else if (a > i || a < 0) {
        cout << "\n\tWrong Input!" << endl;
        Menu::Display();
    }
    else if(entries[a-1].is_directory()){
        Menu::setEntry(entries[a-1]);
        if(entries[a-1].path().filename() == "graph1" || entries[a-1].path().filename() == "graph2" || entries[a-1].path().filename() == "graph3"){
            for (auto &entry: fs::directory_iterator(selected.path())) {
                if (entry.path().filename() == "edges.csv") {  // Skip ".DS_Store" file
                    Menu::setEdges(entry.path());
                }
                else if(entry.path().filename() == "nodes.csv"){
                    Menu::setNodes(entry.path());
                }
            }
            Menu::selectFunctions();
        }
        else
            Menu::Display();
    }
    else if(!entries[a-1].is_directory()){
        Menu::setEntry(entries[a-1]);
        Menu::setEdges(entries[a-1].path());
        cout << entries[a-1].path().filename() << endl;
        Menu::selectFunctions();
    }
    else
        cout << "Unknown Error" << endl;
}

/**
 * Displays the options for selecting different algorithms and performs the selected algorithm based on user input.
 *
 * @brief Displays options and performs selected algorithm.
 */

void Menu::selectFunctions() {
    cout << "\n\t\t\tOcean Shipping and Urban Deliveries ManagementProgram " << endl;
    cout << "\n";
    cout << "\t1) Backtracking Algorithm" << endl;
    cout << "\t2) Triangular Approximation Heuristic" << endl;
    cout << "\t3) Genetic Algorithm" << endl;

    cout << "\n\t0) Exit " << endl;
    bool verify=!nodes.empty();
    Services service;
    FileReader reader(verify);
    int a;
    cin >> a;
    if (a == 0) {
        exit(0);
    }
    else if(a == 1){
        // Perform Backtracking Algorithm
        Graph graph;
        if(reader.verify()){
            reader.readNodes(graph, nodes);
            reader.readEdges2(graph, edges);
        }
        else{reader.readEdges1(graph, edges );}
        graph.setDistMatrix();
        int path[graph.getVertexSet().size()];
        auto startTime = chrono::high_resolution_clock::now();
        double res = service.BT(graph, path);
        if(res == -1){
            cout << "\nThis service is no feasible for the given data" << endl;
            exit(0);
        }
        auto endTime = chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        graph.setOptPathBT(path);
        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
        cout << "\tMinimum distance : " << res << endl;
        cout << "\tOptimal path : [";
        for(int i=0; i<graph.getVertexSet().size(); i++){
            cout << graph.getOptPathBT()[i] << " -> ";
        }
        cout <<"0]" << endl;

        cout << "\n\t\tExecution time: " << duration.count() << " seconds" << endl;

        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
    }

   else if( a == 2) {
        // Perform Triangular Approximation Heuristic
        Graph graph;
        if(reader.verify()){
            reader.readNodes(graph, nodes);
            reader.readEdges2(graph, edges);
        }
        else{reader.readEdges1(graph, edges );}
        graph.setDistMatrix();
        int path[graph.getNumVertex()];
        auto startTime = chrono::high_resolution_clock::now();
        double res = service.TAH(graph, path);
        graph.setOptPathBT(path);

        auto endTime = chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;

        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
        cout << "\tOptimal path (MST in preorder) : [";
        for(int i=0; i<graph.getVertexSet().size(); i++){
            cout << graph.getOptPathBT()[i] << " -> ";
        }
        cout <<"0]" << endl;
        cout << "\tMinimum distance (at most twice the cost of the best solution) : " << res << endl;
        cout << "\n\t\tExecution time: " << duration.count() << " seconds" << endl;

        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
    }

   else if(a==3) {
        // Perform Genetic Algorithm
        Graph graph;
        if(reader.verify()){
            reader.readNodes(graph, nodes);
            reader.readEdges2(graph, edges);
        }
        else{reader.readEdges1(graph, edges );}
        graph.setDistMatrix();
        int path[graph.getNumVertex()];
        auto startTime = chrono::high_resolution_clock::now();
        double res = service.GA(graph, path);
        graph.setOptPathBT(path);

        auto endTime = chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;

        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
        cout << "\tPath : [";
        for(int i=0; i<graph.getVertexSet().size(); i++){
            cout << graph.getOptPathBT()[i] << " -> ";
        }
        cout <<"0]" << endl;
        cout << "\tMinimum distance : " << res << endl;
        cout << "\n\t\tExecution time: " << duration.count() << " seconds" << endl;

        cout << "\n\t\t\t===================" << endl;
        cout << "\n";
    }
}
