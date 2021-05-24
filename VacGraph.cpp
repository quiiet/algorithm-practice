/**
 * @author Zzay
 *
 * @date 2021/05/23
 *
 * @brief Details of the functions of the graph.
 */

#include "VacGraph.h"

/**
 * Constructor. Initialize the amount of vertices.
 *
 * @brief CityGraph<T>::CityGraph
 * @param vertices The amount of vertices.
 */
template <class T>
CityGraph<T>::CityGraph(int vertices)
{
    vertexNum = vertices;
    n = vertices;
    edgeNum = 0;
    graphMatrix = new T*[vertexNum + 1];
    for (int i = 1; i <= vertexNum; i++) {
        graphMatrix[i] = new T[vertexNum + 1];
    }
    // Initalize the whole graph with 0.
    for (int i = 1; i <= vertexNum; i++) {
        for (int j = 1; j <= vertexNum; j++) {
            graphMatrix[i][j] = 0;
        }
    }
    //initialize distance matrix
    a = new int*[n];
    for (int i = 0; i < n; i++) a[i] = new int[n];
    readFromeFile();
    //FindBestVacAssistanceCity();
    //DecideMostVacStorageCity();
}

/**
 * Constructor. Initialize the vertices by giving a double-dimension array.
 *
 * @brief CityGraph<T>::CityGraph
 * @param adjMatrix The adjacent matrix.
 * @param vNum The amount of the vertices.
 */
template <class T>
CityGraph<T>::CityGraph(T** adjMatrix, int vNum)
{
    vertexNum = vNum;
    edgeNum = 0;
    graphMatrix = adjMatrix;
    for (int i = 1; i <= vertexNum; i++) {
        vertices[i] = i;
        for (int j = i; j <= vertexNum; j++) {
            if ((graphMatrix[i][j] != INF) && (graphMatrix[i][j] != 0)) {
                edgeNum++;
                edgeSet.push_back(edge(i, j, graphMatrix[i][j]));
            }
        }
    }
}

/**
 * Find the best assistacne city by using DFS algorithm.
 *
 * @brief FindBestVacAssistanceCity
 * @param name The name of the city to get assistance.
 */
template <class T>
void CityGraph<T>:: FindBestVacAssistanceCity(Vex name)
{
    int end = name.id;
    int d1, d2, d3, d4;
    d1 = FilterShortest(BEIJING - 1, end - 1);
    d2 = FilterShortest(SHANGHAI - 1, end - 1);
    d3 = FilterShortest(GUANGZHOU - 1, end - 1);
    d4 = FilterShortest(WUHAN - 1, end - 1);
    string res;
    int min = INT_MAX;
    if (d1 < min)
    {
        min = d1;
        res = "Beijing";
    }
    if (d2 < d1)
    {
        min = d2;
        res = "Shanghai";
    }
    if (d3 < d2)
    {
        min = d3;
        res = "Guangzhou";
    }
    if (d4 < d3)
    {
        min = d4;
        res = "Wuhan";
    }
    cout << "For " << name.name << " BestVacAssistanceCity is" << res << endl;
}

/**
 * Figure out the city that needs most vaccination storage.
 *
 * @brief DecideMostVacStorageCity
*/
template <class T>
void CityGraph<T>:: DecideMostVacStorageCity()
{
    //int end = name.id;
    int max = 0;
    int sum;
    string re;
    for (int i = 0; i < 105; i++)
    {

        Vex vex = vexes.at(i);
        sum+=FilterMostTotalCost(BEIJING - 1, vex.id - 1);
        sum+=FilterMostTotalCost(SHANGHAI - 1, vex.id - 1);
        sum+=FilterMostTotalCost(GUANGZHOU - 1, vex.id - 1);
        sum+=FilterMostTotalCost(WUHAN - 1, vex.id - 1);
        if (sum > max)
        {
            max = sum;
            re = vex.name;
        }
        sum = 0;
    }
    cout <<"Best storage city is" << re << endl;
}

/**
 * Find out the city that can bring most benefits with given vaccination.
 *
 * @brief FindBestDistributionCity
 * @param vaccination_amount
 */
template <class T>
void FindBestDistributionCity(int vaccination_amount)
{

}

/**
 * Figure out the requirement level of a city towards vaccination when a new virus breaks out.
 *
 * @brief DecideVacRequirementLevel
 * @param virus_influence
 */
template <class T>
void DecideVacRequirementLevel(int virus_influence)
{

}

// Judge whether there's an edge between two specified vertices.
template <class T>
bool CityGraph<T>::IsExist(int srcVertex, int destVertex)
{
    // If given parameters are invalid.
    if (srcVertex < 1 || destVertex < 1 || srcVertex > vertexNum || destVertex > vertexNum) {
        throw myException("ERROR. Given indexes are invalid.");
    }
    // If there's no such edge.
    if(graphMatrix[srcVertex][destVertex] == 0) {
        return false;
    }
    return true;
}

