#include <bits/stdc++.h>
#include <unordered_set>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
    string s = "";
    cin >> s;
    int len = s.length();
    int res = 0;
    int left = 0; // a pointer
    unordered_set<char> window;

    for (int right = 0; right < len; ++right) {
        while (window.count(s[right])) {
            window.erase(s[left]);
            ++left;
        }

        window.insert(s[right]);
        res = max(res, right - left + 1); // a very nice approach to find the max in a cycle
    }

    cout << res << NL;
}
