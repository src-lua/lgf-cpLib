# Code snippets in C++
## Code template

* ### Pattern &nbsp; `"pattern"`
  Competitive programming boilerplate with optimized I/O for fast execution.

  ```c++
  #include <bits/stdc++.h>

  #define endl '\n'

  using namespace std;

  int main() {
      ios::sync_with_stdio(false);
      cin.tie(0);

      /* code */

      return 0;
  }
  ```
* ### Pattern with Test Cases &nbsp; `"patterntc"`
  Competitive programming boilerplate with optimized I/O for fast execution and repeating code block for multiple test cases.

  ```c++
  #include <bits/stdc++.h>

  #define endl '\n'

  using namespace std;

  int solve() {

      /* code */

      return 0;
  }

  int main() {
      ios::sync_with_stdio(false);
      cin.tie(0);

      int tc; cin >> tc; while (tc--) {
          solve();
      }

      return 0;
  }
  ```

* ### I/O &nbsp; `"I/O"`
  Redirecting standard input/output to files for automated testing and evaluation.

  ```c++
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ```
* ### Test cases &nbsp; `"tc", "test_cases" `
  Repeating code block for multiple test cases.

  ```c++
  int tc; cin >> tc; while (tc--) {
      solve();
  }
  ```
* ### Solve Function &nbsp; `"solve" `
  Function for solving the problem.

  ```c++
  int solve() {

      /* code */

      return 0;
  }
  ```

<br>

## Type macros

* ### Define long long &nbsp; `"ll"`
  Aliasing a shorter name for the `long long` data type for convenience.

  ```c++
  using ll = long long;
  ```
* ### Int -> long long &nbsp; `"defintll", "int to ll"`
  Redefining `int` to `long long` for wider integer range by default.

  ```c++
  #define int long long //change main to int32_t
  ```
* ### Pair of ints `"pii"`
  Creating a concise alias `pii` for the `pair<int, int>` data type to simplify code.
  
  ```c++
  using pii = pair<int,int>;
  ```
* ### Tuple of ints `"iii"`
  Establishing a succinct alias `iii` for the `tuple<int, int, int>` data type to enhance readability.


  ```c++
  using iii = tuple<int,int,int>
  ```

<br>

## Nested loops

* ### 2 nested for loops &nbsp; `"2for"`
  Nested loops iterating through a 2D structure or grid-like pattern.
  ```c++
  for (int i = 0; i < a; i++) {
      for (int j = 0; j < b; j++) {
          /* code  */
      }
  }
  ```
* ### 3 nested for loops &nbsp; `"3for"`
  Triple-nested loops traversing a 3D structure or cube-like arrangement.
  ```c++
  for (int i = 0; i < a; i++) {
      for (int j = 0; j < b; j++) {
          for (int k = 0; k < c; k++) {
              /* code  */
          }
      }
  }
  ```

<br>

## Reading and iterating through boards (matrices)

* ### Reading a Board NxN &nbsp; `"NxN", "boardN"`
  Reading a square board of size N x N from input.
  
  ```c++
  int n; char c;

  cin >> n;

  char board[n][n];

  for (int i = 0; i < n; i++) {
      cin.get();
      for (int j = 0; j < n; j++) {
          cin.get(c);
          board[i][j] = c;
      }
  }
  ```
* ### Reading a board row x col &nbsp; `"rowXcol", "rxc", "boardrowcol"`
  Reading a rectangular board of variable dimensions from input.

  ```c++
  int row, col; char c;

  cin >> row >> col;

  char board[row][col];

  for (int i = 0; i < row; i++) {
      cin.get();
      for (int j = 0; j < col; j++) {
          cin.get(c);
          board[i][j] = c;
      }
  }
  ```
* ### dx 4 directions  &nbsp; `"dx4"`
  Declaring an array for common horizontal movement offsets in grid-based problems.

  ```c++
  const int dx[] = {0,0,1,-1};
  ```
* ### dy 4 directions  &nbsp; `"dy4"`
  Declaring an array for common vertical movement offsets in grid-based problems.

  ```c++
  const int dy[] = {1,-1,0,0};
  ```
* ### dx 8 directions  &nbsp; `"dx8"`
  Declaring an array for horizontal offsets representing all 8 adjacent directions in a grid, including diagonals.

  ```c++
  const int dx[] = {0, 0, 1,-1, 1, 1,-1,-1};
  ```
* ### dy 8 directions  &nbsp; `"dy8"`
  Declaring an array for vertical offsets corresponding to all 8 adjacent directions in a grid, including diagonals.

  ```c++
  const int dy[] = {1,-1, 0, 0,-1, 1,-1, 1};
  ```

<br>

## Quality of life (QoL)

* ### Max/min of 3 elements  &nbsp; `"defmax3", "defmin3", "maxmin3"`
  Defining macros for finding minimum and maximum among three values.

  ```c++
  #define min3(a,b,c) (min((a),min((b),(c)))) 
  #define max3(a,b,c) (max((a),max((b),(c)))) 
  ```
* ### MOD  &nbsp; `"MOD", "1e9+7"`
  Defining a constant modulo value for calculations preventing integer overflow and ensuring compatibility with algorithms that rely on prime numbers.
  
  ```c++
  const int MOD = 1e9+7; //pay attention with others MOD numbers, e.g., 1e9+9, 998244353, 469762049 
  ```
* ### INT INF  &nbsp; `"intinf"`
  Define a constant value for representing infinity for integer values within program context.
  
  ```c++
  const int INF = INT_MAX;
  ```
* ### LONG LONG INF  &nbsp; `"llinf"`
  Define a constant value for representing infinity for long integer values within program context.
  
  ```c++
  const long long INF = LLONG_MAX;
  ```
