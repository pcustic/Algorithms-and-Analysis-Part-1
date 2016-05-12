#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

int main(void){
	ifstream fajl;
	fajl.open("DijkstraData.txt");
	int n = 200;
	//cin >> n;
	vector<int> temp(n+1,-1);
	vector<vector<int> > graf(n+1,temp);

	for(int i=1;i<=n;++i){
		string linija;
		getline(fajl,linija);
		istringstream formatirano(linija);
		int temp1,temp2=1;
		formatirano >> temp1;
		
		while(formatirano >> temp1 >> temp2){
			graf[i][temp1] = temp2;
			graf[temp1][i] = temp2;
		}

	}
	vector<int> visited(n+1,0),distance(n+1,1000000000);
	distance[1] = 0;
	
	for(int k=0;k<n;++k){
		int trenutni = -1;
		int maxDist = 1000000000;
		for(int i=1;i<=n;++i)
			if((!visited[i]) && (distance[i]<maxDist)){
				trenutni = i;
				maxDist = distance[i];
			}
				
		if(trenutni == -1) break;
		
		visited[trenutni]=1;
		for(int i=1;i<=n;++i){
			if(graf[trenutni][i] != -1)
				if(distance[trenutni] + graf[trenutni][i] < distance[i])
					distance[i] = distance[trenutni] + graf[trenutni][i];
		}
		
	}
	
	for(int i=1;i<=n;++i)
		cout << i << ".cvor: " << distance[i] << endl;
	
	return 0;
}
