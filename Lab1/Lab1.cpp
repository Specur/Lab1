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
#define Y 100


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


void obliczWartosc(vector <Liczba> &populacja1)
{
	double x;
	for (int i = 0; i < Y; i++)
	{
		x = populacja1[i].x;
		populacja1[i].wartosc=(x*x*x) - (x *x) + sin(4 * x) - cos(15 * x);
	}

	
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
		if (ulamek >= 1)
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
		wartosc += populacja1.bity[i] / pow(2, i);
	}
	if (populacja1.x <0)
		return -1 * (1 + wartosc);
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
	int procent_krzyzowania;
	int czy_mutujemy;
	//wartosci poczatkowe
	for (int i = 0; i < Y; i++)
	{
		tmp.x = -2;
		while (tmp.x > 1 || tmp.x < -1)
		{
			tmp.x = ((double)((rand() % 20000)*10.3) - 100000.0) / 100000.0;
		}
		//cout << setprecision(20) << tmp.x;
		populacja1.push_back(tmp);
		tmp.x = 0;
		populacja2.push_back(tmp);

		//for (int j = 0; j < 40; j++)
		//cout << endl << populacja1[i].bity[j] << " jest bitem numer: " << j  << endl;
	}
	obliczWartosc(populacja1);
	sortowanie(populacja1);


	

	cout << "---------------Iteracje---------------" << endl;

	for (int i = 0; i < 200000; i++)
	{
		
		cout << "Iteracja: " << i + 1 << endl;
		for (int i = 0; i < Y; i++)
		{
			obliczRozwiniecie(populacja1[i]);
			
		}
		obliczWartosc(populacja1);
		obliczWartosc(populacja2);
		//sprawdzamy czy wartoœæ pierwszego (najlepszego) elementu jest ju¿ wystarczaj¹co bliska rozwi¹zaniu
		if (populacja1[0].wartosc >1.72)
		{
		cout << "Idealne dopasowanie: " << endl << "X =  " << populacja1[0].x << endl << "Wartosc: " << populacja1[0].wartosc;
		getchar();
		exit(1);
		}


		//tutaj do zmiennej liczba_2 jest przypisywany nr indexu osobnika ktory zostal wylosowany za pomoca metody ruletki
		//do zmiennej liczba_3 jest zapisywany index drugiego osobnika

		for (int g = 0; g < Y; g++)
		{
			liczba = (double)((rand() % 12));
			liczba_1 = (double)((rand() % 12));
			if (liczba < 5){
				liczba_2 = 1;
			}
			else if (liczba < 8){
				liczba_2 = 2;
			}
			else if (liczba < 10){
				liczba_2 = 3;
			}
			else{
				liczba_2 = 4;
			}

			if (liczba_1 < 5){
				liczba_3 = 1;
			}
			else if (liczba_1 < 8){
				liczba_3 = 2;
			}
			else if (liczba_1 < 10){
				liczba_3 = 3;
			}
			else{
				liczba_3 = 4;
			}



			//tutaj mamy juz wybrane osobniki liczba_2 i liczba_3 przechowuja ich indexy 
			//teraz krzyzowanie i zapisywanie do populacja2

			procent_krzyzowania = (double)((1 + rand() % 40));

			for (int j = 0; j < 41; j++){
				if (j < procent_krzyzowania){
					populacja2[g].bity[j] = populacja1[liczba_2 - 1].bity[j];
				}
				else{
					populacja2[g].bity[j] = populacja1[liczba_3 - 1].bity[j];
				}

			}
			czy_mutujemy = (double)((rand() % 100));
			if (czy_mutujemy < 5){
				int mutowany_bit = rand() % 40;
				if (populacja2[g].bity[mutowany_bit] == 0){
					populacja2[g].bity[mutowany_bit] = 1;
				}
				else{
					populacja2[g].bity[mutowany_bit] = 0;
				}
			}

		}



		//obliczanie wartoœci funkcji
		for (int q = 0; q < populacja2.size(); q++) {
			populacja2[q].x = obliczWartoscRozwiniecia(populacja2[q]);
		}


		obliczWartosc(populacja2);
		sortowanie(populacja1);
		cout << "Najwieksza wartosc:" << populacja1[0] << endl;
		sortowanie(populacja2);
		swap(populacja1, populacja2);
	}

}



