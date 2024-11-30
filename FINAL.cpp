#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Edge {
public:
    int weight;
    char start, end;
    bool isBlocked;
    bool underConstruction;
    Edge* next;

    Edge(char s, char e, int w) : start(s), end(e), weight(w), isBlocked(false), underConstruction(false), next(nullptr) {}
};

class Vertex {
public:
    char id;
    int greenTime; // Optional: For simulation purposes
    Edge* head;    // Points to the first edge
    Vertex* next;

    Vertex(char v) : id(v), greenTime(0), head(nullptr), next(nullptr) {}
    
    void addEdge(char end, int weight, bool isBlocked = false, bool underConstruction = false) {
        Edge* newEdge = new Edge(id, end, weight);
        newEdge->isBlocked = isBlocked;
        newEdge->underConstruction = underConstruction;
        newEdge->next = head;
        head = newEdge;
    }
};

class Graph {
private:
    Vertex* head;

    Vertex* getVertex(char id) {
        Vertex* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

//     void RoadNetwork(const string& filename) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cout << "Failed to open the file: " << filename << "\n";
//         return;
//     }
//     // Skip the first line (header)
//     string header;
//     getline(file, header);
//     string line;
//     while (getline(file, line)) {
//         size_t pos = 0;
//         string token;
//         string tokens[5];
//         int index = 0;
//         while ((pos = line.find(',')) != string::npos && index < 5) {
//             token = line.substr(0, pos);
//             tokens[index++] = token;
//             line.erase(0, pos + 1);
//         }
//         tokens[index] = line; // Last token
//         char startVertex = tokens[0][0];
//         char endVertex = tokens[1][0];
//         int edgeWeight = stoi(tokens[2]); // Convert weight to integer
//         bool blocked = (tokens[3] == "1");
//         bool construction = (tokens[4] == "1");
//         addEdge(startVertex, endVertex, edgeWeight, blocked, construction);
//     }
//     file.close();
// }

void RoadNetwork(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the file: " << filename << "\n";
        return;
    }
    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        string currentToken = "";
        string startVertexStr = "", endVertexStr = "", edgeWeightStr = "";
        int tokenIndex = 0;

        for (int j = 0; j <= line.length(); j++) 
        {
            if (line[j] == ',' || line[j] == '\0') {
                switch (tokenIndex) {
                    case 0:
                        startVertexStr = currentToken;
                        break;
                    case 1:
                        endVertexStr = currentToken;
                        break;
                    case 2:
                        edgeWeightStr = currentToken;
                        break;
                }
                tokenIndex++;
                currentToken = ""; 
            } else {
                currentToken += line[j];
            }
        }
        char startVertex = startVertexStr[0];
        char endVertex = endVertexStr[0];
        int edgeWeight = stoi(edgeWeightStr); 

        addEdge(startVertex, endVertex, edgeWeight);
    }

    file.close();
}

public:
    Graph() : head(nullptr) {}

    void addVertex(char id) {
        if (!getVertex(id)) {
            Vertex* newVertex = new Vertex(id);
            newVertex->next = head;
            head = newVertex;
        }
    }

    void addEdge(char start, char end, int weight, bool isBlocked = false, bool underConstruction = false) {
        addVertex(start);
        addVertex(end);
        Vertex* startVertex = getVertex(start);
        if (startVertex) {
            startVertex->addEdge(end, weight, isBlocked, underConstruction);
        }
    }

    void updateEdgeStatus(char start, char end, bool isBlocked, bool underConstruction) {
        Vertex* startVertex = getVertex(start);
        if (startVertex) {
            Edge* temp = startVertex->head;
            while (temp) {
                if (temp->end == end) {
                    temp->isBlocked = isBlocked;
                    temp->underConstruction = underConstruction;
                    return;
                }
                temp = temp->next;
            }
        }
        cout << "Edge not found.\n";
    }

    void displayBlockedRoads() {
        Vertex* temp = head;
        cout << "Blocked Roads:\n";
        while (temp) {
            Edge* edge = temp->head;
            while (edge) {
                if (edge->isBlocked) {
                    cout << edge->start << " -> " << edge->end << " (Weight: " << edge->weight << ")\n";
                }
                edge = edge->next;
            }
            temp = temp->next;
        }
    }

    void displayGraph() 
    {
        Vertex* temp = head;
        cout << "Graph Structure:\n";
        while (temp) {
            cout << "Vertex " << temp->id << ": ";
            Edge* edge = temp->head;
            while (edge) {
                cout << edge->start << " -> " << edge->end << " (Weight: " << edge->weight << ") ";
                edge = edge->next;
            }
            cout << "\n";
            temp = temp->next;
        }
    }

    void loadRoadNetwork(const string& filename) {
        RoadNetwork(filename);
    }
};

int main() {
    int x=0;
    Graph cityGraph;

    cityGraph.loadRoadNetwork("road_network.csv");

    cityGraph.displayBlockedRoads();
    cityGraph.displayGraph();

    return 0;
}
