// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;
#define X "Lubie Wd"
#define Y 2048
#define ILOSC 8

class Osobnik 
{
public:
	string chromosom;
	unsigned int fitness;
	friend ostream & operator<< (ostream &wyjscie, const Osobnik &s);
};

ostream & operator<< (ostream &wyjscie, const Osobnik &s) 
{
	return wyjscie << "Nazwa: " << s.chromosom << " fitness:" << s.fitness << endl;
}



void swap(vector<Osobnik>& vec);

bool mniejsze(Osobnik PierwszyOsobnik, Osobnik DrugiOsobnik) //funkcja mówi¹ca który element i w jakim wypadku jest mniejszy od drugiego
{
	return PierwszyOsobnik.fitness < DrugiOsobnik.fitness;
}

void sortowanie(vector <Osobnik> &populacja1)
{
	//cout << "------------------Sortowanie----------------------" << endl;
	sort(populacja1.begin(), populacja1.end(), mniejsze);

	/*for (int i = 0; i < populacja1.size(); i++)
	{
		cout << populacja1[i] << endl;
	}*/
	cout << "najmniejszy fitness:" << populacja1[0] << endl;
	
	//getchar();
}

int main()
{

	//inicjalizacja populacji (2 wektory)
	vector<Osobnik> populacja1;
	vector<Osobnik> populacja2;
	srand(time(NULL));

	//wartosci poczatkowe
	for (int i = 0; i < Y; i++) 
	{
		Osobnik tmp;
		for (int j = 0; j < ILOSC; j++) {
			tmp.chromosom += (rand() % 94) + 32;
		}
		populacja1.push_back(tmp);
		tmp.chromosom = "";
		populacja2.push_back(tmp);
	}

	//obliczanie fitnesu
	for (int i = 0; i < populacja1.size(); i++) {
		populacja1[i].fitness = 0;
		for (int j = 0; j < ILOSC; j++) {
			populacja1[i].fitness += abs(int(populacja1[i].chromosom[j] - X[j]));
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



	if (populacja1[0].fitness == 0)
		{
			cout << "Idealne dopasowanie: " << endl << "Nazwa: " << populacja1[0].chromosom << endl << " Fitness: " << populacja1[0].fitness;
			getchar();
			exit(1);
		}


		//kopiowanie 5% do nowej populacji
	//cout << "------------------Kopiowanie 5%----------------------" << endl;
	for (int i = 0; i < 102; i++)
		{
			populacja2[i].chromosom = populacja1[i].chromosom;
			populacja2[i].fitness = populacja1[i].fitness;
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
		string tmp = populacja1[osobnik1].chromosom.substr(0, wspolczynnik_podzialu);
		string tmp1 = populacja1[osobnik2].chromosom.substr(wspolczynnik_podzialu, ILOSC);
		populacja2[i + 102].chromosom = tmp + tmp1;
		//cout << "Krzyzowanie: " << populacja2[i + 102].chromosom << endl;

			//mutacja
		int mutacja = (rand() % 101);
		
		if (mutacja < 5)
		{
			//cout << "------------------ Mutacja ----------------------" << endl;
			int numer_mutacji = (rand() % ILOSC-1) + 1;
			tmp = populacja2[i + 102].chromosom.substr(0, numer_mutacji - 1);
			tmp1 = populacja2[i + 102].chromosom.substr(numer_mutacji, ILOSC);
			char znak = (rand() % 94) + 32;
			populacja2[i + 102].chromosom = tmp + znak + tmp1;
			//cout << populacja2[i + 102].chromosom << endl;
		}
	}

		//wygenerowanie reszty osobników
	for (int i = 302; i < Y; i++)
	{
		Osobnik tmp;
		for (int j = 0; j < ILOSC; j++) 
		{
			tmp.chromosom += (rand() % 94) + 32;
		}
			populacja2[i].chromosom = tmp.chromosom;
		//	cout << populacja2[i].chromosom << "   " << populacja2[i].fitness << endl;
	}
	//	getchar();

		//obliczanie fitnesu
	for (int i = 0; i < populacja2.size(); i++) 
	{
		populacja2[i].fitness = 0;
		for (int j = 0; j < ILOSC; j++) 
		{
			populacja2[i].fitness += abs(int(populacja2[i].chromosom[j] - X[j]));
		}
	}
	//getchar();

	sortowanie(populacja2);
	swap(populacja1, populacja2);
}

}