// Add an edge (i,j) to the graph if it does not exist.
template <class T>
void CityGraph<T>::AddEdge(int srcVertex, int destVertex, double distance)
{
    // If given parameters are invalid.
    if (srcVertex < 1 || destVertex < 1 || srcVertex > vertexNum ||
            destVertex > vertexNum || srcVertex == destVertex) {
        throw myException("ERROR. Given parameters are invalid.");
    }
    // If there's already an edge.
    if (graphMatrix[srcVertex][destVertex] != 0) {
        cout << "The edge has already existed." << endl;
        return;
    }
    // Assign value to both coordinates.
    graphMatrix[srcVertex][destVertex] = graphMatrix[destVertex][srcVertex] = distance;
    edgeNum++;
}

template <class T>
void CityGraph<T>::AddEdge(int i, int j, int weight, int**&a)
{
    if (i < 0 || j < 0 || i > n || j > n || i == j || a[i][j] != 0)
        return;
    a[i][j] = a[j][i] = weight;
    Edge e2;
    e2.city1 = i - 1;
    e2.city2 = j - 1;
    e2.distance = weight;
    edges.push_back(e2);
}

// Delete the edge (i,j) if it exists.
template <class T>
void CityGraph<T>::DelEdge(int srcVertex, int destVertex)
{
    // If given parameters are invalid.
    if (srcVertex < 1 || destVertex < 1 || srcVertex > vertexNum ||
            destVertex > vertexNum || srcVertex == destVertex) {
        throw myException("ERROR. Given parameters are invalid.");
    }
    if (graphMatrix[srcVertex][destVertex] == 0) {
        cout << "The edge does not exist." << endl;
        return;
    }
    // Assign value to both coordinates.
    graphMatrix[srcVertex][destVertex] = graphMatrix[destVertex][srcVertex] = 0;
    edgeNum--;
}

// Output the adjacency matrix.
template <class T>
string CityGraph<T>::ToString()
{
    ostringstream os;
    for (int i = 1; i <= vertexNum; i++) {
        for (int j = 1; j <= vertexNum; j++) {
            if (graphMatrix[i][j] == INF) {
                os << "��  ";
                continue;
            }
            os << graphMatrix[i][j] << "   ";
        }
        os << endl << endl;
    }
    os << endl;
    return os.str();
}

template <class T>
void CityGraph<T>::DFS(int s)
{
    string ss;
    dfs(s, visited, ss);
}

template <class T>
void CityGraph<T>::dfs(int s, bool* visited, string ss)
{
    if (s < 0 || s > n-1)
    {
        return;
    }
    visited[s] = true;
    ss += to_string(s + 1);
    str_paths.push_back(ss);
    //cout << ss << endl;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && a[s][i] > 0)
        {
            //cout << s+1 << " "; visited[s] = true;
            dfs(i, visited, ss);
            //cout << endl;
        }
    }
    visited[s + 1] = false;
}

template <class T>
int CityGraph<T>:: FilterShortest(int start, int end)
{
    DFS(start);
    vector<vector<int>> rere;
    for (int i = 0; i < str_paths.size(); i++)
    {
        string ss = str_paths.at(i);
        vector<int> r;
        for (int j = 0; j < ss.length(); j++)
        {
            r.push_back(int(ss[j]) - 48);
        }
        if (r.back() - 1 == end)
        {
            rere.push_back(r);
        }

    }
    vector <int>sum;
    int min = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < rere.size(); i++)
    {
        int total = 0;
        vector<int> v = rere.at(i);
        for (int j = 0; j < v.size() - 1; j++)
        {
            total += a[v.at(j) - 1][v.at(j + 1) - 1];
        }
        sum.push_back(total);
        if (total < min)
        {
            min = total;
            min_index = i;
        }
    }
//    cout << "最短路径为：";
//    for (int i = 0; i < rere.at(min_index).size(); i++)
//    {
//        cout << rere.at(min_index).at(i) << " ->";
//    }cout << "end" << endl;
    return min;
}

template <class T>
int CityGraph<T>::FilterMostTotalCost(int start, int end)
{
    DFS(start);
    vector<vector<int>> rere;
    for (int i = 0; i < str_paths.size(); i++)
    {
        string ss = str_paths.at(i);
        vector<int> r;
        for (int j = 0; j < ss.length(); j++)
        {
            r.push_back(int(ss[j]) - 48);
        }
        if (r.back() - 1 == end)
        {
            rere.push_back(r);
        }

    }
    int sum;
    int min = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < rere.size(); i++)
    {
        int total = 0;
        vector<int> v = rere.at(i);
        for (int j = 0; j < v.size() - 1; j++)
        {
            total += a[v.at(j) - 1][v.at(j + 1) - 1];
        }
        sum += total;
        if (total < min)
        {
            min = total;
            min_index = i;
        }
    }
    return sum;
}

template <class T>
void CityGraph<T>:: readFromeFile()
{
    ifstream myfile("F:\\VacTransport\\w.txt");
    for (int i = 0; i < 319; i++)
    {
        string temp;
        getline(myfile,temp);
        cout << temp << endl;
        int v = stoi(temp);
        getline(myfile,temp);
        int u = stoi(temp);
        getline(myfile,temp);
        int dis = stoi(temp);
        a[v - 1][u - 1] = dis;
    }
    print(a, 105, 105);
    myfile.close();
}

template <class T>
void CityGraph<T>::print(int **a, int cols, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
