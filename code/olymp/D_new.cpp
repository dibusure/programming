#include <bits/stdc++.h>

#define NL "\n"
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int amount_of_unique_cards = 9;

    int n = 0; cin >> n;
    vector<string> a(n);

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // Ближайшее вхождение каждого типа карты
    vector<int> next_pos(amount_of_unique_cards, n);

    // Позиция, на которой соберутся все 9 карт
    vector<int> finish(n);

    for (int i = n - 1; i >= 0; --i) {
        int id = (a[i][0] - 'a') * 3 + (a[i][1] - '1');

        next_pos[id] = i;

        finish[i] = *max_element(
            next_pos.begin(), next_pos.end()
        );
    }

    int t = 0; cin >> t;
    int l = 0, r = 0;

    for (int i = 0; i < t; ++i) {
        cin >> l >> r;
        --l;
        --r;

        if (finish[l] > r) {
            cout << -1 << NL;
        } else {
            cout << finish[l] - l + 1 << NL;
        }
    }
}
