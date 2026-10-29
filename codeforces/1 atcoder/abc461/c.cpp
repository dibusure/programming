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

    ll N = 0, K = 0, M = 0;
    cin >> N >> K >> M; // choose K gems from N so they have AT LEAST M distinct colors (so there could be more than M!!!)
    vector<vector<ll>>gems(N+1);

    ll color = 0, value = 0;

    for (ll i = 0; i < N; ++i) {
        cin >> color >> value;
        gems[color].pb(value);
    }

    vector<ll> best;
    vector<ll> others;

    for (int i = 1; i <= N; ++i) {
        if (gems[i].empty()) continue; // continue means skip, wow

        sort(gems[i].rbegin(), gems[i].rend());
        best.pb(gems[i][0]);

        for (ll j = 1; j < gems[i].size(); ++j)
            others.pb(gems[i][j]);
    }

    sort(best.rbegin(), best.rend());
    sort(others.rbegin(), others.rend());

    ll sum = 0;

    for (ll i = 0; i < M; ++i)
        sum += best[i];

    K -= M;

    if (best.size() > M) {
        for (ll i = M; i < best.size(); ++i)
            others.pb(best[i]);
    }

    sort(others.rbegin(), others.rend());

    if (K > 0) {
        for (int i = 0; i < K; ++i)
            sum += others[i];
    }

    cout << sum << NL;
}
