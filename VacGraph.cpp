/**
 * @author Zzay
 *
 * @date 2021/05/23
 *
 * @brief Details of the functions of the graph.
 */

#include "VacGraph.h"
#define MAXV 105
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
    map = new int*[n];
    for (int i = 0; i < n; i++) map[i] = new int[n];
    readFromeFile();
    //FindBestVacAssistanceCity();
    //DecideMostVacStorageCity();
 //   FindBestDistributionCity(20000);
    DecideVacRequirementLevel(1);

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
        cout << "i: " << i << endl;
        Vex vex = v.at(i);
        sum+=FilterMostTotalCost(BEIJING - 1, vex.id - 1);
        sum+=FilterMostTotalCost(SHANGHAI - 1, vex.id - 1);
        sum+=FilterMostTotalCost(GUANGZHOU - 1, vex.id - 1);
        sum+=FilterMostTotalCost(WUHAN - 1, vex.id - 1);
        if (sum > max)
        {
            max = sum;
            re = vex.name;
        }
        cout << "Sum: " << sum << endl;
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
void CityGraph<T>::FindBestDistributionCity(int vaccination_amount)
{
    //BFS以每个城市为起点计算每个城市的总疫苗影响力,并且输出各个城市的总疫苗影响力

        double influence [MAXV];//各个城市的疫苗影响力

        int max = 0;
        int firstIndexOfMax = 0;
        int recordMaxIndex[MAXV] = {0};//若为1说明是最大值,0说明不是最大值

        for (int i = 0;i<MAXV;i++) {
            influence[i]=calInfluence(i, vaccination_amount);
            cout <<"City:"<<v[i].name<<"'s vaccine influence is:"<<influence[i]<<endl<<endl;
            if (influence[i] > max) {

                for (int k = 0; k < MAXV; k++) {
                    recordMaxIndex[k] = 0;
                }

                firstIndexOfMax = i;
                max = influence[i];
                recordMaxIndex[i] = 1;

            }else if(influence[i] == max){
                recordMaxIndex[i] = 1;
            }
            else {

            }
        }

        printf("\nthe maximum vaccine influence city is:");
        for (int k = 0; k < MAXV; k++) {
            if (recordMaxIndex[k] == 1) {

                cout << v[k].name << " ";
            }
        }

        cout <<"Their vaccine influence city is:"<< influence[firstIndexOfMax] <<endl;

}

template <class T>
double CityGraph<T>::calInfluence(int i,int numOfVaccine) {//给定疫苗数和城市,求疫苗影响力


    queue<char> q;				//定义一个队列,使用库函数queue
    bool visited[MAXV] = {0};		        //定义一个visited数组,记录已被访问的顶点
    int u;
    double influence=0;

    cout<<"Following calculate city "<<v[i].name<<"'s vaccine influence" << endl;
    //v = LocateVex(G,v0);//找到v0对应的下标
//	cout << v[i].name << " 正在分发疫苗" << endl;

    visited[i] = 1;		//顶点v0已被访问

    q.push(i);			//将i入队

    if (numOfVaccine >= v[i].confirmed) {
        numOfVaccine -= v[i].confirmed;//疫苗消耗量为城市确诊人数
        cout << v[i].name << "consume " << v[i].confirmed << " vaccines,and left" << numOfVaccine << " vaccines" << endl;
        influence += 1;
    }
    else {
        influence += (double)numOfVaccine / (double)v[i].confirmed;
        cout << v[i].name << "consume " << v[i].confirmed << " vaccines,and it is lack" << endl;
        return influence;
    }

    while (!q.empty())
    {

        u = q.front();				//将队头元素u出队,开始访问u的所有邻接点
        q.pop();			//将顶点u出队


        for (int j = 0; j < MAXV; j++)
        {

            if (map[u][j] && !visited[j])//顶点u和w间有边,且顶点w未被访问
            {
                printf("%d ", j);	//打印顶点w
                if (numOfVaccine>=v[j].confirmed) {
                    numOfVaccine -= v[j].confirmed;//疫苗消耗量为城市确诊人数
                    cout << v[j].name << "consume " << v[j].confirmed << " vaccines,and left " << numOfVaccine << " vaccines " << endl;
                    influence += 1;
                }
                else {
                    influence += (double)numOfVaccine / (double)v[j].confirmed;
                    cout << v[j].name << "consume " << v[j].confirmed << " vaccines,and it is lack " << endl;
                    return influence;
                }

                q.push(j);		//将顶点w入队
                visited[j] = 1;		//顶点w已被访问
            }
        }


    }
    cout << "All city is distributed over,and left "<<numOfVaccine<<" vaccines" << endl;
    return MAXV;

}


