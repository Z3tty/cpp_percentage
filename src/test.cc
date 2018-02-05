#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include "percent.h"

int main(int argc, char **argv)
{
	// Testing of every function
	// If any of these return an error, a recent change created a bug
	percentage prc(54);
	percentage qrt(46);
	percentage xyz(2);
	percentage vtc(3);
	std::cout << "1 " << prc << std::endl;
	std::cout << "2 " << qrt << std::endl;
	std::cout << "3 " << xyz << std::endl;
	std::cout << "4 " << vtc << std::endl;
	std::cout << "54 + 46 =\t" << prc + qrt << std::endl;
	std::cout << "54 - 46 =\t" << prc - qrt << std::endl;
	std::cout << "2 * 3   =\t" << xyz * vtc << std::endl;
	std::cout << "46 / 2  =\t" << qrt / xyz << std::endl;
	std::cout << "46 % 3  =\t" << qrt % vtc << std::endl;
	vtc.expp(2);
	std::cout << "3 ** 2  =\t" << vtc << std::endl;

	percentage p(10);
	percentage q(5);
	std::cout << "Origin-values: P:10 Q:5" << std::endl;
	p += q;
	std::cout << "(P += Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p -= q;
	std::cout << "(P -= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p /= q;
	std::cout << "(P /= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p *= q;
	std::cout << "(P *= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	q.realloc(3);
	p %= q;
	std::cout << "(P %= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;

	p.realloc(50);
	std::cout << "P set to 50" << std::endl;
	std::cout << "P + 1 " << p + 1 << std::endl;
	std::cout << "P - 1 " << p - 1 << std::endl;
	std::cout << "P / 2 " << p / 2 << std::endl;
	std::cout << "P * 2 " << p * 2 << std::endl;
	std::cout << "P % 3 " << p % 3 << std::endl;
	std::cout << "P +=1, -=1, *=2, /=2, %=8" << std::endl;
	p += 1;
	std::cout << p << std::endl;
	p -= 1;
	std::cout << p << std::endl;
	p *= 2;
	std::cout << p << std::endl;
	p /= 2;
	std::cout << p << std::endl;
	p %= 8;
	std::cout << p << std::endl;
	std::cout << "P++ " << p++ << std::endl;
	std::cout << "++P " << ++p << std::endl;
	std::cout << "P-- " << p-- << std::endl;
	std::cout << "--P " << --p << std::endl;

	p.realloc(74);
	std::cout << "P is now 74" << std::endl;
	std::cout << "P.toInt() +1 =>\t\t\t\t " 		<< p.toInt()+1 			<< std::endl;
	std::cout << "P.toFloat() +0.5 =>\t\t\t " 		<< p.toFloat()+0.5 		<< std::endl;
	std::cout << "P.toDouble() -0.43253234523 =>\t\t " 	<< p.toDouble()-0.43253234523 	<< std::endl;
	std::cout << "P.toString().append(\"str\") =>\t\t " 	<< p.toString().append("str") 	<< std::endl;
	return 0;
}
