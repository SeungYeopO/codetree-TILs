#include <iostream>
using namespace std;

int N,M,P,C,D;
int rooy, roox;
int map[54][54];
int rdy[8]={-1,-1,0,1,1,1, 0, -1};
int rdx[8]={0, 1, 1,1,0,-1,-1,-1};
int sdy[4]={-1, 0, 1, 0};
int sdx[4]={0, 1, 0, -1};

struct position{
    int y;
    int x;
};

struct santa{
    int num;
    position pos;
    int point;
    bool live;
    
};

santa santas[32];

int chk_dist(int y1, int x1, int y2, int x2){
    int ny = abs(y1 - y2);
    int nx = abs(x1 - x2);

    return ((ny*ny) + (nx*nx));
}

void crush(int santa_idx, int y, int x, int dy, int dx, int idx){
    if(idx == 0) {
        // 루돌프가 와서 부딪힐때
        santas[santa_idx].point += C;
        
        dy *= -C;
        dx *= -C;

        int nexty = santas[santa_idx].pos.y + dy;
        int nextx = santas[santa_idx].pos.x + dx;

        if(nexty < 0 || nexty >= N || nextx < 0 || nextx >= N)
        {
            santas[santa_idx].live = 0;
            map[santas[santa_idx].pos.y][santas[santa_idx].pos.x] = 0;

            return;
        }
        
        //map[ny][nx] = santas[santa_idx];
        if(map[nexty][nextx] > 0){
            //action(nexty, nextx);
        }
        map[nexty][nextx] = santas[santa_idx].num;
    }
    else if(idx == 1){
        // 산타가 와서 부딪힐때
        santas[santa_idx].point += D;

        dy *= -D;
        dx *= -D;

        int nexty = santas[santa_idx].pos.y + dy;
        int nextx = santas[santa_idx].pos.x + dx;

        if(nexty < 0 || nexty >= N || nextx < 0 || nextx >= N)
        {
            santas[santa_idx].live = 0;
            map[santas[santa_idx].pos.y][santas[santa_idx].pos.x] = 0;
            
            return;
        }

        if(map[nexty][nextx] > 0){
            //action(nexty, nextx);
        }
        map[nexty][nextx] = santas[santa_idx].num;
    }
}

void chk_dir(int cury, int curx, int tar_y, int tar_x, int idx){
    if(idx == 0) {
        // 루돌프
        int dx = 0;
        int dy = 0;
        int dist = 1e9;
        int next_y = 0;
        int next_x = 0;
        for(int i = 0; i < 8; i++){
            int tmpy = cury + rdy[i];
            int tmpx = curx + rdx[i];
            int tmp_dist = chk_dist(tmpy, tmpx, tar_y, tar_x);
            
            if(tmp_dist >= dist){
                continue;
            }

            if(tmpy < 0 || tmpx < 0 || tmpy >= N || tmpx >= N){
                continue;
            }

            dist = tmp_dist;
            next_y = tmpy;
            next_x = tmpx;
            dy = rdy[i];
            dx = rdx[i];
        }
        if(map[next_y][next_x] != 0){
            crush(map[next_y][next_x], next_y, next_x, dy, dx, 0);
            map[next_y][next_x] = -1;
        }
    }
    else if(idx == 1) {
        // santa
        int dy = 0;
        int dx = 0;
        int dist = 1e9;
        int next_y = -1;
        int next_x = -1;

        for(int i = 0; i < 4; i++){
            int tmpy = cury + sdy[i];
            int tmpx = curx + sdx[i];
            int tmp_dist = chk_dist(tmpy, tmpx, tar_y, tar_x);

            if(tmp_dist >= dist){
                continue;
            }

            if(tmpy < 0 || tmpx < 0 || tmpy >= N || tmpx >= N) {
                continue;
            }

            if(map[tmpy][tmpx] > 0) {
                continue;
            }

            dist = tmp_dist;
            next_y = tmpy;
            next_x = tmpx;
            dy = sdy[i];
            dx = sdx[i];
        }
        if(next_y == -1 || next_x == -1){
            return;
        }
        if(map[next_y][next_x] == -1){
            crush(map[cury][curx], next_y, next_x, dy, dx, 1);
        }
    }
}

void chk_roo(int y, int x) {
    int dist = 1e9;
    int close_y = 1e9;
    int close_x = 1e9;
    for(int i = 1; i <= P; i++) {
        if(santas[i].live) {
            if(dist == chk_dist(y, x, santas[i].pos.y, santas[i].pos.x)) {
                if(close_y == santas[i].pos.y) {
                    if(close_x > santas[i].pos.x) {
                        close_y = santas[i].pos.y;
                        close_x = santas[i].pos.x;
                        dist = chk_dist(y, x, santas[i].pos.y, santas[i].pos.x);
                    }
                }
                else if(close_y > santas[i].pos.y){
                    close_y = santas[i].pos.y;
                    close_x = santas[i].pos.x;
                    dist = chk_dist(y, x, santas[i].pos.y, santas[i].pos.x);
                }
            }
            else if(dist > chk_dist(y, x, santas[i].pos.y, santas[i].pos.x)) {
                close_y = santas[i].pos.y;
                close_x = santas[i].pos.x;
                dist = chk_dist(y, x, santas[i].pos.y, santas[i].pos.x);
            }
            //dist = min(dist, chk_dist(y, x, santas[i].pos.y, santas[i].pos.x));
        }
    }
    chk_dir(y, x, close_y, close_x, 0);
}

void chk_san(int idx, int roo_y, int roo_x) {
    if(santas[idx].live) {
        int dist = 1e9;
        chk_dir(santas[idx].pos.y, santas[idx].pos.x, roo_y, roo_x, 1);
    }   

}

int main() {
    // 여기에 코드를 작성해주세요.
    
    cin >> N >> M >> P >> C >> D;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            map[i][j] = 0;
        }
    }
    cin >> rooy >> roox;
    for(int i = 1; i <= P;i++){
        cin >> santas[i].num >> santas[i].pos.y >> santas[i].pos.x;
    }
    return 0;
}