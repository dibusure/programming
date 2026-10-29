#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve()
{
    int n = 0, a = 0, b = 0, tmp = 0;
    cin >> n >> a;
    vector<int> v;
    for (int i = 0; i < n; ++i)
    {
        cin >> tmp;
        v.push_back(tmp);
    }

    if (n % 2 == 0)
    {
        b = v[n / 2 - 1];
    }
    else
    {
        b = v[(n + 1) / 2 - 1];
    }

    int a_n = 0, b_n = 0;
    bool toright = false;

    for (int it = 1; a_n > b_n || a_n == 0; ++it)
    {
        a_n = 0;
        b_n = 0;
        for (int i = 0; i < n; ++i)
        {
            if (abs(a - v[i]) <= abs(b - v[i]))
            {
                a_n++;
            }
            else
            {
                b_n++;
            }
        }

        cout << b << ": " << a_n << " vs " << b_n << " -- nope" << NL;

        if (a_n >= b_n)
        {
            if (!toright)
            {
                if (b > 0)
                {
                    --b;
                }
                else
                {
                    toright = true;
                    if (n % 2 == 0)
                    {
                        b = v[n / 2 - 1];
                    }
                    else
                    {
                        b = v[(n + 1) / 2 - 1];
                    }
                }
            }
            else
            {
                if (b < n)
                {
                    b++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    cout << b << NL;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0;
    cin >> t;
    while (t--)
        solve();
}