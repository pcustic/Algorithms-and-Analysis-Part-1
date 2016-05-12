#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

int brojac = 0;

void choosePivot(vector<int> &niz,int poc,int kraj){
    //odabir pivotnog elementa
    vector<int> temp(3);
    temp[0]=niz[poc];
    temp[1]=niz[(poc+kraj)/2];
    temp[2]=niz[kraj];
    sort(temp.begin(),temp.end());

    if(temp[1]==niz[(poc+kraj)/2]){
        swap(niz[poc],niz[(poc+kraj)/2]);
        return;
    }

    if(temp[1]==niz[kraj]){
        swap(niz[poc],niz[kraj]);
        return;
    }
}

void kviksort(vector<int> &niz,int poc,int kraj){
    if(kraj-poc+1==1) return;
    choosePivot(niz,poc,kraj);
    int p = niz[poc];
 
	//usporedjujemo elemente sa pivotom i zamjenjujemo ih ako je potrebno
    int i = poc+1;
    for(int j=i;j<=kraj;++j){
        if(niz[j]<p){
            swap(niz[j],niz[i]);
            ++i;
        }
    }
	//stavimo pivota na njegovo mjesto
    swap(niz[poc],niz[i-1]);

	//pozivamo funkciju rekurzivno na manje djelove niza
    if(i-2-poc>0){
		brojac += i-2-poc;
		kviksort(niz,poc,i-2);
	}
	
	if(i>kraj)i=kraj;
	if(kraj-i>0){
		brojac += kraj-i;
		kviksort(niz,i,kraj);
	}
}

int main(void){
    int n = 10000;
    vector<int> niz(n);
    ifstream fajl;
    fajl.open("QuickSort.txt");
    for(int i=0;i<n;++i)
        fajl >> niz[i];
    
    kviksort(niz,0,n-1);
    brojac+=n-1;
  
    //cout << brojac << endl;
	
	for(int i = 0;i<niz.size();++i)
		cout << niz[i] << " ";

	fajl.close();
    return 0;
}
