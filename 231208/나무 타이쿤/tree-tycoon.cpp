#include <iostream>
#include <vector>
using namespace std;

int n, m;
int map[16][16];
int tmp[16][16];
struct position {
	int y;
	int x;
};
struct info {
	int dir;
	int move;
};
vector<info>nutrition;
vector<position>pos;
vector<position>tmp_pos;
int dy[9] = { 0, 0, -1,-1,-1, 0, 1, 1, 1 };
int dx[9] = { 0, 1, 1, 0, -1,-1,-1, 0, 1 };

void base_set() {
	position loc;

	loc.y = n - 1;
	loc.x = 0;
	pos.push_back(loc);
	
	loc.y = n - 1;
	loc.x = 1;
	pos.push_back(loc);

	loc.y = n - 2;
	loc.x = 0;
	pos.push_back(loc);

	loc.y = n - 2;
	loc.x = 1;
	pos.push_back(loc);
}

void growth() {
	for (int i = 0; i < pos.size(); i++) {
		map[pos[i].y][pos[i].x] += 1;
	}
	for (int i = 0; i < pos.size(); i++) {
		int cnt = 0;

		int left_up = 0;
		int right_up = 0;
		int left_down = 0;
		int right_down = 0;

		if (pos[i].y - 1 >= 0 && pos[i].x - 1 >= 0) {
			left_up = map[pos[i].y - 1][pos[i].x - 1];
		}
		if (pos[i].y - 1 >= 0 && pos[i].x + 1 < n) {
			right_up = map[pos[i].y - 1][pos[i].x + 1];
		}
		if (pos[i].y + 1 < n && pos[i].x - 1 >= 0) {
			left_down = map[pos[i].y + 1][pos[i].x - 1];
		}
		if (pos[i].y + 1 < n && pos[i].x + 1 < n) {
			right_down = map[pos[i].y + 1][pos[i].x + 1];
		}

		if (left_up >= 1)
			cnt++;
		if (right_up >= 1)
			cnt++;
		if (left_down >= 1)
			cnt++;
		if (right_down >= 1)
			cnt++;

		tmp[pos[i].y][pos[i].x] = map[pos[i].y][pos[i].x] + cnt;
	}

	for (int i = 0; i < pos.size(); i++) {
		map[pos[i].y][pos[i].x] = tmp[pos[i].y][pos[i].x];
		tmp[pos[i].y][pos[i].x] = 0;
	}
}

bool nutri_check(int y, int x) {
	for (int i = 0; i < tmp_pos.size(); i++) {
		if (y == tmp_pos[i].y&&x == tmp_pos[i].x)
			return true;
	}
	return false;
}

void batch() {
	for (int i = 0; i < pos.size(); i++) {
		position tmp;
		tmp.y = pos[i].y;
		tmp.x = pos[i].x;
		tmp_pos.push_back(tmp);
	}
	pos.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (nutri_check(i, j)) continue;
			if (map[i][j] >= 2) {
				map[i][j] -= 2;

				position next_pos;
				next_pos.y = i;
				next_pos.x = j;
				pos.push_back(next_pos);

			}
		}
	}
	tmp_pos.clear();
}

void func() {
	for (int i = 0; i < nutrition.size(); i++) {
		for (int j = 0; j < pos.size(); j++) {
			int next_y = nutrition[i].move * dy[nutrition[i].dir];
			int next_x = nutrition[i].move * dx[nutrition[i].dir];

			// 혹시 칸을 벗어나는 경우를 생각해야함. 일어나서 계속해야지...
			if (pos[j].y + next_y >= n) {
				pos[j].y = (pos[j].y + next_y) - n;
			}
			else if (pos[j].y + next_y < 0) {
				pos[j].y = n + (pos[j].y + next_y);
			}
			else {
				pos[j].y += next_y;
			}

			if (pos[j].x + next_x >= n) {
				pos[j].x = (pos[j].x + next_x) - n;
			}
			else if (pos[j].x + next_x < 0) {
				pos[j].x = n + (pos[j].x + next_x);
			}
			else {
				pos[j].x += next_x;
			}
		}
		growth();
		batch();
	}
}

int main() {
	// 여기에 코드를 작성해주세요.
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	base_set();

	int d, p;
	for (int i = 0; i < m; i++) {
		cin >> d >> p;
		info tmp;
		tmp.dir = d;
		tmp.move = p;
		nutrition.push_back(tmp);
	}

	func();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans += map[i][j];
		}
	}

	cout << ans;
	return 0;
}