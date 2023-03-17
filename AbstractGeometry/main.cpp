#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

namespace Geometry //пространство имен Geometry чтобы не путало в
{
	class Shape
	{
	public:
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
		Square(double side)
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
		Rectangle(double width, double length)
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
			if (length < 3)length = 3;
			if (length > 20)length = 20;
			this->length = length;
		}
		void set_width(double width)

		{
			if (width < 3)width = 3;
			if (width > 20)width = 20;
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
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 215, 0));//карандаш рисует контур фигуры
			//(стиль, ширина, цвет)
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 215, 0));//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			::Rectangle(hdc, 50, 50, 400, 300); //обращаясь к глобальнуму пространству через :: и функция рисования прямоугольника
				//координаты верхнего левого угла и две координаты нижнего правого угла

				DeleteObject(hBrush); //удаляем после использования
			DeleteObject(hPen);

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

	class Triangle :public Shape  //треугольник
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

	class Circle :public Shape  //круг
	{
		double rad; //радиус

	public:
		Circle(double rad)
		{
			set_rad(rad);
		}
		~Circle() {}

		double get_rad()const
		{
			return rad;
		}
		void set_rad(double rad)
		{
			if (rad < 5)rad = 5;
			if (rad > 20)rad = 20;
			this->rad = rad;
		}
		double get_area()const override
		{
			return 3.14 * pow(rad, 2);

		}
		double get_perimetr()const override
		{
			return 2 * rad * 3.14;
		}

		void draw()const override
		{
			int POINT[3] = {};

			HWND hwnd = GetConsoleWindow();//для того чтобы рисовать нужно получить окно
			HDC hdc = GetDC(hwnd); //для окна нужно получить контекст устройства
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));//карандаш рисует контур фигуры
			//(стиль, ширина, цвет(код цвета)
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));//кисть

			SelectObject(hdc, hPen); //выбираем карандаш
			SelectObject(hdc, hBrush);//выбираем кисть

			::Ellipse(hdc, 200, 200, 300, 300);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << rad << endl;
			Shape::info();
		}
	};
}


void main()

{
	setlocale(0, "");
	Geometry::Square square(8);
	square.info();
	cout << "\n";

	Geometry::Rectangle rect(5, 12);
	rect.info();
	cout << "\n";

	Geometry::Triangle trian(5, 3, 6);
	trian.info();
	cout << "\n";

	Geometry::Circle circle(10);
	circle.info();
}