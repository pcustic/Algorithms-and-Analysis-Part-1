#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main(void){
	/*Ideja algoritma je da manju polovicu niza drzimo u max hrpi
	  pa da imamo brzi pristup najvecem elementu u manjoj polovici
	  a ostalu polovicu u min hrpi pa da imamo brz pristup najmanjem
	  elementu u vecoj polovici. Tako znamo da je medijan neki od ta
	  dva elementa */
	 
	priority_queue<int> hLow;
	priority_queue<int,vector<int>,greater<int> > hHigh;
	ifstream fajl;
	int suma = 0;
	
	fajl.open("Median.txt");
	int n = 10000;
	//cin >> n;
	for(int i=1;i<=n;++i){
		int temp;
		fajl >> temp;
		if(i==1){
			suma = temp % 10000;
			hLow.push(temp);
			continue;
		}
		if(temp < hLow.top())
			hLow.push(temp);
		else
			hHigh.push(temp);
		
		//balansiranje hrpi
		if(hLow.size()>hHigh.size()+1){
			hHigh.push(hLow.top());
			hLow.pop();
		}
		
		if(hHigh.size()>hLow.size()+1){
			hLow.push(hHigh.top());
			hHigh.pop();
		}
		
		//ako je paran broj ucitan onda uzimamo sa hLow hrpe
		//inace uzimamo sa one hrpe koja ima vise elemenata
		if(i%2==0){
			cout << hLow.top() << endl;
			suma = (suma+hLow.top()) % 10000;
		}
		else{
			if(hLow.size()>hHigh.size()){
				cout << hLow.top() << endl;
				suma = (suma+hLow.top()) % 10000;
			}
			else{
				cout << hHigh.top() << endl;
				suma = (suma+hHigh.top()) % 10000;
			}
		}
	}
	cout << "Suma: " << suma << endl;
	return 0;
}
