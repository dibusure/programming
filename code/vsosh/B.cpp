#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int dsum(vector<int> a) {
    int sum = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (i % 2 == 0) {
            sum += a[i];
        } else {
            sum -= a[i];
        }
    }

    return sum;
}

void solve() {
	ll n = 0, sum = 0;
    cin >> n;
    vector<int> a;
    for (ll i = 1; n%int(pow(10,i)) > 0; i++) {
        a.push_back((n%int(pow(10,i)))/int(pow(10,i-1)));
        n -= n%int(pow(10,i));
    }

    reverse(a.begin(), a.end());

    int csum = dsum(a);
    int summ = csum;

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            summ = csum;
            if (i % 2 == 0) {
                summ -= 2*a[i];
            } else {
                summ += 2*a[i];
            }
            if (j!=i) {
                if (j % 2 == 0) {
                    summ -= 2*a[j];
                } else {
                    summ += 2*a[j];
                }
                if (summ % 11 == 0) {
                    cout << "yes" << NL;
                    return;
                }
            }
        }
    }

    cout << "no" << NL;
    return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0;
    cin >> t;
	cin >> t;
	while (t--) solve();
}

