#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    vector<int> vec;
    int tmp = 0;
    while (cin >> tmp) {
        vec.push_back(tmp);
    }

    int streak = 0, max_streak = 0, size = vec.size();
    bool deleted = false;
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] == vec[i-1] && vec[i] == 1) {
            ++streak;
        } else if (deleted == false && vec[i] == 0 && i != vec.size() - 1 && i != 0 && vec[i+1] == 1 && vec[i-1] == 1) {
            vec.erase(vec.begin() + i, vec.begin() + i + 1);
            deleted = true;
            cout << "delete " << i << NL;
            --i;
        }

        if (streak > max_streak)
            max_streak = streak;
    }

    if (size == vec.size() && find(vec.begin(), vec.end(), 0) == vec.end()) {
        cout << max_streak-1 << NL;
    } else {
        cout << max_streak << NL;
    }
}
