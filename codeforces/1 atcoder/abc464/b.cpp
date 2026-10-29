#include <bits/stdc++.h>

#define NL "\n"
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define INF 100000007
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int H = 0, W = 0;
    cin >> H >> W;
    vector<vector<char>> screen(H);
    char symb;

    for (int h = 0; h < H; ++h) {
        for (int w = 0; w < W; ++w) {
            cin >> symb;
            screen[h].pb(symb);
        }
    }

    // we just need to get the most left #, the most right #, the most top # and the most bottom #

    int top_h = -1, left_w = -1, right_w = -1, bottom_h = -1;

    for (int h = 0; h < H; ++h) {
        for (int w = 0; w < W; ++w) {
            if (screen[h][w] == '#') {
                if (top_h == -1)
                    top_h = h;
                if (left_w == -1 || w < left_w)
                    left_w = w;
                if (h > bottom_h)
                    bottom_h = h;
                if (w > right_w)
                    right_w = w;
            }
        }
    }

    #ifdef DEB
    cout << "---" << NL;
    cout << "Height: " << top_h << " " << bottom_h << NL;
    cout << "Width: " << left_w << " " << right_w << NL;
    #endif

    for (int i = top_h; i <= bottom_h; ++i) {
        for (int j = left_w; j <= right_w; ++j) {
            cout << screen[i][j];
        }
        cout << NL;
    }
    cout << NL;

}
