#include <bits/stdc++.h>

#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define INF 100000007
#define pb push_back
typedef long long ll;
using namespace std;

int main()
{
    int N = 0, streak = 1, streak_max = 0, streak_num = 0, a = 0, b = 0;
    cin >> N;
    // сначала значение элемента, а потом длину цепочки

    for (int i = 0; i < N; ++i) {
        cin >> b;
        if (b == a) {
            ++streak;
        }
        if (streak > streak_max) {
            streak_max = streak;
            if (i == 0) {
                streak_num = b;
            } else {
                streak_num = a;
            }
        }

        if (b != a) {
            streak = 1;
        }

        a = b;
    }

    streak_max = max(streak_max, 1);

    cout << streak_num << " " << streak_max << NL;

}
