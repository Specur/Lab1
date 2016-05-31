#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

#define Y 2048
#define dokladnosc 0.0009765625;
class Liczba 
{
public:
	double x;
	double wartosc;
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



void swap(vector<Liczba>& vec);

bool mniejsze(Liczba PierwszaLiczba, Liczba DrugaLiczba) //funkcja mówi¹ca który element i w jakim wypadku jest mniejszy od drugiego
{
	return PierwszaLiczba.wartosc < DrugaLiczba.wartosc;
}

void sortowanie(vector <Liczba> &populacja1)
{
	//cout << "------------------Sortowanie----------------------" << endl;
	sort(populacja1.begin(), populacja1.end(), mniejsze);

	cout << "najmniejsza wartosc:" << populacja1[0] << endl;
	

}

int main()
{

	//inicjalizacja populacji (2 wektory)
	vector<Liczba> populacja1;
	vector<Liczba> populacja2;
	srand(time(NULL));

	//wartosci poczatkowe
	for (int i = 0; i < Y; i++) 
	{
		Liczba tmp;
		tmp.x = ((rand() % 10000) - 10000)/10000 ;
		populacja1.push_back(tmp);
		tmp.x = 0;
		populacja2.push_back(tmp);
	}

	//obliczanie wartosci
	for (int i = 0; i < populacja1.size(); i++) {
		populacja1[i].wartosc = obliczWartosc(populacja1[i].x);
	}
	// getchar();
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


		//kopiowanie 5% do nowej populacji
	//cout << "------------------Kopiowanie 5%----------------------" << endl;
	for (int i = 0; i < 102; i++)
		{
			populacja2[i].x = populacja1[i].x;
			populacja2[i].wartosc = populacja1[i].wartosc;
		}


	//cout << "------------------ Kry¿owanie ----------------------" << endl;
/**	for (int i = 0; i < 200; i++)
	{
		TO JEST DOBRZE 
		for(int i=0;i<Y;i++)
		{
		if(i==0)
		populacja1[i].kolopocz=0;
		else
		populacja1[i].kolopocz = populacja1[i-1].kolokoniec+0.0000000001;
		populacja1.[i].kolokoniec = populacja[i].kolopocz + (2048-Y)/2098176;
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
		//wygenerowanie reszty osobników
	for (int i = 302; i < Y; i++)
	{
		Liczba tmp;
		for (int j = 0; j < Y; j++) 
		{
			tmp.x += (rand() % 94) + 32;
		}
			populacja2[i].x = tmp.x;
		//	cout << populacja2[i].x << "   " << populacja2[i].wartosc << endl;
	}
	//	getchar();

		//obliczanie fitnesu
	for (int i = 0; i < populacja2.size(); i++) {
		populacja2[i].wartosc = obliczWartosc(populacja2[i].x);
		}
	
	//getchar();

	sortowanie(populacja2);
	swap(populacja1, populacja2);
}

}



