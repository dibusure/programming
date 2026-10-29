#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0, n = 0, five = 0;
    cin >> t;
    string call = "";
    while (t--) {
        cin >> call;
        for (int i = 0; i < call.size(); ++i) {
            n = int(call[i]) - 96;
            five = n/5;
            if (five > 4) {

            } else {
                if (n % 5 <= 2) {
                    n = (five+1)/2;
                    cout << n;
                } else {
                    n = (five+1)/2 + 1;
                    cout << n;
                }
            }
        }
        cout << NL;
    }
    
}
