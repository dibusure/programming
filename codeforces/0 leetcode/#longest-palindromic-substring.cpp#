#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
    string s = "";
    cin >> s;
    int left = 0, right = s.length()-1; // pointers
    int len = 0, res = 0;

    while (right >= left) {
        while (s[right] == s[left] && right != left) {
            --right;
            ++left;
            len+=2;
        }

        if (right-left > 2) {
            len = 0; // there isn't any palindromes
        } else {
            if (right - left == 2 || right - left == 0)
                ++len; // palindrome is like "aba"
            res = max(len, res);
        }

        left++;
    }

    cout << res << NL;
}
