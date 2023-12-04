#include <iostream>
#include <algorithm>

using namespace std;

int n;
int arr[12];
int oper[3];
int min_result = 1000001;
int max_result = -1000001;

int calc(int num1, int num2, int idx) {
	if (idx == 0) return num1 + num2;
	else if (idx == 1) return num1 - num2;
	else if (idx == 2) return num1 * num2;
}

void dfs(int level, int sum) {
	if (level == n - 1) {
		min_result = min(min_result, sum);
		max_result = max(max_result, sum);
		return;
	}

	for (int i = 0; i < 3; i++) {
		if (oper[i] == 0) {
			continue;
		}
		oper[i] -= 1;
		dfs(level + 1, calc(sum, arr[level + 1], i));
		oper[i] += 1;
	}
}
int main() {
	// 여기에 코드를 작성해주세요.
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < 3; i++) {
		cin >> oper[i];
	}

	dfs(0, arr[0]);

	cout << min_result << " " << max_result;
	
	return 0;
}