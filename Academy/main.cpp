﻿#include<iostream>
using namespace std;
//список принимаемых параметров HUMAN
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
//список передаваемых параметров HUMAN
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age
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
		return os << last_name << " " << first_name << age;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
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
	void set_speciality(const std::string & speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string & group)
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
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS)
		:Human(HUMAN_GIVE_PARAMETERS)
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

	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS)
		:Human(HUMAN_GIVE_PARAMETERS)
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
	std::ostream& print(std::ostream& os) const override
	{
		return Human::print(os) << " " << speciality << " " << experience;
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
		return Student::print(os) << subject;
	}
};
/*std::ostream& operator<<(std::ostream& os, const Graduate& obj)
{
	return os << (Student&)obj << " " << obj.get_subject();
}*/


//#define INHERITANCE_CHECK



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
		cout << typeid(*group[i]).name() << endl;//typeid - оператор позволяет проверить тип переменной
		//group[i]->info();

		//dinamic-cast-убедиться, что результат преобразования типов указывает на валидный завершённый объект

		if (typeid(*group[i]) == typeid(Student))cout << *dynamic_cast<Student*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Graduate))cout << *dynamic_cast<Graduate*>(group[i]) << endl;
		if (typeid(*group[i]) == typeid(Teacher))cout << *dynamic_cast<Teacher*>(group[i]) << endl;
		cout << "\n-----------------------------------\n";
	}
	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)//обращение к деструктору
	{
		delete group[i]; //если delete[] group[i] то удаляется весь массив, а так удаляется элементы 
	}
	//delete[] group; //При удалении статической памяти вылетает
	//Debug Assertion Failed
}
