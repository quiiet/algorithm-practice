/**
 * @author Zzay
 *
 * @date 2021/05/19
 *
 * @brief Structure of edges, nodes and the construction of the graph network.
 */

#ifndef VACGRAPH_H
#define VACGRAPH_H

#define BEIJING 8
#define SHANGHAI 1
#define GUANGZHOU 31
#define WUHAN 69

#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "arrayQueue.h"
#include "myExceptions.h"
#include <stack>
#include <fstream>
#include <queue>

#define MAX_SIZE 128
#define INF 65535
using namespace std;

// The vertex structure.
typedef struct Vex {
    int id;           // Id of the city.
    string name;      // Name of the city.
    double longitude; // Longitude of the city.
    double latitude;  // Latitude of the city.
    int confirmed;    // Amount of confirmed cases in the city.
    int recovered;    // Amount of recovered cases in the city.
    double ability;      // The city's anti-epidemic ability (recovered cases / confirmed cases).
} City;

// The edge structure.
struct Edge {
    int city1;    // Id of the first connected city.
    int city2;    // Id of the second connected city.
    int distance; // Distance between the two connected cities.
};

// Weighted Matrix Graph.
template<class T>
class CityGraph {
public:
    CityGraph(int vertices);
    // Constructor. Initialize the vertex number as well.
    CityGraph(T** adjMatrix, int vertices);
    // Constructor. Initialize the vertices by giving a double-dimension array.
    ~CityGraph() { delete[] graphMatrix; }
    // Destructor. Delete the graph matrix array.
    string ToString();
    // Output the adjacency matrix.
public:
    void FindBestVacAssistanceCity(Vex name);
    // Find the best assistacne city by using DFS algorithm.
    void DecideMostVacStorageCity();
    // Figure out the city that needs most vaccination storage.
    void FindBestDistributionCity(int vaccination_amount);
    // Find out the city that can bring most benefits with given vaccination.
    void DecideVacRequirementLevel(int virus_influence);
    // Figure out the requirement level of a city towards vaccination when a new virus breaks out.
    double calInfluence(int i,int numOfVaccine);
    //Calculate the city's influence
    double calVirusEffect(int i, double virusEffectINIT);
    //Calculate the city's virus effect
private:
    int vertexNum;           // Number of vertices.
    int edgeNum;             // Number of edges.
    int vertices[MAX_SIZE];  // Vertices array.
    T** graphMatrix;         // An adjacent matrix of the WMGraph
    vector<Edge> edgeSet;    // Set storing edges in the graph.
    vector<Edge> edges;      //
    vector <int> onepath;//????????????
    vector <vector <int>> allpath;//????????????
    vector<int> re;
    vector<Vex> v;
    stack<int> stacks;
    int n = 105;
    int **map;                 //Distance matrix
private:
    bool IsExist(int srcVertex, int destVertex);
    // Judge whether there's an edge between two specified vertices.
    int GetVertexNum() { return vertexNum; }
    // Return the number of the vertices.
    int GetEdgeNum() { return edgeNum; }
    // Return the number of the edges.
    void AddEdge(int srcVertex, int destVertex, double distance);
    // Add an edge (i,j) to the graph if it does not exist.
    void AddEdge(int i, int j, int weight, int**&a);
    //???????????????
    void DelEdge(int srcVertex, int destVertex);
    // Delete the edge (i,j) if it exists.
    void DFS(int s);
    void dfs(int s, bool* visited, string ss);
    int FilterShortest(int start, int end, int route);
    //Find minumun cost between two vertices
    int FilterMostTotalCost(int start, int end);
    //Finid maxmun total cost of all path between two vertices
    void readFromeFile();
    void print(int **a, int cols, int rows);
};

#endif // VACGRAPH_H
