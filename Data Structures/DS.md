## Data Structures

<details>
<summary>  
    Binary Indexed Tree / Fenwick Tree 
</summary>

**Problem:** [CSES Range Sum Queries II](https://cses.fi/problemset/task/1648)

**Code:**

```cpp
ll n, q;
ll old[MX];
ll Tree[MX]; // 1 - indexed.

ll Update(ll idx, ll value){
    while(idx <= n){
        Tree[idx] += value;
        idx += (idx & -idx);
    }
}

ll Sum(ll idx){
    ll sum = 0;
    while(idx){
        sum += Tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

ll Query(ll L, ll R){
    return Sum(R) - Sum(L - 1);
}

int main(){

    setIO();

    cin >> n >> q;

    FOR(i, 1, n + 1){
        cin >> old[i];
        Update(i, old[i]);
    }

    F0R(i, q){

        ll operation_type;
        cin >> operation_type;

        if(operation_type == 1){
            ll change_index, new_value;
            cin >> change_index >> new_value;
            Update(change_index, new_value - old[change_index]);
            old[change_index] = new_value;
        }
        else{
            ll L, R;
            cin >> L >> R;
            cout << Query(L, R) << "\n";
        }
    }
}
```
</details>
