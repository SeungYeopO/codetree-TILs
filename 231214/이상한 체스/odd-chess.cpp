#include <iostream>
#include <vector>
#include <climits>
#include <tuple>
#include <algorithm>

#define MAX_N 8
#define MAX_M 8
#define CHESS_TYPE_NUM 5
#define DIR_NUM 4

using namespace std;

int n, m;
int min_area = INT_MAX;
vector<pair<int, int> > chess_pieces;
int board[MAX_N][MAX_M];

// 말들의 방향을 표시합니다.
int piece_dir[MAX_N][MAX_M];

// 자신의 말로 갈 수 있는 영역을 표시합니다.
bool visited[MAX_N][MAX_M];

// 입력으로 주어진 방향에 대해
// 말의 종류마다 북동남서 방향으로
// 이동이 가능한지 표시합니다.
bool can_move[CHESS_TYPE_NUM + 1][DIR_NUM] = {
    {},
    {1, 0, 0, 0},
    {0, 1, 0, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 1},
    {1, 1, 1, 1}
};

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

// 움직일 수 있는 곳인지 여부를 확인합니다.
bool CanGo(int x, int y) {
    return InRange(x, y) && board[x][y] != 6;
}

// (start_x, start_y)에서 해당 타입의 말이 특정 방향을 
// 바라보고 있을 때 갈 수 있는 곳들을 전부 표시합니다.
void Fill(int start_x, int start_y, int piece_num, int face_dir) {
    // 북동남서 순으로 방향을 설정합니다.
    int dx[DIR_NUM] = {-1, 0, 1, 0};
    int dy[DIR_NUM] = {0, 1, 0, -1};
    
    for(int i = 0; i < 4; i++) {
        // 해당 말이 움직일 수 있는 방향인지를 확인합니다.
        // 움직일 수 없다면 pass합니다.
        if(!can_move[piece_num][i])
            continue;
        
        // 갈 수 있다면, 끝날때까지 계속 진행합니다.
        // 방향은 face_dir만큼 시계방향으로 
        // 회전했을 때를 기준으로 움직입니다.
        int x = start_x, y = start_y;
        int move_dir = (i + face_dir) % 4;
        while(true) {
            visited[x][y] = true;
            int nx = x + dx[move_dir], ny = y + dy[move_dir];
            if(CanGo(nx, ny)) {
                x = nx; y = ny;
            }
            else
                break;
        }
    }
}

// n 개의 체스 말의 방향이 정해졌을 때 이동할 수 없는 영역의 넓이를 반환합니다.
int GetArea() {
    // visited 배열을 초기화합니다.
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            visited[i][j] = 0;

    for(int i = 0; i < (int) chess_pieces.size(); i++) {
        int x, y;
        tie(x, y) = chess_pieces[i];
        
        // 해당 말이 정해진 방향에 있을 때 갈 수 있는 곳들을 전부 표시합니다.
        Fill(x, y, board[x][y], piece_dir[x][y]);
    }
    
    int area = 0;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(visited[i][j] == 0 && board[i][j] != 6)
                area++;

    return area;
}

void SearchMinArea(int cnt) {
    // 자신의 말들의 방향이 전부 결정되었을 때, 갈 수 없는 넓이를 계산하여 갱신합니다.
    if(cnt == (int) chess_pieces.size())  {
        min_area = min(min_area, GetArea());
        return;
    }

    // cnt 말의 방향을 설정합니다. 
    int piece_x, piece_y;
    tie(piece_x, piece_y) = chess_pieces[cnt];
    
    for(int i = 0; i < 4; i++) {
        piece_dir[piece_x][piece_y] = i;
        SearchMinArea(cnt + 1);
    }
}

int main() {
    cin >> n >> m;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
            if(1 <= board[i][j] && board[i][j] <= 5)
                chess_pieces.push_back(make_pair(i, j));
        }

    SearchMinArea(0);
    cout << min_area;
    
    return 0;
}