#include <bits/stdc++.h>
#include <vector>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	/* actually, this problem looks like n*n table, i wonder how to write this table in cpp..
	 * i could use map...*/

	ll N = 0, K = 0;
	ll t = 0;
	cin >> N;
	//vector<set<ll>> restable(N+1); // set isn't necessary — it's already sorted
	vector<vector<ll>> restable(N+1);

	for (ll i = 1; i <= N; ++i) {
	    cin >> K;
		for (ll j = 1; j <= K; ++j) {
		    cin >> t;
			//cout << i << " gifts " << t << NL;
			restable[t].push_back(i);
		}
	}

	ll size = 0;
	for (ll i = 1; i <= N; ++i) {
	    size = restable[i].size();
		cout << size << " ";
		if (size > 0) {
		    for (auto x : restable[i])
				cout << x << " ";
		}
		cout << NL;
	}

}
