# Techniques-from-practice

## Dynamic Programming

* Calculate the maximum cost to visit (1, 1) to (n, m) in a matrix, 
  ```
  FOR(i, 1, n + 1){
      FOR(j, 1, m + 1){
          Dp[i][j] = max(Dp[i - 1][j], Dp[i][j - 1]) + arr[i][j];
      }
  }
  ```
