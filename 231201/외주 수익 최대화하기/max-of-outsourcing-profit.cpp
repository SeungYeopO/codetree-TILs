#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int> > times;
vector<int> profits;

int max_profit;
vector<int> selected_jobs;

// 선택된 외주 작업에 대한 수익을 반환해줍니다.
int GetProfit() { 
    int profit = 0;
    for(int i = 0; i < (int) selected_jobs.size(); i++) 
        profit += profits[selected_jobs[i]];
    return profit;
}

// 수행하고자 하는 외주 작업들이 수행 가능한지 여부를 확인합니다.
bool IsAvailable() {
    // 이전 외주의 종료일이 그 다음 외주의 시작보다 늦은 경우 이는 불가능한 경우입니다.
    for(int i = 0; i < (int) selected_jobs.size() - 1; i++)
        if(times[selected_jobs[i]].second >= times[selected_jobs[i + 1]].first)
            return false;

    // 각 외주의 종료일이 휴가 기간을 초과하는 경우 이는 불가능한 경우입니다.
    for(int i = 0; i < (int) selected_jobs.size(); i++)
        if(times[selected_jobs[i]].second > n)
            return false;

    return true;
}

void FindMaxProfit(int curr_idx) {
    // 모든 외주 작업에 대해 다 탐색한 경우 스케쥴링이 가능한지를 확인한 뒤
    // 가능한 최대 수익을 갱신해줍니다.
    if(curr_idx == n) {
        if(IsAvailable())
            max_profit = max(max_profit, GetProfit());
        return;
    }

    // 해당 인덱스의 외주 작업을 수행하지 않았을 때의 경우를 탐색합니다.
    FindMaxProfit(curr_idx + 1);

    // 해당 인덱스의 외주 작업을 수행했을 때의 경우를 탐색합니다.
    selected_jobs.push_back(curr_idx);
    FindMaxProfit(curr_idx + 1);
    selected_jobs.pop_back();
}

int main() {
    cin >> n;

    // 첫번째 날부터 n번째 날까지 외주 정보를 입력받습니다.
    int time, profit;
    for(int i = 1; i <= n; i++) {
        cin >> time >> profit;
        // 외주 작업의 시간일과 종료일을 pair로 저장합니다.
        times.push_back(make_pair(i, i + time - 1));
        profits.push_back(profit);
    }

    FindMaxProfit(0); 
    cout << max_profit;

    return 0;
}