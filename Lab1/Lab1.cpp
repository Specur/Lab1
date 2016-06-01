#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;
#define Y 4

class Liczba
{
public:
	double x;
	double wartosc;
	int bity[41];


	friend ostream & operator<< (ostream &wyjscie, const Liczba &s);
};

ostream & operator<< (ostream &wyjscie, const Liczba &s)
{
	return wyjscie << "X: " << s.x << " wartosc:" << s.wartosc << endl;
}

double obliczWartosc(double x)
{
	return (x*x*x) - (x *x) + sin(4 * x) - cos(15 * x);
}

void obliczRozwiniecie(Liczba &populacja1)
{
	int cyfra = populacja1.x;
	if (populacja1.x < 0)
	{
		populacja1.bity[0] = 1;
	}	
	else
	{
		populacja1.bity[0] = 0;
	}
		
	double ulamek = populacja1.x - cyfra;
	for (int i = 1; i < 41; i++)
	{
		ulamek = ulamek * 2;
		if (ulamek >= 1 )
		{
			populacja1.bity[i] = 1;
			ulamek = ulamek - 1;
		}
		else if (ulamek <= -1)
		{
			populacja1.bity[i] = 1;
			ulamek = ulamek + 1;
		}
		else
			populacja1.bity[i] = 0;
	}
}

double obliczWartoscRozwiniecia(Liczba &populacja1)
{
	double wartosc;
	if (populacja1.bity[0] == 0)
		wartosc = 0;
	else wartosc = -1;
	for (int i = 1; i < 41; i++)
	{
		wartosc += populacja1.bity[i] / pow(2,i);
	}
	if (populacja1.x <0)
	return -1* (1+wartosc);
	else return wartosc;
}

void swap(vector<Liczba>& vec);

bool wieksze(Liczba PierwszaLiczba, Liczba DrugaLiczba) //funkcja mówi¹ca który element i w jakim wypadku jest wiekszy
{
	return PierwszaLiczba.wartosc > DrugaLiczba.wartosc;
}

void sortowanie(vector <Liczba> &populacja1)
{
	//cout << "------------------Sortowanie----------------------" << endl;
	sort(populacja1.begin(), populacja1.end(), wieksze);

	cout << "Najwieksza wartosc:" << populacja1[0] << endl;


}

int main()
{

	//inicjalizacja populacji (2 wektory)
	vector<Liczba> populacja1;
	vector<Liczba> populacja2;
	srand(time(NULL));
	Liczba tmp;
	int liczba_1;
	int liczba;
	int liczba_2;
	int liczba_3;
	//wartosci poczatkowe
	for (int i = 0; i < Y; i++)
	{
		tmp.x = ((double)((rand() % 20000)*10.3) - 100000.0) / 100000.0;
		//cout << setprecision(20) << tmp.x;
		populacja1.push_back(tmp);
		tmp.x = 0;
		populacja2.push_back(tmp);
		obliczRozwiniecie(populacja1[i]);
		//for (int j = 0; j < 40; j++)
			//cout << endl << populacja1[i].bity[j] << " jest bitem numer: " << j  << endl;
		populacja1[i].wartosc = obliczWartosc(populacja1[i].x);
	}

	

	sortowanie(populacja1);

	cout << "---------------Iteracje---------------" << endl;

	for (int i = 0; i < 200000; i++)
	{
		cout << "Iteracja: " << i + 1 << endl;



		/** warunki zakoñczenia iteracji -NIE WIEM JAK ZROBIC xd
		if (populacja1[0].wartosc == 0)
		{
		cout << "Idealne dopasowanie: " << endl << "Nazwa: " << populacja1[0].x << endl << " Fitness: " << populacja1[0].wartosc;
		getchar();
		exit(1);
		}*/

		//tutaj do zmiennej liczba_2 jest przypisywany nr indexu osobnika ktory zostal wylosowany za pomoca metody ruletki
		//do zmiennej liczba_3 jest zapisywany index drugiego osobnika

		for (int i = 0; i < Y; i++)
		{
			liczba = (double)((rand() % 5458));
			liczba_1 = (double)((rand() % 5458));
			if (liczba < 100){
				liczba_2 = (int)liczba / 10;
			}
			else if (liczba < 910){
				liczba_2 = ((int)liczba - 100 / 9) + 10;
			}
			else if (liczba < 2910){
				liczba_2 = ((int)liczba - 910 / 5) + 100;
			}
			else if (liczba < 4910){
				liczba_2 = ((int)liczba - 2910 / 2) + 500;
			}
			else{
				liczba_2 = ((int)liczba - 4910 / 1) + 1500;

			}

			if (liczba_1 < 100){
				liczba_3 = (int)liczba / 10;
			}
			else if (liczba_1 < 910){
				liczba_3 = ((int)liczba - 100 / 9) + 10;
			}
			else if (liczba_1 < 2910){
				liczba_3 = ((int)liczba - 910 / 5) + 100;
			}
			else if (liczba_1 < 4910){
				liczba_3 = ((int)liczba - 2910 / 2) + 500;
			}
			else{
				liczba_3 = ((int)liczba - 4910 / 1) + 1500;

			}


			//tutaj mamy juz wybrane osobniki liczba_2 i liczba_3 przechowuja ich indexy 
			//teraz mutacje genow



		}


		//cout << "------------------ Kry¿owanie ----------------------" << endl;
		/**	for (int i = 0; i < 200; i++)
		{
		TO JEST DOBRZE
		for(int i=0;i<Y;i++)
		{
		if(i==0)
		populacja1[i].kolopoczatek=0;
		else
		populacja1[i].kolopoczatek = populacja1[i-1].kolokoniec+0.0000000001;
		populacja1.[i].kolokoniec = populacja[i].kolopoczatek + (2048-Y)/2098176;
		}
		DOT¥D


		int wspolczynnik_podzialu = (rand() % Y-1) + 1;
		//cout << osobnik1 << ", " << osobnik2 << "," << wspolczynnik_podzialu;
		string tmp = populacja1[osobnik1].x.substr(0, wspolczynnik_podzialu);
		string tmp1 = populacja1[osobnik2].x.substr(wspolczynnik_podzialu, Y);
		populacja2[i + 102].x = tmp + tmp1;

		//mutacja
		int mutacja = (rand() % 101);

		if (mutacja < 5)
		{
		//cout << "------------------ Mutacja ----------------------" << endl;
		int numer_mutacji = (rand() % Y-1) + 1;
		tmp = populacja2[i + 102].x.substr(0, numer_mutacji - 1);
		tmp1 = populacja2[i + 102].x.substr(numer_mutacji, Y);
		char znak = (rand() % 94) + 32;
		populacja2[i + 102].x = tmp + znak + tmp1;
		//cout << populacja2[i + 102].x << endl;
		}
		}
		*/


		//obliczanie wartoœci funkcji
		for (int i = 0; i < populacja2.size(); i++) {
			populacja2[i].wartosc = obliczWartosc(populacja2[i].x);
		}

		sortowanie(populacja2);
		//	swap(populacja1, populacja2);
	}

}