/**
 * Figure out the requirement level of a city towards vaccination when a new virus breaks out.
 *
 * @brief DecideVacRequirementLevel
 * @param virus_influence
 */
template <class T>
void CityGraph<T>::DecideVacRequirementLevel(int virus_influence)
{
    //BFS以每个城市为起点计算每个城市的总病毒影响力,并且输出各个城市的总病毒影响力

        double effect[MAXV];//各个城市的病毒影响力

        int max = 0;
        int firstIndexOfMax = 0;
        int recordMaxIndex[MAXV] = { 0 };//若为1说明是最大值,0说明不是最大值


        for (int i = 0; i < MAXV; i++) {
            effect[i] = calVirusEffect(i, virus_influence);
            cout << "City " << v[i].name << "'s virus influence is " << effect[i] << endl << endl;
            if (effect[i] > max) {

                for (int k = 0; k < MAXV; k++) {
                    recordMaxIndex[k] = 0;
                }

                firstIndexOfMax = i;
                max = effect[i];
                recordMaxIndex[i] = 1;

            }
            else if (effect[i] == max) {
                recordMaxIndex[i] = 1;
            }
            else {

            }
        }

        printf("\nthe maximum virus influence city is:");
        for (int k = 0; k < MAXV; k++) {
            if (recordMaxIndex[k] == 1) {

                cout << v[k].name << " ";
            }
        }

        cout << "their virus effect is " << effect[firstIndexOfMax] << endl;

}

template <class T>
double CityGraph<T>::calVirusEffect(int i, double virusEffectINIT) {//以某个城市为爆发起点的总病毒影响力

    queue<char> q;				//定义一个队列,使用库函数queue
    bool visited[MAXV] = { 0 };		        //定义一个visited数组,记录已被访问的顶点
    int u;
    double totalInfluence = 0;
    double virusEffect[MAXV] = {0};//每个城市对其他城市的病毒影响力

    cout << "Following calculate city: " << v[i].name << " 's virus effect " << endl;
    //v = LocateVex(G,v0);//找到v0对应的下标
//	cout << v[i].name << " 正在分发疫苗" << endl;

    visited[i] = 1;		//顶点v0已被访问

    q.push(i);			//将i入队

    if (virusEffectINIT >= v[i].ability) {

        cout << "city: " << v[i].name << " receive virus effect is " << virusEffectINIT << " ,after the city protect ability:" << v[i].ability << " weaken,left ";

        virusEffectINIT -= v[i].ability;
        virusEffect[i] = virusEffectINIT;
        cout<< virusEffect[i] << " virus effect" << endl;

    }
    else {
        cout << "city " << v[i].name << " after the city protect ability: " << v[i].ability << " weaken,has no virus effect" << endl;
        cout << "Current start from " << v[i].name << " total virus effect is" << totalInfluence << endl;
        return 0;
    }

    while (!q.empty())
    {

        u = q.front();				//将队头元素u出队,开始访问u的所有邻接点
        q.pop();			//将顶点u出队


        for (int j = 0; j < MAXV; j++)
        {

            if (map[u][j] && !visited[j])//顶点u和w间有边,且顶点w未被访问
            {
               // printf("%d ", j);	//打印顶点w
                if (virusEffect[u] >= v[j].ability) {

                    cout << "city " << v[j].name << " receive "<<v[u].name<<" 's virus effect is " << virusEffect[u] << " ,after the city protect ability:" << v[i].ability << " weaken,left ";

                    virusEffect[j] = virusEffect[u]-v[j].ability;//疫苗消耗量为城市确诊人数

                    cout << virusEffect[j] << " virus effect" << endl;

                }
                else {//防疫水平高于收到的病毒影响力

                    if (virusEffect[u] == 0) {//如果前一个城市已经没有病毒影响力,什么也不输出
                        virusEffect[j] = 0;
                    }else {
                        cout << "city: " << v[j].name << " receive virus effect is "<<virusEffect[u]<<" ,after the city protect ability:" << v[j].ability << " weaken,has no virus effect" << endl;
                        virusEffect[j] = 0;
                    }

                }

                q.push(j);		//将顶点w入队
                visited[j] = 1;		//顶点w已被访问
            }
        }


    }

    for (int j = 0; j < MAXV; j++){
        totalInfluence += virusEffect[j];
    }
    cout << "Start from " << v[i].name << " total virus effect is" << totalInfluence <<endl;
    return totalInfluence;


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
    onepath.push_back(s + 1);
    cout << ss << endl;
    allpath.push_back(onepath);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && map[s][i] > 0)
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
//    DFS(start);
//    vector<vector<int>> rere;
//    for (int i = 0; i < onepath.size(); i++)
//    {
//        string ss = onepath.at(i);
//        vector<int> r;
//        for (int j = 0; j < ss.length(); j++)
//        {
//            r.push_back(int(ss[j]) - 48);
//        }
//        if (r.back() - 1 == end)
//        {
//            rere.push_back(r);
//        }

