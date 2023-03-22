#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
//#include<math.h>
using namespace std;

namespace Geometry //пространство имен Geometry чтобы не путало с глобальными функциями расположенными в библиотеке <Windows.h>
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
		//0x - Hexadecimal (шестнадцатиричная система исчисления)
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

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
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

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

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
			if (width < limits::MIN_SIZE)width = limits::MIN_SIZE;
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

			HWND hwnd = GetConsoleWindow();//для того чтобы рисовать нужно получить окно
			HDC hdc = GetDC(hwnd); //для окна нужно получить контекст устройства
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//карандаш рисует контур фигуры
			//(стиль, ширина, цвет)
			HBRUSH hBrush = CreateSolidBrush(color);//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length); //обращаясь к глобальнуму пространству через :: и функция рисования прямоугольника
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


	class Square :public Rectangle  //квадрат
	{

	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};


		class Circle :public Shape  //круг
		{
			double radius; //радиус

		public:
			Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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

				::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

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

		class Triangle :public Shape
		{
		public:
			Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
			virtual double get_height()const = 0;
			void info()const
			{
				cout << "Высота треугольника: " << get_height() << endl;
				Shape::info();
			}
		};

		class EquilateralTriangle :public Triangle
		{
			double side;

		public:
			EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
			{
				set_side(side);
			}
			~EquilateralTriangle() {}

			double get_side()const
			{
				return side;
			}
			void set_side(double side)
			{
				if (side < limits::MIN_SIZE)side = limits::MIN_SIZE;
				if (side > limits::MAX_SIZE)side = limits::MAX_SIZE;
				this->side = side;
			}
			double get_height()const
			{
				return sqrt(pow(side, 2) - pow(side / 2, 2));
			}
			double get_area()const
			{
				return side * get_height() / 2;
			}
			double get_perimetr()const
			{
				return side * 3;
			}
			void draw()const
			{
				HWND hwnd = GetConsoleWindow();
				HDC hdc = GetDC(hwnd);
				HPEN hPen = CreatePen(PS_SOLID, line_width, color);
				HBRUSH hBrush = CreateSolidBrush(color);

				SelectObject(hdc, hPen);
				SelectObject(hdc, hBrush);

				POINT vertex[] =
				{
					{start_x, start_y + side},
					{start_x + side, start_y + side},
					{start_x + side / 2, start_y + side - get_height()}
				};

				::Polygon(hdc, vertex, 3);

				DeleteObject(hBrush);
				DeleteObject(hPen);

				ReleaseDC(hwnd, hdc);
			}
			void info()const
			{
				cout << typeid(*this).name() << endl;
				cout << "Длина стороны: " << side << endl;
				Triangle::info();
			}
		};

		class RightTrinagle :public Triangle
		{
			double side1, side2;
		public:
			RightTrinagle(double side1, double side2, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
			{
				set_side_1(side1);
				set_side_2(side2);
			}
			~RightTrinagle() {}
			double get_side_1()const
			{
				return side1;
			}
			double get_side_2()const
			{
				return side2;
			}
			void set_side_1(double side1)
			{
				if (side1 < limits::MIN_SIZE) side1 = limits::MIN_SIZE;
				if (side1 > limits::MAX_SIZE) side1 = limits::MAX_SIZE;
				this->side1 = side1;
			}
			void set_side_2(double side2)
			{
				if (side2 < limits::MIN_SIZE) side2 = limits::MIN_SIZE;
				if (side2 > limits::MAX_SIZE) side2 = limits::MAX_SIZE;
				this->side2 = side2;
			}
			double get_height()const
			{
				return side2;
			}
			double get_hypotenuse()const
			{
				return sqrt(side1 * side1 + side2 * side2);
			}
			double get_area()const
			{
				return side1 * side2 / 2;
			}
			double get_perimeter()const
			{
				return side1 + side2 + get_hypotenuse();
			}
			void draw()const
			{
				HWND hwnd = GetConsoleWindow();
				HDC hdc = GetDC(hwnd);
				HPEN hPen = CreatePen(PS_SOLID, line_width, color);
				HBRUSH hBrush = CreateSolidBrush(color);

				SelectObject(hdc, hPen);
				SelectObject(hdc, hBrush);

				POINT vertex[] =
				{
					{start_x, start_y},
					{start_x, start_y + get_height()},
					{start_x + side1, start_y + get_height()},
				};
				::Polygon(hdc, vertex, 3);

				DeleteObject(hBrush);
				DeleteObject(hPen);

				ReleaseDC(hwnd, hdc);
			}
			void info()const
			{
				cout << typeid(*this).name() << endl;
				cout << "Сторона 1:	 " << side1 << endl;
				cout << "Сторона 2:	 " << side2 << endl;
				cout << "Гипотенуза: " << get_hypotenuse() << endl;
				Triangle::info();
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

	Geometry::EquilateralTriangle eq_triangle(250, 700, 50, 10, Geometry::Color::green);
	eq_triangle.info();
	

}