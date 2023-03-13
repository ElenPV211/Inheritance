#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//список принимаемых параметров HUMAN
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
//список передаваемых параметров HUMAN
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

enum allignment
{
	last_name_width = 15,
	first_name_width = 10,
	age_width = 5,
	speciality_width = 25,
	numeric_width = 8
};

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}
	///------------------Constractors:-----------------//
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(allignment::last_name_width);
		ofs << left;
		ofs << last_name;
		ofs.width(allignment::first_name_width);
		ofs << first_name;
		ofs.width(allignment::age_width);
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& scan(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}

};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}

std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	return obj.scan(ifs);
}


#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
//---------------------------------------------------
class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;

public:

	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}
	//---------------Constructors:---------------///
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//-----------------Metods:--------------------------//
	void info()const
	{
		Human::info(); // ссылаемся на родительский класс
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}

	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(allignment::speciality_width);
		ofs << left;
		ofs << speciality;
		ofs.width(allignment::numeric_width);
		ofs << group;
		ofs.width(allignment::numeric_width);
		ofs << rating;
		ofs.width(allignment::numeric_width);
		ofs << attendance;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		char sz_buffer[allignment::speciality_width] = {};
		ifs.read(sz_buffer, allignment::speciality_width - 1);	//ìåòîä read() ÷èòàåò çàäàííîå êîëè÷åñòâî Áàéò èç ôàéëà
		for (int i = allignment::speciality_width - 2; sz_buffer[i] == ' '; i--)
			sz_buffer[i] = 0;
		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++)sz_buffer[i] = sz_buffer[i + 1];
		speciality = sz_buffer;
		ifs >> group;
		ifs >> rating;
		ifs >> attendance;
		return ifs;
	}

};
/*std::ostream& operator<<(std::ostream& os, const Student& obj)
{
	return os << (Human&)obj << " " << obj.get_speciality() << " " << obj.get_group() << " " << obj.get_rating() << " " << obj.get_attendance();
}*/


//-----------------------------------------------------------

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, double experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher : public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(double experience)
	{
		this->experience = experience;
	}

	//----------Constractors:----------------------//

	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS)	:Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//------------Metods:---------------------------//
	void info()const
	{
		Human::info();
		cout << speciality << " " << experience << " лет.\n";
	}
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << experience;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(allignment::speciality_width);
		ofs << speciality;
		ofs.width(allignment::numeric_width);
		ofs << experience;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		char sz_buffer[allignment::speciality_width] = {};
		ifs.read(sz_buffer, allignment::speciality_width - 1);
		for (int i = allignment::speciality_width - 2; sz_buffer[i] == ' '; i--)sz_buffer[i] = 0;
		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++)sz_buffer[i] = sz_buffer[i + 1];
		speciality = sz_buffer;
		ifs >> experience;
		return ifs;
	}

};

/*std::ostream& operator<<(std::ostream& os, const Teacher& obj)
{
	return os << (Human&)obj << " " << obj.get_speciality() << " " << obj.get_experience();
}*/
//--------------------------------------------------------

#define GRADUATE_TAKE_PARAMETRS const std::string& subject
#define GRADUATE_GIVE_PARAMETRS subject
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}

	//--------------Constractors:-------------------//
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETRS
	) : Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	void info()const
	{
		Student::info();
		cout << subject << endl;
	}
	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os) << " " << subject;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs << subject;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)
	{
		Student::scan(ifs);
		std::getline(ifs, subject);
		return ifs;
	}

};
/*std::ostream& operator<<(std::ostream& os, const Graduate& obj)
{
	return os << (Student&)obj << " " << obj.get_subject();
}*/

Human* HumanFactory(const std::string& type)
{
	if (type.find("Student") != std::string::npos)return new Student("", "", 0, "", "", 0, 0);
	if (type.find("Graduate") != std::string::npos)return new Graduate("", "", 0, "", "", 0, 0, "");
	if (type.find("Teacher") != std::string::npos)return new Teacher("", "", 0, "", 0);
}




void save(Human** group, const int n, const char* filename)
// функция принимающая ссылка на ссылку группы, размер этой группы и имя файла

