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

<details>
<summary>  
    Disjoint Set Union (DSU)
</summary>
    
**Problem:** [Yosupo OJ Union Find](https://judge.yosupo.jp/problem/unionfind)

**Code:**
    
```cpp
int n, q;
int Size[MX], Path[MX]; // 1 - indexed.

void Initialize(){
    FOR(i, 1, n + 1) Size[i] = 1, Path[i] = i; // Initial Size for all i is 1 and Path is i.
}

int Find(int x){
    return (x == Path[x] ? x : Path[x] = Find(Path[x])); // Finding the root path.
}

bool Same(int a, int b){
    return Find(a) == Find(b); // If both a and b are from same root path.
}

void Unite(int a, int b){
    a = Find(a);
    b = Find(b);
    if(Size[a] < Size[b]) swap(a, b);
    Size[a] += Size[b];
    Path[b] = a;        // New path for b is the path of a.
}

int main(){

    setIO();

    cin >> n >> q;

    Initialize();

    F0R(i, q){

        int t, a, b;
        cin >> t >> a >> b;

        if(t == 0){
            Unite(a + 1, b + 1);
        }
        else{
            cout << Same(a + 1, b + 1) << "\n";
        }
    }
}
```
</details>

<details>
<summary>  
    DSU template from Benq
</summary>
    
```cpp
struct DSU { // 0 - indexed.
    vi e; void init(int N){ e = vi(N,-1); }
    // get representive component, uses path compression
    int get(int x){ return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool sameSet(int a, int b){ return get(a) == get(b); }
    int size(int x){ return -e[get(x)]; }
    bool unite(int x, int y) { // union by size
        x = get(x), y = get(y); if(x == y) return 0;
        if(e[x] > e[y]) swap(x, y); // e[x] < 0 means size = -e[x], 
        e[x] += e[y]; e[y] = x; return 1; // e[x] >= 0 means root path of x = e[x].
    }
};
```
</details>

<details>
<summary>  
    Bipertite Checking by BFS
</summary>
    
```cpp
int n;
vi adj[MX], side(MX, -1);
queue<int> Q;

bool is_Bipertite(){ // 1 - indexed Graph.

    bool ok = true;

    FOR(node, 1, n + 1){
        if(side[node] == -1){
            Q.push(node);
            side[node] = 0;
            while(!Q.empty()){
                int v = Q.front(); Q.pop();
                for(auto u : adj[v]){
                    if(side[u] == -1){
                        side[u] = side[v] ^ 1;
                        Q.push(u);
                    }
                    else ok &= side[u] != side[v];
                }
            }
        }
    }

    return ok;
}
```
</details>

<details>
<summary>  
    Finding cycle in an undirected graph
</summary>

**Problem:** [CSES Round Trip](https://cses.fi/problemset/task/1669/)

**Code:**
```cpp
int n, m, from[MX], sv, ev;
vi adj[MX], cycle;
bool cycle_found = false, visited[MX];

bool DFS(int node, int parent){

    visited[node] = true;
    from[node] = parent;

    for(auto u : adj[node]){
        if(visited[u] && u != parent){
            cycle_found = true;
            sv = u;    // starting vertex.
            ev = node; // ending vertex.
            return true;
        }
        else if(!visited[u]) if(DFS(u, node)) return true;
    }
    return false;
}

int main(){

    setIO();

    cin >> n >> m;

    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    FOR(i, 1, n + 1){
        if(!visited[i]) DFS(i, 0);
        if(cycle_found){

            cycle.pb(sv);    // Get the cycle by the from array.
            while(ev != sv){
                cycle.pb(ev);
                ev = from[ev];
            }
            cycle.pb(sv);

            cout << sz(cycle) << "\n";
            for(auto it : cycle) cout << it << " ";
            return 0;
        }
    }

    cout << "IMPOSSIBLE";
}
```
</details>


