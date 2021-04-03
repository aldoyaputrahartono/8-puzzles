#include<bits/stdc++.h>
using namespace std;

typedef pair<int,vector<int> > pi;
typedef pair<int,pi> pii;
typedef priority_queue<pii, vector<pii>, greater<pii> > pqpii;
clock_t start;
double duration;

//cek apakah sudah mencapai goal
bool cek(vector<int> tmp, vector<int> goal){
	for(int i=0;i<9;i++)
		if(tmp[i]!=goal[i]) return false;
	
	return true;
}

//heuristik dengan manhattan distance
int manhattan(vector<int> state, vector<int> goal){
	int res = 0, idx;
	for(int i=0;i<9;i++){
		if(state[i]==0) continue;
		for(idx=0; idx<9; idx++)
			if(state[i]==goal[idx]) break;
		int dx = abs(i%3 - idx%3);
		int dy = abs(i/3 - idx/3);
		res += dx + dy;
	}
	return res;
}

//masukkan ke antrian berikutnya
void masukkan(pqpii *aksi, int depth, vector<int> tmp, vector<int> goal, set<vector<int> > *done, int kode){
	if(!(done->count(tmp))){
		int heur = manhattan(tmp,goal);
		if(kode == 1) aksi->push(make_pair(heur,make_pair(depth+1,tmp)));
		if(kode == 2) aksi->push(make_pair(heur+depth+1,make_pair(depth+1,tmp)));
		done->insert(tmp);
	}
}

//geser kotak kosong
void geser(pqpii *aksi, int depth, vector<int> tmp, vector<int> goal, set<vector<int> > *done, int kode){
	int ind;
	for(int i=0;i<9;i++)
		if(tmp[i]==0) ind=i;
	
	//geser kiri
	if(ind%3!=0) {swap(tmp[ind],tmp[ind-1]); masukkan(aksi, depth, tmp, goal, done, kode); swap(tmp[ind],tmp[ind-1]);}
	//geser kanan
	if(ind%3!=2) {swap(tmp[ind],tmp[ind+1]); masukkan(aksi, depth, tmp, goal, done, kode); swap(tmp[ind],tmp[ind+1]);}
	//geser atas
	if(ind/3!=0) {swap(tmp[ind],tmp[ind-3]); masukkan(aksi, depth, tmp, goal, done, kode); swap(tmp[ind],tmp[ind-3]);}
	//geser bawah
	if(ind/3!=2) {swap(tmp[ind],tmp[ind+3]); masukkan(aksi, depth, tmp, goal, done, kode); swap(tmp[ind],tmp[ind+3]);}
}

