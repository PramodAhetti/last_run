

#include<queue>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& graph, vector<int>& visited, int cur) {
    bool shouldVisit = false;
    
    // Critical section to safely check and mark visited
    #pragma omp critical
    {
        if (visited[cur] == 0) {
            visited[cur] = 1;
            shouldVisit = true;
            cout << cur << endl;
        }
    }

    if (shouldVisit) {
        // Parallelize visiting neighbors
        #pragma omp parallel for
        for (int i = 0; i < graph[cur].size(); i++) {
            dfs(graph, visited, graph[cur][i]);
        }
    }
}



void bfs(vector<vector<int>>& graph,vector<int>& visited, int cur) {
      queue<int> unvist;  
      unvist.push(cur);
      while(!unvist.empty()) {
        int cur = unvist.front();
        unvist.pop();
        cout << cur << endl;
        visited[cur] = 1;
        for (int i = 0; i < graph[cur].size(); i++) {
            if (visited[graph[cur][i]] == 0) {
                unvist.push(graph[cur][i]);
            }
        }
      }
        

}

int main() {
    vector<vector<int>> graph = {{1, 2}, {3, 2}, {0, 1}, {3, 2}};
    vector<int> visited(4, 0);

    // Start with one thread and allow spawning others
    #pragma omp parallel
    {
        #pragma omp single
        {
            dfs(graph, visited, 0);
        }
    }
    visited.assign(4, 0); // 
    cout<<"bfs"<<endl;
    cout<<"breadth first search"<<endl;
    bfs(graph,visited,0);
    return 0;
}
