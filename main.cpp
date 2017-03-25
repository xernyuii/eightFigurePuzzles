#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
typedef int statusArray[4][4];

class Board{
public:
	int status,F,G,H;
	statusArray arr;
	int cid, pid;
	Board(const statusArray& arr, const int F, const int G, const int H, const int cid, const int pid){
		memcpy(this->arr, arr, sizeof(statusArray));
		this->F = F;
		this->G = G;
		this->H = H;
		this->cid = cid;
		this->pid = pid;
	}
	bool operator<(const Board &b) const {
		return F < b.F;
	}
	bool operator<=(const Board &b) const { 
		return F <= b.F;
	}
	bool operator==(const Board &b) const{
		return F == b.F;
	}
};


std::set<Board> opening;
std::vector<Board> path;
std::set<int> closed;

int DIS[10][10];
statusArray START;
statusArray END;
int movx[] = {-1, 0, 1, 0};
int movy[] = {0, 1, 0, -1};
void int2array(int num, statusArray& arr){
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			arr[i][j] = num%10;
			num /= 10;
		}
	}
}
int array2int(statusArray& arr){
	int num = 0;
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			num *= 10;
			num += arr[i][j];
		}
	}
	return num;
}

void preWorkforDIS(){

}

int getH(const statusArray& now, const statusArray& end){
	int H = 0;
	std::vector<int> S;
	std::vector<int> E;
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			S.push_back(now[i][j]);
			E.push_back(end[i][j]);
		}
	}
	for(int i=0;i<=8;i++){
		for(int j=0;j<=8;j++){
			if(S[i] == E[j]){
				int ix = i % 3;
				int iy = i / 3;
				int jx = j % 3;
				int jy = j / 3;
				H += abs(ix - jx) + abs(iy - jy);
			}
		}
	}
	return H;
}

int getF(const Board& now){
	return now.G + now.H;
}

bool success(const statusArray& now, const statusArray& end){
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			if (now[i][j]!=end[i][j]) return false;
		}
	}
	return true;
}

bool check(const statusArray& now, const statusArray& end){
	int cnt_now = 0;
	int cnt_end = 0;
	for(int i=0; i<9; i++){
		for(int j=0; j<i; j++){
			if(now[j/3+1][j%3+1] != 0 && now[j/3+1][j%3+1] < now[i/3+1][i%3+1]) cnt_now++;
			if(end[j/3+1][j%3+1] != 0 && end[j/3+1][j%3+1] < end[i/3+1][i%3+1]) cnt_end++;

		}
	}
	return (cnt_now % 2) == (cnt_end % 2);
}

int solve(const statusArray& start, const statusArray& end){
	opening.clear();
	closed.clear();
	path.clear();
	int id = 0;
	if(check(start, end)) return -1;
	opening.insert(Board(start, getH(start, end), 0, getH(start, end), id, id++));
	while(opening.size()){
		Board p = *(opening.begin());
		opening.erase(opening.begin());
		path.push_back(p);
		closed.insert(array2int(p.arr));
		if(success(p.arr, end)) return p.G;
		int cx = 0, cy = 0;
		for(int i=1; i<=3; i++){
			if(cx != 0) break;
			for(int j=1; j<=3; j++){
				if(p.arr[i][j] == 0){
					cx = i;
					cy = j;
					break;
				}
			}
		}
		for(int k=0; k<4; k++){
			int nx = cx + movx[k];
			int ny = cy + movy[k];
			if(nx < 1 || nx > 3 || ny < 1 || ny > 3) continue;
			std::swap(p.arr[cx][cy], p.arr[nx][ny]);
			Board n(p.arr, 0, p.G+1, getH(p.arr, end), id++, p.cid);
			std::swap(p.arr[cx][cy], p.arr[nx][ny]);
			n.F = getF(n);
			if(closed.find(array2int(n.arr)) == closed.end()){
				std::set<Board>::iterator it = find(opening.begin(), opening.end(), n);
				if(it != opening.end() && it->F > n.F){
					opening.erase(it);
					opening.insert(n);
				}
				if(it == opening.end()){
					opening.insert(n);
				}
			}
		}
	}
	return -1;
}
void input(statusArray &S){
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			scanf("%1d",&S[i][j]);
		}
	}
}
void output(int pid, int ss, int st){
	if(st < 0) return;
	else if(st ==0 ){
		printf("step:%d ==>\n",st);
		statusArray *p = &path[ss].arr;
		for(int i=1;i<=3;i++){
			for(int j=1;j<=3;j++){
				printf("%d",(*p)[i][j]);
			}
			printf("\n");
		}
	}

}
int main(){
	freopen("test.in","r",stdin);
	statusArray S,E;
	input(S);
	input(E);
	int step = solve(S,E);
	if(step != -1){
		output((path.end()-1)->pid, path.size() - 1, step);
	}
	else
		printf("No Answer!\n");

	return 0;
}