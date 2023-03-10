#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

const char* UNITS[] = { "B", "kB","MB", "GB" };

void main()
{
	setlocale(0, "");
	setlocale(LC_ALL, "");
	cout << "Hello World";
	cout << endl;
	//https://legacy.cplusplus.com/doc/tutorial/files/
#ifdef WRITE_TO_FILE

	/*name_file[256];
	cout << "Введите имя файла: \n";
	cin >> name_file;

	if ()//во введённом имени нет .txt делаем name_file = 'name_file'+'.txt'

	ofstream fout;
	fout.open(name_file, std::ios_base::app); 
	fout << "Всем привет" << endl;
	fout << "Hello Files" << endl;//3) Пишем в поток
	fout.close(); // 4) После того как запись в поток*/

    //1) Создаём поток
	fout.open("File.txt", std::ios_base::app); //2) Открываем поток
	fout << "Всем привет" << endl;
	fout << "Hello Files" << endl;//3) Пишем в поток
	fout.close(); // 4) После того как запись в поток
	//выполнена его обязательно надо закрыть
	system("notepad File.txt");
#endif // WRITE_TO_FILE


#ifdef READ_FROM_FILE
	std::ifstream fin("File.txt");
	cout << "Начальная позиция курсора: " << fin.tellg() << endl;
	fin.seekg(0, ios::end);
	int i = 0;
	int filesize = fin.tellg();
	cout << "Конечная позиция курсора: " << filesize << endl;
	for (; filesize > 1024; i++, filesize /= 1024);
	cout << "Размер файла: " << filesize << " " << UNITS[i] << endl;
	//fin.tellg() - tell get position (говорит позицию считывающего курсора)
	//по умолчанию, разделителем для fin.getline() является '\n'
	
	system("PAUSE");
	if (fin.is_open())
	{
		//TODO: будем читать из файла
		const int SIZE = 256;
		char sz_buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);//getline() позволяет ввести строку с пробелами, до заданного разделителя
			//по умолчанию, разделителем для fin.getline() является '\n'
			cout << sz_buffer << endl;

		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif  // READ_FROM_FILE
}