#include <algorithm>
#include <bits/stdc++.h>

#define NL "\n"
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define INF 100000007
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N = 0, M = 0;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> B(M);
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    for (int i = 0; i < M; ++i)
        cin >> B[i];

    // B must be at most twice A (B<=2A)
    //
    // 4 2 1 8
    // 14 9 3 2 9
    //
    // 1 2 4 8
    // 2 3 9 9 14

    int cunt = 0;

    sort(all(B));
    sort(all(A));

    for (int i = 0; i < N; ++i) {
        auto bound = lower_bound(all(B), 2*A[i]);
        if (lower_bound != B.end()) {
            // lower_bound возвращает итератор на первое значение, не меньшее x => как раз B<=2A, потом надо будет проверить, что этот баунд >= A
            // но я бы вообще проверил upper_bound от A[i], потому что это оптимальная штука
            #ifdef DEB
            cout << A[i] << " with " << *bound << NL;
            #endif
            B.erase(bound); // i need to fix this, because we don't wanna sort B every time
            // here is n^2
            ++cunt;
        }
    }

    cout << cunt << NL;
}