{
	std::ofstream fout(filename);      //создаём файл, если так std::ofstream& fout(filename);
	//то ошибка т.к. пытаемся создать ссылку, надо без &

	for (int i = 0; i < n; i++) // выполняем запись в цикле
	{
		fout << typeid(*group[i]).name() << ":\t";//tipeid для того, чтобы мы могли различать участников группы,
        // понимать объект какого класса нужно нам создать когда мы будем загружать.
		fout << *group[i] << endl;  // *group[i] каждый участник группы будет занимать отдельную строку
	}
	fout.close();
	std::string s_command = "start notepad "; //запустить блокнот
	s_command += filename;
	system(s_command.c_str());//s_command является объектом класса std striam
	//system не знает, что такое string и чтобы из него достать обычную raw
	//строку есть метод c_str()
}

Human** load(const char* filename, int& n)
{
	Human** group = nullptr;	//Åñëè ôàéë íåáûë íàéäåí, òî ãðóïïà íå ñîçäàíà
	n = 0;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Îïðåäåëÿåì êîëè÷åñòâî ñòðîê â ôàéëå:
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			if (buffer.empty())continue;
			n++;
		}

		//2) Âûäåëÿåì ïàìÿòü ïîä îáúåêòû. Êàæäûé îáúåêò çàíèìàåò îòäåëüíóþ ñòðîêó â ôàéëå.
		group = new Human * [n] {};

		//3) Âîçâðàùàåìñÿ â íà÷àëî ôàéëà, äëÿ òîãî ÷òîáû ïðî÷èòàòü åãî åùå ðàç:
		cout << "Ïîçèöèÿ êóðñîðà â ôàéëå: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);	//seekg() çàäàåò get-ïîçèöèþ êóðñîðà (get - âçÿòü, ïðî÷èòàòü)
		cout << "Ïîçèöèÿ êóðñîðà â ôàéëå: " << fin.tellg() << endl;

		//4) Âûïîëíÿåì ïîâòîðíîå ÷òåíèå:
		std::string obj_type;
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, obj_type, ':');
			fin.ignore();
			if (obj_type.empty())continue;
			group[i] = HumanFactory(obj_type);
			fin >> *group[i];
		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}

	return group;
}

//#define INHERITANCE_CHECK
#define POLIMORFISM //(многоформенность)
//#define READ_FROM_FILE


void main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE_CHECK
	Human human("Тупенко", "Василий", 20);
	human.info();

	Student student("Иванов", "Иван", 18, "IT", "PV211", 12, 100);
	student.info();

	Teacher teacher("Einstein", "Albert", 143, "Astronomiy", 110);
	teacher.info();

	Graduate graduate("Петров", "Николай", 21, "IT", "PV_211", 10, 80, "Организация безопасности");
	graduate.info();
#endif //INHERITANCE_CHECK

#ifdef POLIMORFISM
	//-----------Generalisation (UpCast)---
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 89, 92),
		new Teacher("Whaite", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "OBN", 95, 75,"How to catch Heizenberg"),
		new Student("Vercetti", "Tomas", 30, "Criminalistic", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};

	cout << sizeof(group) / sizeof(group[0]) << endl;

	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		//typeid - оператор позволяет проверить тип переменной
		cout << typeid(*group[i]).name() << endl;
		//group[i]->info();
			//dinamic-cast-убедиться, что результат преобразования типов указывает на валидный завершённый объект
		/*if (typeid(*group[i]) == typeid(Student))cout << *dynamic_cast<Student*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Graduate))cout << *dynamic_cast<Graduate*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Teacher))cout << *dynamic_cast<Teacher*>(group[i]) << endl;
*/
		cout << *group[i] << endl;
		cout << "\n---------------------------------\n";
	}
	save(group, sizeof(group) / sizeof(group[0]), "group.txt");

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++) //обращение к деструктору
	{
		delete group[i]; //если delete[] group[i] то удаляется весь массив, а так удаляется элементы 
	}
#endif // POLIMORFISM

#ifdef READ_FROM_FILE
	int n = 0;	//Ðàçìåð ãðóïïû. Áóäåò âû÷èñëåí ôóíêöèåé load()
	Human** group = load("group.txt", n);
	cout << "\n-----------------------------------------\n";
	for (int i = 0; i < n; i++)
	{
		cout << *group[i] << endl;
		cout << "\n-----------------------------------------\n";
	}
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
	delete[] group;
#endif // READ_FROM_FILE

}


