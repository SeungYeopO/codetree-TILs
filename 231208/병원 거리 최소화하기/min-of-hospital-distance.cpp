#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int map[51][51];
struct pos {
	int y;
	int x;
};
vector<pos>hospital;
vector<pos>location;

int ans = 100001;

int dist_calc(int y, int x) {
	int dist = 10001;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 2) {
				dist = min(abs(i - y) + abs(j - x), dist);
			}
		}
	}
	return dist;
}

int calc() {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {
				sum += dist_calc(i, j);
			}
		}
	}

	return sum;
}

void dfs(int idx) {

	if (location.size() == m) {
		for (int i = 0; i < location.size(); i++) {
			map[location[i].y][location[i].x] = 2;
		}
		calc();
		ans = min(calc(), ans);
		
		for (int i = 0; i < location.size(); i++) {
			map[location[i].y][location[i].x] = 0;
		}

		return;
	}
	for (int i = idx; i < hospital.size(); i++) {
		pos point;
		point.y = hospital[i].y;
		point.x = hospital[i].x;
		location.push_back(point);
		dfs(i + 1);
		location.pop_back();
	}

	return;
}

int main() {
	// 여기에 코드를 작성해주세요.

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				pos point;
				point.y = i;
				point.x = j;
				hospital.push_back(point);
				map[i][j] = 0;
			}
		}
	}

	dfs(0);

	cout << ans;

	return 0;
}