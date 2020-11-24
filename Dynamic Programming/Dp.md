## Dynamic Programming

<details>
<summary>  
    Calculate the maximum cost to visit (1, 1) to (n, m) in a matrix, 
</summary>

```cpp
FOR(i, 1, n + 1){
    FOR(j, 1, m + 1){
        Dp[i][j] = max(Dp[i - 1][j], Dp[i][j - 1]) + arr[i][j];
    }
}
```
</details>

<details>
<summary>  
    Two way Dp
</summary>

**Problem:** [CF Bear and Blocks R1600](https://codeforces.com/problemset/problem/573/B)

**Solution Link:** https://codeforces.com/contest/573/submission/97623198
</details>

<details>
<summary>  
    Optimizing DP with Number Theory
</summary>

**Problem:** [CF Multiplicity R1700](https://codeforces.com/problemset/problem/1061/C)

**Solution Link:** https://codeforces.com/contest/1061/submission/97968104
</details>

<details>
<summary>  
    Subset Sum equals k 
</summary>

```cpp
// GeeksforGeeks.
bool isSubsetSum(vector<int> Set, int n, int sum){
 
    bool subset[n + 1][sum + 1];
 
    F0R(i, n + 1) subset[i][0] = true;    // We can always make 0.
    F0R(i, sum + 1) subset[0][i] = false; // We can't make anything without taking a single element.
        
 
    FOR(i, 1, n + 1){
        FOR(j, 1, sum + 1){
            if(j < Set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if(j >= Set[i - 1])
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - Set[i - 1]];
        }
    }
 
    return subset[n][sum];
}
```

**Problem:** [CF Unmerge R1800](https://codeforces.com/contest/1381/problem/B)
**Solution Link:** https://codeforces.com/contest/1381/submission/99295496
</details>
