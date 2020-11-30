## Graph Theory

<details>
<summary>  
    Dijkstra
</summary>
    
```cpp
ll n, m;
vector<pair<ll, ll>> adj[MX];
ll Distance[MX], From[MX]; // From array needed when you need the path.
bool processed[MX];
priority_queue<pair<ll, ll>> PQ;
 
void Dijkstra(int start){
 
    FOR(i, 1, n + 1) Distance[i] = INF;
    Distance[start] = 0;
    PQ.push({0, start});
 
    while(!PQ.empty()){
 
        int a = PQ.top().ss; PQ.pop();
 
        if(processed[a]) continue;
        processed[a] = true;
 
        for(auto u : adj[a]){
 
            ll b = u.ff, w = u.ss;
 
            if(Distance[a] + w < Distance[b]){
                Distance[b] = Distance[a] + w;
                PQ.push({-Distance[b], b});
                From[b] = a;
            }
        }
    }
}
```
</details>

<details>
<summary>  
    Topological Sort 
</summary>
    
```cpp
int n, m;
vi Graph[MX], top_sort; // Assume that this Graph is a DAG
bool visited[MX];
 
void DFS(int node){
 
    if(visited[node]) return;
    visited[node] = true;
 
    for(auto u : Graph[node]) DFS(u);
 
    top_sort.pb(node);
}
 
void Compute(){
 
    FOR(i, 1, n + 1) if(!visited[i]) DFS(i);
 
    reverse(all(top_sort));
}
 
bool Valid(vi top_sort){
 
    int indx[n + 1];
    F0R(i, n) indx[top_sort[i]] = i + 1;
 
    FOR(i, 1, n + 1){
        for(auto u : Graph[i]){
            if(indx[u] <= indx[i]){
                return false;
            }
        }
    }
 
    return true;
}
 
int main(){
 
    setIO();
 
    cin >> n >> m;
 
    F0R(i, m){
        int a, b;
        cin >> a >> b;
        Graph[a].pb(b);
    }
 
    Compute();
 
    if(!Valid(top_sort)){
        cout << "IMPOSSIBLE";
        return 0;
    }
    else for(auto it : top_sort) cout << it << " ";
}
```
</details>
