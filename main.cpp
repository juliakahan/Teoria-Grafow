
#include <iostream>
#include <climits>
#include <queue>
#include <string>
#include <fstream>
#define MAX 7

using namespace std;


class FFmethod
{
public:
    int costs[MAX][MAX];
    bool visited[MAX] = {false};
    int residualGraph[MAX][MAX];
    int graph[MAX][MAX];





    bool bfs(int src, int bfsSink, int parent[])
    {
        memset(visited, 0, sizeof(visited));
        queue<int> q;
        q.push(src);
        visited[src] = true;
        parent[src] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < MAX; v++) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    if (v == bfsSink) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return false;


    }




    void initGraph () 
    {
        fstream graphFile;
        graphFile.open("adjacencyList.txt", ios::in);
        if (!graphFile.good())
        {
            cout << "cannot open given file";
            exit(1);
        }

        int i = 0, j = 0, n = 0;
        while( graphFile >> residualGraph[ i ][ j ] )
        {
            if( ++j >= MAX ) {
                j = 0;
                i++;
            }
            n++;
            if( n >= MAX*MAX ) break;

        }
        graphFile.close();

        }




    int fordFulkerson(int FFsrc, int FFsink)
    {
        int edg, vert;



        int parent[MAX];

        int max_flow = 0; // na poczatku przeplyw jest zerowy

        // rozszerzamy przeplyw o sciezke, jesli istnieje
        while (bfs( FFsrc, FFsink, parent)) {
            //szukamy max przeplywu w danej sciezce
            int path_flow = INT_MAX;
            for (vert = FFsink; vert != FFsrc; vert = parent[vert]) {
                edg = parent[vert];
                path_flow = min(path_flow, residualGraph[edg][vert]);
            }

            //aktualizujemy wartosci pojemnosci
            for (vert = FFsink; vert != FFsink; vert = parent[vert]) {
                edg = parent[vert];
                residualGraph[edg][vert] -= path_flow;
                residualGraph[vert][edg] += path_flow;
            }

            // zwiekszamy przeplyw calkowity o przeplyw obecnie analizowanej sciezki
            max_flow += path_flow;
        }


        return max_flow;
    }

};

int main()
{
    FFmethod A;
    A.initGraph();

    cout<<"maxflow is: " << A.fordFulkerson(1,5);

    return 0;
}



