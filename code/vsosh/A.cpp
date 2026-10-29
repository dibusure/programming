#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    ll n = 0, a = 0, b = 0;
    cin >> n >> a >> b;
    if (a==b) {
        if (n%2==0) {
            cout << n/2 << NL;
        } else {
            cout << "-1" << NL;
        }
    } else {
        if ((n*b)%(a+b) == 0) {
            cout << (n*b)/(a+b) << NL;
        } else {
            cout << "-1" << NL;
        }
    }
}