//    }
//    vector <int>sum;
//    int min = INT_MAX;
//    int min_index = 0;
//    for (int i = 0; i < rere.size(); i++)
//    {
//        int total = 0;
//        vector<int> v = rere.at(i);
//        for (int j = 0; j < v.size() - 1; j++)
//        {
//            total += map[v.at(j) - 1][v.at(j + 1) - 1];
//        }
//        sum.push_back(total);
//        if (total < min)
//        {
//            min = total;
//            min_index = i;
//        }
//    }
//    cout << "最短路径为:";
//    for (int i = 0; i < rere.at(min_index).size(); i++)
//    {
//        cout << rere.at(min_index).at(i) << " ->";
//    }cout << "end" << endl;
//    return min;
}

template <class T>
int CityGraph<T>::FilterMostTotalCost(int start, int end)
{
    DFS(start);

    vector<vector<int>> rere;
    for (int i = 0; i < allpath.size(); i++)
    {
        vector<int>ss = allpath.at(i);
        if (ss.back() - 1 == end)
        {
            rere.push_back(ss);
        }

    }

    int sum;
    int min = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < rere.size(); i++)
    {

        int total = 0;
        vector<int> v2 = rere.at(i);
        for (int j = 0; j < v2.size() - 1; j++)
        {
            total += map[v2.at(j)-1][v2.at(j + 1)-1];
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
    ifstream myfile("F:\\Study\\GITSTROGRE\\algorithm-practice\\w.txt");

    for (int i = 0; i < 319; i++)
    {
        string temp;
        getline(myfile,temp);

        int v = stoi(temp);
        getline(myfile,temp);
        int u = stoi(temp);

        getline(myfile,temp);
        int dis = stoi(temp);
        //cout << dis << endl;
        map[v - 1][u - 1] = dis;
    }

    for (int i = 0; i < 105; i++)
    {
        for (int j = 0; j < 105; j++)
        {
            if(map[i][j]<0)
            map[i][j]=0;
        }

    }


    //read vertices info
    ifstream myfilev("F:\\Study\\GITSTROGRE\\algorithm-practice\\v.txt");

    for (int i = 0; i < 105; i++)
    {
        string temp;

        getline(myfilev,temp);//read ID
        int id = stoi(temp);

        getline(myfilev,temp);//read name
        string name = temp;

        getline(myfilev,temp);//read  longitude
        double longitude = stod(temp);

        getline(myfilev,temp);//read  latitude
        double latitude = stod(temp);



        getline(myfilev,temp);//read confirmed
        int confirmed = stoi(temp);

        getline(myfilev,temp);//read recovered
        int recovered = stoi(temp);

        double ability=recovered*1.0/(confirmed*1.0+1);
         //double ability=100;

        v.push_back({id,name,longitude,latitude,confirmed,recovered,ability});
//        double longitude; // Longitude of the city.
//        double latitude;  // Latitude of the city.
//        int confirmed;    // Amount of confirmed cases in the city.
//        int recovered;    // Amount of recovered cases in the city.
//        double ability;

    }

     myfilev.close();

//     cout << "done" << endl;
//    for (int i = 0; i < 105; i++)
//    {
//     cout<<v[i].ability<<endl;

//    }

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
