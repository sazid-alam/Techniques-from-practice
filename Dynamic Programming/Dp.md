## Dynamic Programming

### Calculate the maximum cost to visit (1, 1) to (n, m) in a matrix, 
```cpp
FOR(i, 1, n + 1){
    FOR(j, 1, m + 1){
        Dp[i][j] = max(Dp[i - 1][j], Dp[i][j - 1]) + arr[i][j];
    }
}
```
### Two way Dp
**Problem:** [CF Bear and Blocks R1600](https://codeforces.com/problemset/problem/573/B)

**Solution Link:** https://codeforces.com/contest/573/submission/97623198

### Optimizing Dp with Number Theory
**Problem:** [CF Multiplicity R1700](https://codeforces.com/problemset/problem/1061/C)

**Solution Link:** https://codeforces.com/contest/1061/submission/97968104
