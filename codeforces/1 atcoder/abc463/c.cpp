#include <algorithm>
#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N = 0, Q = 0;
    //vector<pair<int, int>> people; — using two different vectors is 1) faster, 2) more convenient
    //vector<double> times; — why the fuck?

    cin >> N;
    vector<ll> L(N), H(N); // L is length (i think) and H is time (somehow.. hours maybe)
    for (ll i = 0; i < N; ++i)
        cin >> H[i] >> L[i];


    // sort(people.begin(), people.end(), compare); IT IS ALREADY SORTED BY TIME

    /*cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> time;
        //times.push_back(time); // instead of +0.5 we'll just compare with > (not >=)
        for (int j = 0; j < N; ++j) {
            if (people[j].second > time) {
                cout << people[j].first << NL;
                break;
            }
        } they're just a meh lines of code

    }*/


    //see suffix_max.cpp to get the idea
    vector<ll> suffix_max(N+1, 0);
    for (ll i = N-1; i >= 0; --i) {
        suffix_max[i] = max(suffix_max[i+1], H[i]);
    }

    ll time = 0;
    cin >> Q;
    while (Q--) { // super convenient loop, i need to get used to it
        cin >> time;

        ll pos = upper_bound(L.begin(), L.end(), time) - L.begin(); // because L is sorted already, we just find some x > time
        cout << suffix_max[pos] << NL; // the largest height for this time
    }
}
