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
    int N = 0, M = 0;
    cin >> N >> M;
    vector<int> f_colors (N);
    vector<int> days(N);
    vector<int> s_colors (N);

    for (int i = 0; i < N; ++i)
        cin >> f_colors[i] >> days[i] >> s_colors[i];

    vector<int> colors_count(N+1,0); // since there's N colors

    for (int i = 0; i < N; ++i)
        colors_count[f_colors[i]] += 1;

    int unique_c = 0;

    for (int d = 1; d <= M; ++d) { // days counter
        for (int i = 0; i < N; ++i) {
            if (days[i] == d) {
                colors_count[f_colors[i]] -= 1;
                colors_count[s_colors[i]] += 1;
            }
        }

        // count unique
        for (int i = 1; i <= N; ++i) {
            if (colors_count[i] > 0)
                ++unique_c;
        }

        cout << unique_c << NL;
        unique_c = 0;
    }

}
