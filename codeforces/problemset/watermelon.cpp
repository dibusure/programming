#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int w = 0;
    cin >> w;
    if (w % 2 == 0 && w > 2) {
        cout << "YES" << NL;
    } else {
        cout << "NO" << NL;
    }
}
