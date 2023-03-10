#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	setlocale(0, "");
	const int IP_SIZE = 16;
	const int MAC_SIZE = 18;

	char sz_ip_buffer[IP_SIZE] = {};
	char sz_mac_buffer[MAC_SIZE] = {};
	char sz_filename[FILENAME_MAX] = {};
	
	
	cout << "Введите имя файла: "; cin.getline(sz_filename, FILENAME_MAX);
	if (strcmp(sz_filename + strlen(sz_filename) - 4, ".txt"))
		strcat(sz_filename, ".txt");
	/*
	int strcmp (const char* str1, const char str2);
	Функция strcmp(StringCompare) выполняет сравнение строк,
	Если strcmp() вернула 0, значит строки идентичны

	strcat(str1,str2);
	Функция strcat() выполняет конкантенацию(сложение) строк, т.е.
	в конец первой строки str1 добавляет вторую str2

	*/

	cout << sz_filename << endl;


	std::ofstream fout("201 ready.txt");
	std::ifstream fin("201 RAW.txt");//открывается если есть файл с заданным именем
	//std::ifstream fin(sz_filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;

		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	fout.close();
	char sz_command[FILENAME_MAX] = "start notepad ";
	strcat(sz_command, "201 ready.txt");

	fout.close();
	system(sz_command);
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	fout.open("201.dhcpd");
	fin.open(sz_filename);
	if (fin.is_open())
	{
		//TODO
		for (int i = 0; !fin.eof(); i++)
		{
			fin >> sz_ip_buffer >> sz_mac_buffer;

			if (strlen(sz_ip_buffer) == strlen(sz_mac_buffer))continue;
			
			for (int i = 0; sz_mac_buffer[i]; i++)
				if (sz_mac_buffer[i] == '-')sz_mac_buffer[i] = ':';

			cout << "host-" << i + 1 << endl;
			cout << "{\n";
			cout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			cout << "\tfixed-address:\t\t" << sz_ip_buffer << ";\n";
			cout << "}\n";
			cout << endl;


			fout << "host-" << i + 1 << endl;
			fout << "{\n";
			fout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			fout << "\tfixed-address:\t\t" << sz_ip_buffer << ";\n";
			fout << "}\n";
			fout << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	fout.close();
	system("notepad 201.dhcpd");



}
