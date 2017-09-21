//复数操作运算，这个头文件最好用vs自带的vector库替换

#ifndef __COMPLEX_H__
#define __COMPLEX_H__
#pragma   once  
#include<iostream>
class complex
{
public:
 complex(){real=0;imag=0;}
 complex(double r,double i){real=r;imag=i;}
 complex operator+(complex &c2);
 complex operator-(complex &c2);
 complex operator*(complex &c2);
 complex operator/(complex &c2);
 complex operator+(int &i);
 complex operator-(int &i);
 complex operator*(int &i);
 complex operator*(const int &i);
 complex operator/(int &i);
 complex conj(complex &c2);

 void display();
 void setValue(double r, double i);
 double getReal();
 double getImag();
 double real; 
 double imag;
//private:
// double real;
// double imag;
};
#endif

//void complex::setValue(double r, double i)
//{
//	real = r;
//	imag = i;
//}
//
//double complex::getReal()
//{
//	return real;
//}
//double complex::getImag()
//{
//	return imag;
//}
//
//complex complex::operator+(complex &c2)//不明白为什么这里的return不能像后面复数与整数相加时的return.
//{
// complex c;
// c.real=real+c2.real;
// c.imag=imag+c2.imag;
// return c;
//}
//complex complex::operator-(complex &c2)
//{
// complex c;
// c.real=real-c2.real;
// c.imag=imag-c2.imag;
// return c;
//}
//complex complex::operator *(complex &c2)
//{
// complex c;
// c.real=real*c2.real-imag*c2.imag;
// c.imag=imag*c2.real+real*c2.imag;
// return c;
//}
//complex complex::operator / (complex &c2)
//{
// complex c;
// c.real=(real*c2.real+imag*c2.imag)/(c2.real*c2.real+c2.imag*c2.imag);
// c.imag=(imag*c2.real-real*c2.imag)/(c2.real*c2.real+c2.imag*c2.imag);
// return c;
//}
//complex complex::operator +(int &i)
//{
// return complex(real+i,imag);
//}
//complex complex::operator -(int &i)
//{
// return complex(real-i,imag);
//}
//complex complex::operator *(int &i)
//{
// return complex(real*i,imag*i);
//}
//complex complex::operator *(const int &i)
//{
// return complex(real*i,imag*i);
//}
//complex complex::operator /(int &i)
//{
// return complex(real/i,imag/i);
//}
//void complex::display()
//{
// std::cout<<"("<<real<<","<<imag<<"i)"<<std::endl;
//}
