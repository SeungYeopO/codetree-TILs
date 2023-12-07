#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, L, R;
int visited[51][51];
int arr[51][51];
int tmp[51][51];
int dy[4] = {-1, 0, 1 ,0};
int dx[4] = {0, 1, 0, -1};
int tmp_y = 0, tmp_x = 0;
int sum = 0;
vector<pair<int, int>> vec;
bool link_flag = 0;
pair<int, int>next_pair;
int cnt = 0;

bool check_egg() {
	bool egg_flag = false;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			for (int i = 0; i < 4; i++) {
				int next_y = y + dy[i];
				int next_x = x + dx[i];

				if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= n) continue;

				int dif = abs(arr[y][x] - arr[next_y][next_x]);
				if (dif <= R && dif >= L) {
					egg_flag = true;
				}
			}
		}
	}
	return egg_flag;
}

bool pair_find(int y, int x) {
	bool exist_flag = 0;

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].first == y && vec[i].second == x) {
			exist_flag = 1;
		}
	}

	return exist_flag;
}


void func(int y, int x) {

	if (visited[y][x] == 1) {
		return;
	}

	visited[y][x] = 1;

	if (pair_find(y, x) == false) {
		vec.push_back({ y, x });
		sum += arr[y][x];
	}

	for (int i = 0; i < 4; i++) {
		int next_y = y + dy[i];
		int next_x = x + dx[i];

		if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= n) continue;

		int dif = abs(arr[y][x] - arr[next_y][next_x]);
		if (dif <= R && dif >= L) {
			if (pair_find(next_y, next_x) == false) {
				vec.push_back({ next_y,next_x });
				sum += arr[next_y][next_x];

				link_flag = 1;
				/*tmp_y = next_y;
				tmp_x = next_x;*/
			}
			else {
				link_flag = 0;
			}
		}
	}

	if (link_flag == 0) {
		for (int i = 0; i < vec.size(); i++) {
			tmp[vec[i].first][vec[i].second] = sum / vec.size();
		}
		vec.clear();
		sum = 0;
	}
}

void print_tmp() {
	/*cout << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << tmp[i][j] << " ";
		}
		cout << endl;
	}*/

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = tmp[i][j];
		}
	}
}
int main() {
	// 여기에 코드를 작성해주세요.
	cin >> n >> L >> R;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	while(check_egg()) {
		cnt++;

		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				if (visited[y][x] == 1) continue;
				if (link_flag == 1) {
					for (int i = 0; i < vec.size(); i++) {
						func(vec[i].first, vec[i].second);
					}
				}
				func(y, x);
			}
		}

		print_tmp();
	}
	
	cout << cnt;

	return 0;
}