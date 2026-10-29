#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

//https://cp-algorithms.com/sequences/mex.html
// O(N*logN)
int mex(vector<int> const& A) {
    set<int> b(A.begin(), A.end());

    int result = 0;
    while (b.count(result))
        ++result;
    return result;
}

bool check(vector<int> &a) { // a.size() is certainly 3
    int max = max_element(a.begin(), a.end());
    int min = min_element(a.begin(), a.end());

    for (int i = 0; i < a.size(); ++i)


    if (mex == max-min)
        return true;
    return false;
}

void ans() {
    int n, unk = 0; // unk - *unk*nown (-1) elements counter
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == -1)
            ++unk;
    }
    
    if (unk == n) {
        cout << "yes" << NL;
        return;
    }

    
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    int t = 0;
    cin >> t;
    while (t--) ans();
}
