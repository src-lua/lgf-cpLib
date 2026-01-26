// Time Complexity: O(log(n))
    int binarySearch(int l, int r, vector<int>& arr, int target) {
        int answ;
        while (l <= r) {
            int m = l + (r - l) / 2;
    
            // If NOT SOLVE, ignore left half
            if (! (arr[m] > target) )
                l = m + 1;
    
            // If SOLVE, ignore right half
            else {
                r = m - 1;
                answ = m;
            }
        }
    
        return answ;
    }