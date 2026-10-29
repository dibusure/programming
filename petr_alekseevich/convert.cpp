#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    string word;
    cin >> word;

    for (int i = word.length(); i >= 0; --i) {
        cout << hex << (int)word[i];
    }

    cout << NL;
}
