# Techniques-from-practice

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



## Strings

### Prefix Function
```cpp
/*
    everything 0-indexed
    pi[i] = 0 -> empty string matched
    pi[i] = j -> prefix s[0..(j)] matched
*/
int prefixFunction(const string& s){

    int n = sz(s);

    vector<int> pi(n);

    FOR(i, 1, n){

        int j = pi[i - 1];

        /*
            while there is some matching left before it
            if Characters at the positions are equal : break
            else : go to next smaller matching.

            more explanation: https://codeforces.com/blog/entry/84359?#comment-718894.
        */
        while(j > 0 && s[j] != s[i]) j = pi[j - 1];

        if(s[j] == s[i]) j++;
        pi[i] = j;
    }
    return pi[n - 1];
}
```
**Problem:** CF Camp Schedule R1600

**Solution Link:** https://codeforces.com/contest/1137/submission/97693928
