#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

long long int SortCountSplit(vector<int> &niz,int poc,int kraj){
	/*Ovo je kao Merge rutina iz Mergesorta samo kada spajamo dva niza
	  onda ukoliko uzimamo element iz desnog dijela niza znamo
	  da se tu dogodila inverzija.*/
	
	vector<int> livi,desni;
	long long int brojac = 0;
	int sredina = (poc+kraj)/2;
	for(int i=poc;i<=sredina;++i)
		livi.push_back(niz[i]);
	for(int i=sredina+1;i<=kraj;++i)
		desni.push_back(niz[i]);
	
	int i=0,j=0,k=poc;
	while((i<livi.size()) && (j<desni.size())){
		if(livi[i]<desni[j]){
			niz[k]=livi[i];
			++i;
			++k;
		}
		else{
			niz[k]=desni[j];
			brojac+= (long long)livi.size()-i;
			++k;
			++j;
		}
	}
	while(i<livi.size()){
		niz[k]=livi[i];
		++i;
		++k;
	}
	while(j<desni.size()){
		niz[k]=desni[j];
		++j;
		++k;
	}
	
	return brojac;
}
long long int SortCount(vector<int> &niz,int poc,int kraj){
	//rekurzivno dijelimo niz i brojimo lijeve, desne i podijeljene inverzije
	if(kraj-poc==0) return 0;
	long long int lijevi,desni,split;
	lijevi = SortCount(niz,poc,(poc+kraj)/2);
	desni = SortCount(niz,(poc+kraj)/2+1,kraj);
	split = SortCountSplit(niz,poc,kraj);
	return (lijevi+desni+split);
}
	
	
int main(void){
	vector<int> niz(100000);

	ifstream fajl;
	fajl.open("IntegerArray.txt");
	for(int i = 0;i<100000;++i)
		fajl >> niz[i];
	
	cout << SortCount(niz,0,99999) << endl;
	
	return 0;
}
	
