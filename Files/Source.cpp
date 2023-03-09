#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

const char unit[] = {"B", "kB","MB", "GB"}

void main()
{
	setlocale(0, "");
#ifdef WRITE_TO_FILE
    ofstream fout; //1) ������ �����
	fout.open("File.txt", std::ios_base::app); //2) ��������� �����
	fout << "���� ������" << endl;
	fout << "Hello Files" << endl;//3) ����� � �����
	fout.close(); // 4) ����� ���� ��� ������ � �����
	//��������� ��� ����������� ���� �������
	system("notepad File.txt");
#endif // WRITE_TO_FILE

	std::ifstream fin("File.txt");
	cout << "��������� ������� �������: " << fin.tellg() << endl;
	fin.seekg(0, ios::end);
	int i = 0;
	int filesize = fin.tellg();
	cout << "�������� ������� �������: " << filesize << endl;
	for (; filesize > 1024; i++, filesize /= 1024);
	cout << "������ �����: " << filesize << " " << UNITI << endl;
	//fin.tellg() - tell get position (������� ������� ������������ �������)
	//�� ���������, ������������ ��� fin.getline() �������� '\n'
	
	system("PAUSE");
	if (fin.is_open())
	{
		//TODO: ����� ������ �� �����
		const int SIZE = 256;
		char sz_buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);
			cout << sz_buffer << endl;

		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
}