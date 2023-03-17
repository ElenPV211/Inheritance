#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

namespace Geometry //пространство имен Geometry чтобы не путало в
{
	enum limits
	{
		MIN_SIZE = 50,
		MAX_SIZE = 500,
		MIN_LINE_WIDTH = 1,
		MAX_LINE_WIDTH = 30,
		MIN_START_X = 100,
		MAX_START_X = 1000,
		MIN_START_Y = 100,
		MAX_START_Y = 700
	}; 
	enum Color
	{
		//0x - 
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x00FFFF,
		white = 0x00FFFFFF
	};
#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x,start_y,line_width, color

	class Shape
	{
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color;
	public:

		Shape(SHAPE_TAKE_PARAMETERS):color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape()
		{		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		void set_start_x(int start_x)
		{
			if (start_x < limits::MIN_START_X)start_x = limits::MIN_START_X;
			if (start_x > limits::MAX_START_X)start_x = limits::MAX_START_X;
			this->start_x = start_x;
		
		}
		void set_start_y(int start_y)
		{
			if (start_y < limits::MIN_START_Y)start_y = limits::MIN_START_Y;
			if (start_y > limits::MAX_START_Y)start_y = limits::MAX_START_Y;
			this->start_y = start_y;

		}
		void set_line_width(int line_width)
		{
			if (line_width < limits::MIN_LINE_WIDTH)line_width = limits::MIN_LINE_WIDTH;
			if (line_width > limits::MAX_LINE_WIDTH)line_width = limits::MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		virtual double get_area()const = 0;//как посчитать площадь геометрической фигуры
		virtual double get_perimetr()const = 0;//периметр
		virtual void draw()const = 0;//как нарисовать фигуру мы не знаем поэтому виртуальный метод
		virtual void info()const
		{
			cout << "Площадь фигуры:" << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimetr() << endl;
			draw();
		}
	};

	class Square :public Shape  //квадрат
	{
		double side; //сторона
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);//в конструкторе вызываем set метод который уже фильтрует данные 
		}
		~Square() {}

		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			//условия чтобы мы отфильтровать все ненужные значения
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;

		}
		double get_perimetr()const override
		{
			return side * 4;
		}

		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << side << endl;
			Shape::info();
		}
	};
	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle()
		{

		}

		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length < limits::MIN_SIZE)length = limits::MIN_SIZE;
			if (length > limits::MAX_SIZE)length = limits::MAX_SIZE;
			this->length = length;
		}
		void set_width(double width)

		{
			if (width <  limits::MIN_SIZE)width = limits::MIN_SIZE;
			if (width > limits::MAX_SIZE)width = limits::MAX_SIZE;
			this->width = width;
		}

		double get_area()const override
		{
			return length * width;
		}
		double get_perimetr()const override
		{
			return (length + width) * 2;
		}
		void draw()const override
		{
			/*for (int i = 0; i < width; i++)
			{
			for (int j = 0; j < length; j++)
			{
			cout << "* ";
			}
			cout << endl;
			}*/
			HWND hwnd = GetConsoleWindow();//для того чтобы рисовать нужно получить окно
			HDC hdc = GetDC(hwnd); //для окна нужно получить контекст устройства
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//карандаш рисует контур фигуры
			//(стиль, ширина, цвет)
			HBRUSH hBrush = CreateSolidBrush(color);//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			::Rectangle(hdc, start_x, start_y, start_x+width, start_y+length); //обращаясь к глобальнуму пространству через :: и функция рисования прямоугольника
				//координаты верхнего левого угла и две координаты нижнего правого угла

				DeleteObject(hBrush); //удаляем после использования
			DeleteObject(hPen);
			this;
			ReleaseDC(hwnd, hdc);//контекст устройства занимает некоторое место, поэтому пока он не нужен его нужно освободить
				//параметры hwnd окно, hdc - устройство
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Высота прямоугольника: " << length << endl;
			cout << "Ширина прямоугольника: " << width << endl;
			Shape::info();
		}
	};

	/*class Triangle :public Shape  //треугольник
	{
		double sideA; //сторона A
		double sideB; //сторона B
		double sideC; //сторона C

	public:


		Triangle(double sideA, double sideB, double sideC)
		{
			set_sideA(sideA);
			set_sideB(sideB);
			set_sideC(sideC);
		}
		~Triangle()
		{}

		double get_sideA()const
		{
			return sideA;
		}
		double get_sideB()const
		{
			return sideB;
		}
		double get_sideC()const
		{
			return sideC;
		}

		void set_sideA(double sideA)
		{
			if (sideA < 3)sideA = 3;
			if (sideA > 20)sideA = 20;
			this->sideA = sideA;
		}

		void set_sideB(double sideB)
		{
			if (sideB < 3)sideB = 3;
			if (sideB > 20)sideB = 20;
			this->sideB = sideB;
		}

		void set_sideC(double sideC)
		{
			if (sideC < 3)sideC = 3;
			if (sideC > 20)sideC = 20;
			this->sideC = sideC;
		}

		double get_area()const override
		{
			return sqrt(get_perimetr() * (get_perimetr() - sideA) * (get_perimetr() - sideB) * (get_perimetr() - sideC));
		}
		double get_perimetr()const override
		{
			double perimetr = (sideA + sideB + sideC) / 2;

			return perimetr;
		}

		void draw()const override
		{
			double h; //высота треугольника
			h = 2 / sideA * (get_perimetr());

			cout << "Высота треугольника: " << h << endl;

			for (int i = 0; i < h; i++)
			{
				for (int j = 1; j < h - i; j++) cout << ' ';
				for (int j = h - i; j <= h; j++) cout << "* ";

				cout << endl;
			}

			//*BOOL WINAPI Polygon(
			//	HDC hdc,             // идентификатор контекста отображения
			//	const POINT FAR * lppt,// указатель на массив структур POINT
			//	int cPoints);         // размер массива
			
			HWND hwnd = GetConsoleWindow();//для того чтобы рисовать нужно получить окно
			HDC hdc = GetDC(hwnd); //для окна нужно получить контекст устройства
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(205, 92, 92));//карандаш рисует контур фигуры
			//(стиль, ширина, цвет(код цвета)
			HBRUSH hBrush = CreateSolidBrush(RGB(205, 92, 92));//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			POINT points[] =
			{
				{50, 150},
				{150, 50},
				{250, 150}
			};

			::Polygon(hdc, points, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длины сторон треугольника: ";
			cout << " A = " << sideA << " B = " << sideB;
			cout << " C = " << sideC << endl;
			Shape::info();
		}
	};
*/
	class Circle :public Shape  //круг
	{
		double radius; //радиус

	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}

		double get_radius()const
		{
			return this->radius;
		}
		void set_radius(double radius)
		{
			if (radius < limits::MIN_SIZE)radius = limits::MIN_SIZE;
			if (radius > limits::MAX_SIZE)radius = limits::MAX_SIZE;
			this->radius = radius;
		}
		double get_area()const override
		{
			return M_PI * pow(radius, 2);

		}
		double get_perimetr()const override
		{
			return 2 * radius * M_PI;
		}

		void draw()const override
		{
			
			HWND hwnd = GetConsoleWindow();//для того чтобы рисовать нужно получить окно
			HDC hdc = GetDC(hwnd); //для окна нужно получить контекст устройства
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//карандаш рисует контур фигуры
			//(стиль, ширина, цвет(код цвета)
			HBRUSH hBrush = CreateSolidBrush(color);//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			::Ellipse(hdc, start_x, start_y, start_x+2*radius, start_y+2*radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << radius << endl;
			Shape::info();
		}
	};
}


void main()

{
	setlocale(0, "");
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD coord;
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	Geometry::Square square(8, 100, 100, 5, Geometry::Color::blue);
	square.info();
	cout << "\n";

	Geometry::Rectangle rect(50, 60, 200,100,5, Geometry::Color::red);
	rect.info();
	cout << "\n";

	//Geometry::Triangle trian(5, 3, 6);
	//trian.info();
	//cout << "\n";

	Geometry::Circle circle(30,  250,50,5, Geometry::Color::blue);
	circle.info();
}