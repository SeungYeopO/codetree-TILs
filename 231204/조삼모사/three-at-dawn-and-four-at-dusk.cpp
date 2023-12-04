#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, arr[21][21];
int visited[21];
vector<int> tmp;
vector<int> tmp2;
vector<int>fin;
vector<int>fin2;

int morning = 0;
int night = 0;
int ans = 101;

void calc(int cnt) {
	if (fin.size() == 2) {
		morning += arr[fin[0]][fin[1]];
		return;
	}
	for (int i = 0; i < tmp.size(); i++) {
		fin.push_back(tmp[i]);
		calc(cnt + 1);
		fin.pop_back();
	}
}

void calc2(int cnt) {
	if (fin2.size() == 2) {
		night += arr[fin2[0]][fin2[1]];
		return;
	}
	for (int i = 0; i < tmp2.size(); i++) {
		fin2.push_back(tmp2[i]);
		calc2(cnt + 1);
		fin2.pop_back();
	}
}

void dfs(int index) {
	if (tmp.size() == n / 2) {
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				tmp2.push_back(i);
			}
		}
		
		/*cout << "tmp1: ";
		for (int i = 0; i < tmp.size(); i++) {
			cout << tmp[i] << " ";
		}
		cout << endl << "tmp2: ";
		for (int i = 0; i < tmp2.size(); i++) {
			cout << tmp2[i] << " ";
		}
		
		cout << endl;*/
		calc(0);	// 아침에 하는 일의 총양
		calc2(0);	// 저녁에 하는 일의 총양
		
		ans = min(ans, abs(morning - night));
		morning = 0;
		night = 0;
		tmp2.clear();
		return;
	}
	for (int i = index; i < n; i++) {
		if (visited[i] == 1) {
			continue;
		}
		visited[i] = 1;
		tmp.push_back(i);
		dfs(i + 1);
		tmp.pop_back();
		visited[i] = 0;
	}

}
int main() {
	// 여기에 코드를 작성해주세요.
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
		
	}

	dfs(0);

	cout << ans << endl;
	return 0;
}