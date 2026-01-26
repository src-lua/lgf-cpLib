    #include <bits/stdc++.h>

#define ll long long

using namespace std;

struct item {
    int weight;
      ll value;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int item_count, capacity;

    cin >> item_count >> capacity;
    ll table[++item_count][++capacity];

    int weight;
     ll  value;

    vector<item> items = {{0,0}};

    for (int i = 1; i < item_count; i++) { // reading the items
        cin >> weight >> value;

        items.push_back({weight, value});
    }

    for (int i = 0; i < item_count;i++) { // setting the capacity 0 to 0 value;
        table[i][0] = 0;
    }
    for (int j = 0; j < capacity; j++) { // setting the item 0 to 0 value;
        table[0][j] = 0;
    }

    for (int i = 1; i < item_count; i++) { // populating the table;
        for (int j = 1; j < capacity; j++) {
            int w = items[i].weight;
             ll v = items[i].value;
            
            table[i][j] = table[i-1][j];
            if (w <= j) table[i][j] = max(table[i][j], v + table[i-1][j-w]);
        }
    }

    vector<int> chosen_itens; // retrieving the chosen itens in the optimal solution
    int c = capacity - 1;
    for (int i = item_count - 1; i > 0; i--) {
        if (table[i][c] != table[i-1][c]) {
            chosen_itens.push_back(i);
            c -= items[i].weight;
        }
    }

    for (int i = 0; i < item_count; i++) { // printing the table for debug
        cout << '\n';
        for (int j = 0; j < capacity; j++) {
            cout << table[i][j] << ' ';
        }
    }
    cout << '\n';

    cout << table[--item_count][--capacity] << '\n'; //print the max value;

    for (auto e: chosen_itens) cout << e << ' '; //print the chosen itens;

    return 0;
}