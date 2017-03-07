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


void int2array(int num, statusArray& arr){
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			arr[i][j] = num%10;
			num /= 10;
		}
	}
}
void array2int(statusArray& arr, int& num){
	num = 0;
	for(int i=1; i<=3; i++){
		for(int j=1; j<=3; j++){
			num *= 10;
			num += arr[i][j];
		}
	}
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