//cetak kondisi 8 puzzle saat ini
void print(vector<int> tmp){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<tmp[i*3+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

//cetak menu input
void menu_input(vector<int> *state, vector<int> *goal, string str){
	cout<<endl<<str<<endl;
	cout<<"Masukkan angka 1-8 sebagai angka pada puzzle dan 0 sebagai kotak kosong"<<endl;
	cout<<"Masukkan state awal: ";
	for(int i=0;i<9;i++) cin>>(*state)[i];
	cout<<"Masukkan goal akhir: ";
	for(int i=0;i<9;i++) cin>>(*goal)[i];
	start = clock();
}

void greedy_bfs_algo(){
	//input state dan goal
	vector<int> state, goal;
	state.resize(9); goal.resize(9);
	menu_input(&state,&goal,"GREEDY BEST FIRST SEARCH");
	
	//greedy bfs memakai priority queue
	int heuristik = manhattan(state,goal);
	int counter = 0, depth = 0;
	set<vector<int> > done;
	pqpii aksi;
	pii tmp;
	
	done.insert(state);
	aksi.push(make_pair(heuristik,make_pair(depth,state)));
	
	while(!aksi.empty()){
		tmp = aksi.top(); aksi.pop();
		print(tmp.second.second);											//cetak kondisi 8 puzzle
		if(cek(tmp.second.second,goal)) break;								//jika sama dengan goal, berhenti
		else geser(&aksi,tmp.second.first,tmp.second.second,goal,&done,1);	//jika tidak sama, geser
		counter++;
	}
	
	duration = (clock()-start)/(double)CLOCKS_PER_SEC;
	cout<<"Waktu Proses (s) : "<<duration<<endl;
	cout<<"Pencarian selesai dalam "<<counter<<" langkah"<<endl;
	cout<<"Minimum langkah dari state ke goal: "<<tmp.second.first<<endl;
}

void a_star_algo(){
	//input state dan goal
	vector<int> state, goal;
	state.resize(9); goal.resize(9);
	menu_input(&state,&goal,"A* SEARCH");
	
	//a* memakai priority queue
	int heuristik = manhattan(state,goal);
	int counter = 0, depth = 0;
	set<vector<int> > done;
	pqpii aksi;
	pii tmp;
	
	done.insert(state);
	aksi.push(make_pair(heuristik+depth,make_pair(depth,state)));
	
	while(!aksi.empty()){
		tmp = aksi.top(); aksi.pop();
		print(tmp.second.second);											//cetak kondisi 8 puzzle
		if(cek(tmp.second.second,goal)) break;								//jika sama dengan goal, berhenti
		else geser(&aksi,tmp.second.first,tmp.second.second,goal,&done,2);	//jika tidak sama, geser
		counter++;
	}
	
	duration = (clock()-start)/(double)CLOCKS_PER_SEC;
	cout<<"Waktu Proses (s) : "<<duration<<endl;
	cout<<"Pencarian selesai dalam "<<counter<<" langkah"<<endl;
	cout<<"Minimum langkah dari state ke goal: "<<tmp.second.first<<endl;
}

int main(){
	string kode;
	
	//menu utama
	while(1){
		cout<<"Selamat Datang di 8 Puzzle Solver"<<endl;
		cout<<"By: James Rafferty Lee   (05111940000055)"<<endl;
		cout<<"    Aldo Yaputra Hartono (05111940000084)"<<endl<<endl;
		cout<<"Metode Penyelesaian:"<<endl;
		cout<<"1. Greedy Best-First Search"<<endl;
		cout<<"2. A* Search"<<endl;
		cout<<"0. Keluar"<<endl;
		cout<<endl<<"Pilih (masukkan kode angka): ";
		cin>>kode;
		
		//pilih metode penyelesaian 8 puzzle
		while(kode!="0" && kode!="1" && kode!="2"){
			cout<<"Kode salah"<<endl;
			cout<<endl<<"Pilih (masukkan kode angka): ";
			cin>>kode;
		}
		if(kode=="0") break;
		else if(kode=="1") greedy_bfs_algo();	//Greedy Best-First Search
		else if(kode=="2") a_star_algo();		//A* Search
		
		cout<<endl<<"Ingin mengulang lagi (y/n)? ";
		cin>>kode;
		
		//pilih mau ulang lagi atau tidak
		while(kode!="y" && kode!="Y" && kode!="n" && kode!="N"){
			cout<<"Kode salah"<<endl;
			cout<<endl<<"Ingin mengulang lagi (y/n)? ";
			cin>>kode;
		}
		if(kode=="n" || kode=="N") break;
		else if(kode=="y" || kode=="Y") system("CLS"); //clear screen
	}
	
	//program berakhir
	cout<<endl<<"Terima Kasih dan Selamat Tinggal"<<endl;
	return 0;
}

/*
Greedy Best First Search
2 8 3 1 6 4 7 0 5
1 2 3 8 0 4 7 6 5
Waktu Proses (s) : 0.016
Pencarian selesai dalam 5 langkah
Minimum langkah dari state ke goal: 5
7 2 4 5 0 6 8 3 1
0 1 2 3 4 5 6 7 8
Waktu Proses (s) : 0.500
Pencarian selesai dalam 427 langkah
Minimum langkah dari state ke goal: 60

A* Search
2 8 3 1 6 4 7 0 5
1 2 3 8 0 4 7 6 5
Waktu Proses (s) : 0.015
Pencarian selesai dalam 5 langkah
Minimum langkah dari state ke goal: 5
7 2 4 5 0 6 8 3 1
0 1 2 3 4 5 6 7 8
Waktu Proses (s) : 4.530
Pencarian selesai dalam 4085 langkah
Minimum langkah dari state ke goal: 26

testcase lain
2 5 3 1 7 6 4 0 8
1 2 3 4 5 6 7 8 0

4 1 3 7 8 2 5 0 6
1 2 3 4 5 6 7 8 0

2 4 3 1 0 7 8 5 6
1 2 3 4 5 6 7 8 0

2 8 3 4 5 7 0 1 6
1 2 3 4 5 6 7 8 0

6 8 0 3 1 2 4 7 5
1 2 3 4 5 6 7 8 0

3 1 2 5 0 6 8 4 7
1 2 3 4 5 6 7 8 0

0 5 7 8 2 3 1 4 6
1 2 3 4 5 6 7 8 0

7 4 3 5 6 1 0 8 2
1 2 3 4 5 6 7 8 0
*/
