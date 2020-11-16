// Complexity: O(n^3)
// We will run n (1, 2, ..., n) rounds. For each the nodes will compare the ith nearest node.
// Thus we can update the shortest path between each pair of nodes.

int n, m;
int Dist[n][n];
int Adj[n][n];

void Floyd_Warshall(){
    
    FOR(i, 1, n + 1){       // Keep Dist[i][j] ready with adjacency matrix.
        FOR(j, 1, n + 1){
            if(i == j) Dist[i][j] = 0;
            else if(Adj[i][j]) Dist[i][j] = Adj[i][j];
            else Dist[i][j] = MOD; // INF
        }
    }
    
    FOR(k, 1, n + 1){
        FOR(i, 1, n + 1){
            FOR(j, 1, n + 1){
                Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
            }
        }
    }
}
