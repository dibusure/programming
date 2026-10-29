#include <bits/stdc++.h>
#include <math.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    ll n = 0;
    cin >> n;
    
    ll fives = 0;
    // obviously we need 5*2, but we say that there are enough twos to satisfy all of the fives => count only fives
    for (int i = 5; i <= n; i *= 5)
        fives += n/i; 

    cout << fives << NL;
}

