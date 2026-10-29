#include <bits/stdc++.h>

#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define pb push_back
typedef long long ll;
using namespace std;


int main()
{
    int t = 1, max = 0, cnt = 0;
    while(t) {
        cin >> t;
        if (t>max) {
            max = t;
            cnt = 1;
        } else if (t == max)
            cnt++;
    }

    cout << cnt << NL;
}
