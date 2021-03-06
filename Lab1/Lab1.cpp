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


void obliczWartosc(vector <Liczba> &populacja1)  //obliczanie warto�ci podanej funkcji dla wylosowanego x
{
	double x;
	for (int i = 0; i < Y; i++)
	{
		x = populacja1[i].x;
		populacja1[i].wartosc=(x*x*x) - (x *x) + sin(4 * x) - cos(15 * x);
	}

	
}

void obliczRozwiniecie(Liczba &populacja1)	//obliczanie rozwiniecia bitowego dla wylosowanego x
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
	
double obliczWartoscRozwiniecia(Liczba &populacja1)		//obliczanie wartosci x z rozwini�cia bitowego
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

bool wieksze(Liczba PierwszaLiczba, Liczba DrugaLiczba) //funkcja m�wi�ca kt�ry element i w jakim wypadku jest wiekszy
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
			tmp.x = ((double)((rand() % 20000)*10000.3634) - 100000000.0) / 100000000.0;		//losowanie
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

	for (int i = 0; i < 200000; i++)		//g��wna p�tla 
	{
		
		cout << "Iteracja: " << i + 1 << endl;
		for (int i = 0; i < Y; i++)
		{
			obliczRozwiniecie(populacja1[i]);
			
		}
		obliczWartosc(populacja1);
		obliczWartosc(populacja2);

		//sprawdzamy czy warto�� pierwszego (najlepszego) elementu jest ju� wystarczaj�co bliska rozwi�zania
		if (populacja1[0].wartosc >1.72)
		{
		cout << "Idealne dopasowanie: " << endl << "X =  " << populacja1[0].x << endl << "Wartosc: " << populacja1[0].wartosc;
		getchar();
		exit(1);
		}


		//tutaj do zmiennej liczba_2 jest przypisywany nr indexu osobnika ktory zostal wylosowany za pomoca metody ruletki
		//do zmiennej liczba_3 jest zapisywany index drugiego osobnika
		sortowanie(populacja1);
		sortowanie(populacja2);
		for (int g = 0; g < Y; g++)
		{
			liczba = (double)((rand() % 55));
			liczba_1 = (double)((rand() % 55));
			if (liczba < 20){
				liczba_2 = (rand() % 10);
			}
			else if (liczba < 35){
				liczba_2 = 9 + (rand() % 40);
			}
			else if (liczba < 45){
				liczba_2 = 48 + (rand() % 30);
			}
			else{
				liczba_2 = 73+(rand() % 25);
			}

			if (liczba_1 < 20){
				liczba_3 = (rand() % 10);
			}
			else if (liczba_1 < 35){
				liczba_3 = 9 + (rand() % 40);
			}
			else if (liczba_1 < 45){
				liczba_3 = 48 + (rand() % 30);
			}
			else{
				liczba_3 = 73+(rand() % 25);
			}



			//tutaj mamy juz wybrane osobniki liczba_2 i liczba_3 przechowuja ich indexy 
			//teraz krzyzowanie i zapisywanie do populacja2

			procent_krzyzowania = (double)((1 + rand() % 39));

			for (int j = 1; j < 41; j++){
				if (j < procent_krzyzowania){
					populacja2[g].bity[j] = populacja1[liczba_2].bity[j];
				}
				else{
					populacja2[g].bity[j] = populacja1[liczba_3].bity[j];
				}

			}
			//losujemy % na mutacj�, je�li mniejszy od 5 to mutujemy, je�li nie zostawiamy
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



		//obliczanie warto�ci funkcji
		for (int q = 0; q < populacja2.size(); q++) {
			populacja2[q].x = obliczWartoscRozwiniecia(populacja2[q]);
			populacja1[q].x = obliczWartoscRozwiniecia(populacja1[q]);
		}

		obliczWartosc(populacja1);
		obliczWartosc(populacja2);
		sortowanie(populacja1);
		//cout << "Najwieksza wartosc:" << populacja1[0] << endl;
		sortowanie(populacja2);
		
		swap(populacja1, populacja2);
	}

}



