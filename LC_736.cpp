using namespace std;


typedef pair<int, int> v_dist; 
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        //find source
        set<int, greater<int>> s;
        map<int, vector<int>> graph;
        set<int>::iterator it;
        vector<bool> visited(N+1, false);
        list<int> queue;
        
        //construct graph
        for (auto& v: times){
            s.insert(v[1]);
            visited[v[0]] = false;
            visited[v[1]] = false;
            if (graph.find(v[0]) == graph.end())
                graph[v[0]]= {v[1], v[2]};
            else{
                vector<int>& children = graph[v[0]];
                children.push_back(v[1]);
                children.push_back(v[2]);
            }
        }
        
        //check reachability of source by BFS
        visited[K] = true;
        queue.push_back(K);
        
        while(!queue.empty()){
            int curNode = queue.front();
            queue.pop_front();

            for (int i = 0; i < (graph[curNode].size())/2; i++){
                int child = graph[curNode][i*2];
                if (!visited[child]){
                    visited[child] = true;
                    queue.push_back(child);
                }   
            }  
        }
        
        for (unsigned int i = 1; i< visited.size(); i++){
            if (!visited[i])
                return -1;
        }
        
        int delay_time = max_shortest_path(K, graph, N);
        return delay_time; 
    }
    
    
    int max_shortest_path(int source, std::map<int, vector<int>>& g, int N){
        vector<int> dist(N+1, 600000);
        priority_queue<v_dist, vector<v_dist>, greater<v_dist>> vertex_set;
        vertex_set.push(make_pair(0, source));
        dist[source] = 0;
        while (!vertex_set.empty()){
            int curNode = vertex_set.top().second;
            vertex_set.pop();

            for (int i = 0; i < (g[curNode].size())/2; i++){
                int v = g[curNode][i*2];
                int v_weight = g[curNode][i*2+1];
                if (dist[v] > dist[curNode] + v_weight){
                    dist[v] = dist[curNode] + v_weight;
                    vertex_set.push(make_pair(dist[v], v));
                }       
            }
        }         
        int max_min_dist = -1;
        for (int i = 1; i < N+1; i++){
            if (dist[i] > max_min_dist)
                max_min_dist = dist[i];
        }
        return max_min_dist;
    }
    