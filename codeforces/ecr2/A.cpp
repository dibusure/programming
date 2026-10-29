#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

#define NL "\n";
typedef long long ll;

using namespace std;

bool ans(int a, int x, int y) {
    for (int b = 1; b <= max(x,y); ++b) {
        if (abs(y-b) < abs(y-a) && abs(x-b) < abs(x-a)) {
            return true;
        }
    }
    return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0, a = 0, x = 0, y = 0;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        cin >> a >> x >> y;
        if (ans(a,x,y)) {
            cout << "YES" << NL;
        } else {
            cout << "NO" << NL;
        }
    }
}

