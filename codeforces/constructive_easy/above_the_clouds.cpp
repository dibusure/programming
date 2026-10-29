#include <bits/stdc++.h> // string is here too

#define NL "\n";
typedef long long ll;

using namespace std;

bool ans(string s) {
    ll n = s.size();
    string a = "", b = "", c = "";

    for (ll i = 0; i < n-2; ++i) {
        a = s.substr(0, i+1);

        for (ll j = n-1; j > i+1; --j) {
            c = s.substr(j, n-j);
            b = s.substr(i+1, j-i-1);

            #ifdef TEST
            cout << a << " " << b << " " << c << NL;
            #endif


            if ((a+c).contains(b) && !b.empty() && a+b+c == s) {
                #ifdef TEST
                cout << endl;
                cout << a << " " << b << " " << c << NL;
                cout << 0 << "-" << i << "; " << i+1 << "-" << j-1 << "; " << j << "-" << n-1 << ";" << NL;
                #endif
                return true;
            }
        }
    }

    return false;

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    string s = " ";
    ll t = 0, n = 0;
    cin >> t;
    
    for (ll i = 0; i < t; ++i) {
        cin >> n >> s;
        if (ans(s)) {
            cout << "yes" << NL;
            #ifdef TEST
            cout << endl;
            #endif
        } else {
            cout << "no" << NL;
            #ifdef TEST
            cout << endl;
            #endif
        }
    }
}
