#include <iostream>
#include <algorithm>

using namespace std;

long long n;
long long cli[1000000];
long long leader, member;
long long ans = 0;

int main(void) {

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> cli[i];
	}

	cin >> leader >> member;


	for (int i = 0; i < n; i++) {
		cli[i] = cli[i] - leader;
		if (cli[i] > 0) {
			if (cli[i] > member) {
				ans += cli[i] / member;
				if (cli[i] % member != 0) {
					ans += 1;
				}
			}
			else {
				ans += 1;
			}
		}
		
	}

	ans += n;

	cout << ans;

	return 0;
}