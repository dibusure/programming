#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    char first_char = ' ', second_char = ' ';
    int counter = 0, max_counter = -1;

    while (cin >> second_char) {
        if (second_char == first_char) {
            ++counter;
        } else {
            counter = 0;
        }

        if (counter > max_counter)
            max_counter = counter;
        first_char = second_char;
    }

    cout << max_counter+1 << NL;
}
