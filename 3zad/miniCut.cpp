#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*Algoritam: dok imamo vise od dva cvora na random izaberemo dva cvora
  i spojimo ih. Broj bridova koji nam na kraju ostanu izmedju ta dva cvora
  je jedan cut u grafu. 
*/


int kontraktiraj(vector<vector<int> > graf){
	while(graf.size()>3){
		int i,j;
		i = rand() % (graf.size()-1)+1;
		j = rand() % graf[i].size();

		j = graf[i][j];
		if(i>j)swap(i,j);

		//u cvor i dodajemo sve elemente iz cvora j i mijenjamo graf
		//tako da sve veze koje su isle prema j prebacujemo u i
		graf[i].insert(graf[i].end(),graf[j].begin(),graf[j].end());
		for(int t=1;t<graf.size();++t)
			for(int k=0;k<graf[t].size();++k)
				if(graf[t][k]==j) graf[t][k]=i;

		//izbrise redak j (inace bi trebalo .begin()+j-1 ali prvi elem je prazan
		graf.erase(graf.begin()+j);

		//izbrise sve elemente iz retka i koji imaju vrijednost i zato jer su to stari bridovi prema j.
		// ovaj remove samo preseli elemente i na kraj vectora i vrati it koji kaze odakle
		//pocinju ti nezeljeni elementi
		graf[i].erase(remove(graf[i].begin(),graf[i].end(),i),graf[i].end());

		//posto smo izbrisali jedan cvor moramo svim cvorevima poslije tog
		//smanjiti oznaku cvora za 1
		for(int t=1;t<graf.size();++t)
			for(int k=0;k<graf[t].size();++k)
				if(graf[t][k]>j) --graf[t][k];
	}

	return graf[1].size();
}

int main(void){
	ifstream fajl;
	fajl.open("kargerMinCut.txt");
	int n;
	cin >> n;
	vector<vector<int> > graf(n+1);
	//kompliciran unos radi cudnog formata ulazne datoteke
	for(int i=1;i<=n;++i){
		string linija;
		getline(fajl,linija);
		istringstream formatirano(linija);
		int temp,prvi=1;
		vector<int> red;
		while(formatirano >> temp){
			if(prvi)
				prvi=0;
			else
				red.push_back(temp);
		}
		graf[i]=red;
	}

	fajl.close();
	//da bi bili sigurni da je to min cut trebamo vise puta pokrenuti algoritam
	srand(time(NULL));
	int min = kontraktiraj(graf);
	for(int i=0;i<10;++i){
		int temp;
		temp = kontraktiraj(graf);
		if(temp<min)
			min = temp;
	}
	cout << "finalno: " << min << endl;

	return 0;
}

