#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;



class Liczba 
{
public:
	double x;
	double wartosc;
	friend ostream & operator<< (ostream &wyjscie, const Liczba &s);
	double obliczWartosc(double x);
};

ostream & operator<< (ostream &wyjscie, const Liczba &s) 
{
	return wyjscie << "X: " << s.x << " wartosc:" << s.wartosc << endl;
}

double Liczba::obliczWartosc(double x)
{
	return (x*x*x)- (x *x) + sin(4 * x) - cos(15 * x)
}



void swap(vector<Liczba>& vec);

bool mniejsze(Liczba PierwszyLiczba, Liczba DrugiLiczba) //funkcja mówi¹ca który element i w jakim wypadku jest mniejszy od drugiego
{
	return PierwszyLiczba.wartosc < DrugiLiczba.wartosc;
}

void sortowanie(vector <Liczba> &populacja1)
{
	//cout << "------------------Sortowanie----------------------" << endl;
	sort(populacja1.begin(), populacja1.end(), mniejsze);


	cout << "najmniejszy wartosc:" << populacja1[0] << endl;
	

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
		for (int j = 0; j < ILOSC; j++) {
			tmp.x += (rand() % 94) + 32;
		}
		populacja1.push_back(tmp);
		tmp.x = "";
		populacja2.push_back(tmp);
	}

	//obliczanie fitnesu
	for (int i = 0; i < populacja1.size(); i++) {
		populacja1[i].wartosc = 0;
		for (int j = 0; j < ILOSC; j++) {
			populacja1[i].wartosc += abs(int(populacja1[i].x[j] - X[j]));
		}
	}
	// getchar();
	sortowanie(populacja1);

	cout << "---------------Iteracje---------------" << endl;

for (int i = 0; i < 200000; i++)
{
	cout << "Iteracja: " << i + 1 << endl;

		/*
		for (int i = 0; i < populacja1.size(); i++)
		{
		cout << populacja1[i] << endl;
		}
		*/



	if (populacja1[0].wartosc == 0)
		{
			cout << "Idealne dopasowanie: " << endl << "Nazwa: " << populacja1[0].x << endl << " Fitness: " << populacja1[0].wartosc;
			getchar();
			exit(1);
		}


		//kopiowanie 5% do nowej populacji
	//cout << "------------------Kopiowanie 5%----------------------" << endl;
	for (int i = 0; i < 102; i++)
		{
			populacja2[i].x = populacja1[i].x;
			populacja2[i].wartosc = populacja1[i].wartosc;
			//cout << populacja2[i] << endl;
		}
	// getchar();


	//cout << "------------------ Kry¿owanie ----------------------" << endl;
		//krzyzowanie
	for (int i = 0; i < 200; i++)
	{
		int osobnik1 = (rand() % 2048 - 103) + 103;
		int osobnik2 = (rand() % 2048 - 103) + 103;
		int wspolczynnik_podzialu = (rand() % ILOSC-1) + 1;
			//cout << osobnik1 << ", " << osobnik2 << "," << wspolczynnik_podzialu;
		string tmp = populacja1[osobnik1].x.substr(0, wspolczynnik_podzialu);
		string tmp1 = populacja1[osobnik2].x.substr(wspolczynnik_podzialu, ILOSC);
		populacja2[i + 102].x = tmp + tmp1;
		//cout << "Krzyzowanie: " << populacja2[i + 102].x << endl;

			//mutacja
		int mutacja = (rand() % 101);
		
		if (mutacja < 5)
		{
			//cout << "------------------ Mutacja ----------------------" << endl;
			int numer_mutacji = (rand() % ILOSC-1) + 1;
			tmp = populacja2[i + 102].x.substr(0, numer_mutacji - 1);
			tmp1 = populacja2[i + 102].x.substr(numer_mutacji, ILOSC);
			char znak = (rand() % 94) + 32;
			populacja2[i + 102].x = tmp + znak + tmp1;
			//cout << populacja2[i + 102].x << endl;
		}
	}

		//wygenerowanie reszty osobników
	for (int i = 302; i < Y; i++)
	{
		Liczba tmp;
		for (int j = 0; j < ILOSC; j++) 
		{
			tmp.x += (rand() % 94) + 32;
		}
			populacja2[i].x = tmp.x;
		//	cout << populacja2[i].x << "   " << populacja2[i].wartosc << endl;
	}
	//	getchar();

		//obliczanie fitnesu
	for (int i = 0; i < populacja2.size(); i++) 
	{
		populacja2[i].wartosc = 0;
		for (int j = 0; j < ILOSC; j++) 
		{
			populacja2[i].wartosc += abs(int(populacja2[i].x[j] - X[j]));
		}
	}
	//getchar();

	sortowanie(populacja2);
	swap(populacja1, populacja2);
}

}



