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

    int n = 0;
    cin >> n;

    // если n = 3, то можно сразу все 3 и вывести
    // если n != 3
    //   если есть 2 отрицательных числа, то можно отсортировать массив и взять условно A[0] * A[1] * A[n-1] и сравнить с A[n-1] * A[n-2] * A[n-3] — притом длина массива (n) нам реально не важна

    if (n==3) {
        int t = 0;
        for (int i = 0; i < 3; ++i) {
            cin >> t;
            cout << t << " ";
        }
        cout << NL;
   } else {
        vector<int> A(n);
        for (int i = 0; i < n; ++i)
            cin >> A[i];
        sort(all(A));

        int back = A[0] * A[1] * A[2],
            front = A[n-1] * A[n-2] * A[n-3],
            mid = A[0] * A[1] * A[n-1];

        // первые 2 случая сосут при -2 -1 0 1, потому что потому
        if (mid > front && mid > back) {
            cout << A[0] << " " << A[1] << " " << A[n-1] << NL;
        } else if (front > back) {
            cout << A[n-1] << " " << A[n-2] << " " << A[n-3] << NL;
        } else {
            cout << A[0] << " " << A[1] << " " << A[2] << NL;
        }
   }
}
