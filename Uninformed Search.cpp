#include<bits/stdc++.h>
using namespace std;

typedef pair<int,vector<int> > pi;
clock_t start;
double duration;

//cek apakah sudah mencapai goal
bool cek(vector<int> tmp, vector<int> goal){
	for(int i=0;i<9;i++)
		if(tmp[i]!=goal[i]) return false;
	
	return true;
}

//masukkan ke antrian berikutnya
template <typename T>
void masukkan(T *aksi, int depth, vector<int> tmp, set<vector<int> > *done){
	if(!(done->count(tmp))){
		aksi->push(make_pair(depth+1,tmp));
		done->insert(tmp);
	}
}

//geser kotak kosong dengan prioritas LRUD
template <typename T>
void geser(T *aksi, int depth, vector<int> tmp, set<vector<int> > *done){
	int ind;
	for(int i=0;i<9;i++)
		if(tmp[i]==0) ind=i;
	
	//geser kiri
	if(ind%3!=0) {swap(tmp[ind],tmp[ind-1]); masukkan(aksi, depth, tmp, done); swap(tmp[ind],tmp[ind-1]);}
	//geser kanan
	if(ind%3!=2) {swap(tmp[ind],tmp[ind+1]); masukkan(aksi, depth, tmp, done); swap(tmp[ind],tmp[ind+1]);}
	//geser atas
	if(ind/3!=0) {swap(tmp[ind],tmp[ind-3]); masukkan(aksi, depth, tmp, done); swap(tmp[ind],tmp[ind-3]);}
	//geser bawah
	if(ind/3!=2) {swap(tmp[ind],tmp[ind+3]); masukkan(aksi, depth, tmp, done); swap(tmp[ind],tmp[ind+3]);}
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

void bfs_algo(){
	//input state dan goal
	vector<int> state, goal;
	state.resize(9); goal.resize(9);
	menu_input(&state,&goal,"BREADTH FIRST SEARCH");
	
	//bfs memakai queue
	int counter = 0, depth = 0;
	set<vector<int> > done;
	queue<pi> aksi;
	pi tmp;
	
	done.insert(state);
	aksi.push(make_pair(depth,state));
	
	while(!aksi.empty()){
		tmp = aksi.front(); aksi.pop();
		print(tmp.second);								//cetak kondisi 8 puzzle
		if(cek(tmp.second,goal)) break;					//jika sama dengan goal, berhenti
		else geser(&aksi,tmp.first,tmp.second,&done);	//jika tidak sama, geser
		counter++;
	}
	
	duration = (clock()-start)/(double)CLOCKS_PER_SEC;
	cout<<"Waktu Proses (s) : "<<duration<<endl;
	cout<<"Pencarian selesai dalam "<<counter<<" langkah"<<endl;
	cout<<"Minimum langkah dari state ke goal: "<<tmp.first<<endl;
}

void dfs_algo(){
	//input state dan goal
	vector<int> state, goal;
	state.resize(9); goal.resize(9);
	menu_input(&state,&goal,"DEPTH FIRST SEARCH");
	
	//dfs memakai stack
	int counter = 0, depth = 0;
	set<vector<int> > done;
	stack<pi> aksi;
	pi tmp;
	
	done.insert(state);
	aksi.push(make_pair(depth,state));
	
	while(!aksi.empty()){
		tmp = aksi.top(); aksi.pop();
		print(tmp.second);								//cetak kondisi 8 puzzle
		if(cek(tmp.second,goal)) break;					//jika sama dengan goal, berhenti
		else geser(&aksi,tmp.first,tmp.second,&done);	//jika tidak sama, geser
		counter++;
	}
	
	duration = (clock()-start)/(double)CLOCKS_PER_SEC;
	cout<<"Waktu Proses (s) : "<<duration<<endl;
	cout<<"Pencarian selesai dalam "<<counter<<" langkah"<<endl;
	cout<<"Minimum langkah dari state ke goal: "<<tmp.first<<endl;
}

void ucs_algo(){
	//input state dan goal
	vector<int> state, goal;
	state.resize(9); goal.resize(9);
	menu_input(&state,&goal,"UNIFORM COST SEARCH");
	
	//ucs memakai priority queue
	int counter = 0, depth = 0;
	set<vector<int> > done;
	priority_queue<pi, vector<pi>, greater<pi> > aksi;
	pi tmp;
	
	done.insert(state);
	aksi.push(make_pair(depth,state));
	
	while(!aksi.empty()){
		tmp = aksi.top(); aksi.pop();
		print(tmp.second);								//cetak kondisi 8 puzzle
		if(cek(tmp.second,goal)) break;					//jika sama dengan goal, berhenti
		else geser(&aksi,tmp.first,tmp.second,&done);	//jika tidak sama, geser
		counter++;
	}
	
	duration = (clock()-start)/(double)CLOCKS_PER_SEC;
	cout<<"Waktu Proses (s) : "<<duration<<endl;
	cout<<"Pencarian selesai dalam "<<counter<<" langkah"<<endl;
	cout<<"Minimum langkah dari state ke goal: "<<tmp.first<<endl;
}

int main(){
	string kode;
	
	//menu utama
	while(1){
		cout<<"Selamat Datang di 8 Puzzle Solver"<<endl;
		cout<<"By: James Rafferty Lee   (05111940000055)"<<endl;
		cout<<"    Aldo Yaputra Hartono (05111940000084)"<<endl<<endl;
		cout<<"Metode Penyelesaian:"<<endl;
		cout<<"1. Breadth First Search (BFS)"<<endl;
		cout<<"2. Depth First Search (DFS)"<<endl;
		cout<<"3. Uniform Cost Search (UCS)"<<endl;
		cout<<"0. Keluar"<<endl;
		cout<<endl<<"Pilih (masukkan kode angka): ";
		cin>>kode;
		
		//pilih metode penyelesaian 8 puzzle
		while(kode!="0" && kode!="1" && kode!="2" && kode!="3"){
			cout<<"Kode salah"<<endl;
			cout<<endl<<"Pilih (masukkan kode angka): ";
			cin>>kode;
		}
		if(kode=="0") break;
		else if(kode=="1") bfs_algo();	//breadth first search
		else if(kode=="2") dfs_algo();	//depth first search
		else if(kode=="3") ucs_algo();	//uniform cost search
		
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
Breadth First Search
2 8 3 1 6 4 7 0 5
1 2 3 8 0 4 7 6 5
Waktu Proses (s) : 0.093
Pencarian selesai dalam 57 langkah
Minimum langkah dari state ke goal: 5

Depth First Search
2 8 3 1 6 4 7 0 5
1 2 3 8 0 4 7 6 5
Waktu Proses (s) : 31.992
Pencarian selesai dalam 29316 langkah
Minimum langkah dari state ke goal: 28013

Uniform Cost Search
2 8 3 1 6 4 7 0 5
1 2 3 8 0 4 7 6 5
Waktu Proses (s) : 0.062
Pencarian selesai dalam 39 langkah
Minimum langkah dari state ke goal: 5
*/
