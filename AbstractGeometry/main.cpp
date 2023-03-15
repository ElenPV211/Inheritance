﻿#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry //пространство имен Geometry чтобы не путало в
{
class Shape
{
public:
	virtual double get_area()const = 0;
	virtual double get_perimetr()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь фигуры:" << get_area() << endl;
		cout << "Периметр фигуры:" << get_perimetr() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	Square(double side)
	{
		set_side(side);
	}
	~Square(){}

	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
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
		this->length= length;
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
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};
}
void main()

{
	setlocale(0, "");
	Geometry:: Square square(8);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimetr() << endl;
	square.draw();*/

	square.info();

	Geometry::Rectangle rect(5, 12);
	rect.info();

}