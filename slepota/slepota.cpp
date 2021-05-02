// slepota.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include<clocale>
#include <vector>
using namespace std;

ofstream fout("Расчет времени.txt");


vector<double> input(int n, const char* text)
{
	cout << text << endl;

	vector<double> output;

	double c = 0;
	for (int i = 0; i < n; i++)
	{
		cout << "[" << i << "]: ";
		cin >> c;
		output.push_back(c);
	}

	fout << text;
	for (double elem : output)
		fout << elem << ", ";

	fout << endl;

	cout << endl;

	return output;
}

double sum_dol(vector<double> slag, vector<double>dol, int nach, int konets)
{
	double s = 0;

	for (int i = nach; i < konets; i++)
		s += slag[i] * dol[i];

	return s;
}

vector<double> vremyaBezLech(double i_vozr0, double i_vozr1, vector<double> t)
{
	vector<double> vremyaBez = { i_vozr0, i_vozr1 };
	double time = i_vozr1;

	for (size_t i = 1; i < 4; i++)
		vremyaBez.push_back(vremyaBez[i]+t[i]);

	return vremyaBez;
}

vector<double> sv(vector<double>vremyaBez, vector<double>lech, int konets)
{
	vector<double> s;

	for (int i = 0; i < konets; i++)
	{
		double t = vremyaBez[i];
		for (int j = 0; j < konets; j++)
			t += lech[j];

		s.push_back(t);
	}

	return s;
}


int main()
{

    setlocale(0, "");
	string name;
	double i_vozr0, i_vozr1; //истинные возрасты
	double prodZhizn, svns, svuz;
    vector<double> lech;
	vector<double> t;
	vector<double> dolya;
	vector<double> vremyaBez;
	vector<double> slep, uhud;
	bool start = true;

	while (start)
	{

		cout << "Введите истинный возраст нулевой и первой стадии: " << endl;
		cout << "[0]: ";
		cin >> i_vozr0;

		cout << "[1]: ";
		cin >> i_vozr1;
		cout << endl;
		//вывод в файл
		fout << "Истинные возрасты нулевой и первой стадии: " << i_vozr0 << ", " << i_vozr1 << endl;

		cout << "Введите среднюю продолжительность жизни: ";
		cin >> prodZhizn;
		fout << "Средняя продолжительность жизни: " << prodZhizn << endl;


		t = input(4, "Время прохождения стадий без лечения: ");

		cout << "Введите название технологии лечения: ";
		cin >> name;
		fout << "Технология лечения: " << name << endl;

		lech = input(4, "Среднее время при лечении: "); //в зависимости от технологии
		dolya = input(4, "Укажите доли по стадиям (если не известна, ставьте 0): ");

		vremyaBez = vremyaBezLech(i_vozr0, i_vozr1, t); //Время без лечения
		cout << "Время наступления слепоты без лечения: " << vremyaBez[4] << endl;
		fout << "Время наступления слепоты без лечения: " << vremyaBez[4] << endl;

		slep = sv(vremyaBez, lech, 4);
		uhud = sv(vremyaBez, lech, 3);

		int nach = 0;

		if (i_vozr0 < 1) nach = 1;

		svns = sum_dol(slep, dolya, nach, 4);
		svuz = sum_dol(slep, dolya, nach, 3);

		double ost_slep, ost_uhud;
		ost_slep = svns - prodZhizn;
		ost_uhud = svuz - prodZhizn;

		if (ost_slep > 0)
		{
			cout << "Человек не слепнет до смерти." << endl;
			fout << "Человек не слепнет до смерти." << endl;
			cout << "Запас продолжительности жизни " << ost_slep << " лет" << endl;
			fout << "Запас продолжительности жизни " << ost_slep << " лет" << endl;
		}
		else
		{
			cout << "Человек слепнет раньше, чем умирает на " << -ost_slep << " лет" << endl;
			fout << "Человек слепнет раньше, чем умирает на " << -ost_slep << " лет" << endl;
		}

		if (ost_uhud > 0)
		{
			cout << "Запас времени без ухудшения зрения " << ost_uhud << " лет" << endl;
			fout << "Запас времени без ухудшения зрения " << ost_uhud << " лет" << endl;
		}
		else
		{
			cout << "Зрения человека ухудшается до его смерти за " << -ost_uhud << " лет" << endl;
			fout << "Зрения человека ухудшается до его смерти за " << -ost_uhud << " лет" << endl;
		}

		cout << "Хотите продолжить? Да - 1, Нет - 0: ";
		bool choice;
		cin >> choice;

		if (!choice)
		{
			start = false;
			break;
		}

		cout << "---" << endl;
		fout << "---" << endl;

	}

    fout.close();

    return 0;
}
