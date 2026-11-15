#include <bits/stdc++.h>
#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define INF 100000007
#define pb push_back
using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.second < b.second) {
        return true;
    } else {
        return false;
    }
}

bool cond(pair<int, int> sector, int point) {
    if (sector.first <= point && sector.second >= point) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int n = 0;
    cin >> n;
    vector<pair<int, int>> sect(n);
    for (int i = 0; i < n; ++i) {
        cin >> sect[i].first;
        cin >> sect[i].second;
    }

    sort(sect.begin(), sect.end(), comp);

    vector<int> dots;
    dots.pb(sect[0].second);
    // хочу пройтись по всем отрезкам, посмотреть, есть ли в них первая точка
    // если есть, забиваем
    // если нет, надо делать новую точку в конце первого отрезка, который эту точку не содержит
    for (int i = 0; i < n; ++i) {
        int is_dot = 0; 
        for (int j = 0; j < dots.size(); ++j)
            is_dot += cond(sect[i], dots[j]);

        if (is_dot == 0)
            dots.pb(sect[i].second);
    }

    cout << dots.size() << '\n';
    for (int i = 0; i < dots.size(); ++i)
        cout << dots[i] << " ";
    cout << '\n';

}
