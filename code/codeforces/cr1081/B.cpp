#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0;
    cin >> n;
    string a(n, '0');
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int counter = 0, cunt_max = 0;    
    for (int i = 0; i <= n/2; i++) {
        rotate(a.begin(), a.begin()+i, a.end());
        
        for (int j = 0; j-1 < n; j++) {
            if (a[j] == a[j+1])
                counter++;
        }

        if (counter > cunt_max)
            cunt_max = counter;
        counter = 0;
    }

    cout << cunt_max << NL;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 0; cin >> t;
	while (t--) solve();
}