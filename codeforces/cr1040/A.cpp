#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;


// actually, the solution is that we need the mex() function only for zeros, because for the sequences that aren't {0, 1} the value of mex() less than the value of sum(). And for the sequance {0, 1} in reality it is mex({0}) + sum({1}). So the answer in all cases is the number of zeros add sum(S)

void solve() {
    int n = 0, ans = 0, tmp = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        ans += tmp + (tmp==0);
    }

    cout << ans << NL;
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0;
    cin >> t;
    while(t--) solve();
}
