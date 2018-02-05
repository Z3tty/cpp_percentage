/*
 *  CPP_Percentage => A percentage datatype for C++
 *  Copyright (C) 2018  ZexZee
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include "percent.h"

// The actual cout overloading, makes sure that printing -> (VALUE)%
std::ostream& operator<<(std::ostream& os, const percentage& p) { os << p.value << "%"; return os; }

// Constructor: Verify bounds and report any assignment/value errors
percentage::percentage(unsigned int p) 
{
	if(p <0 || p >100) {
		std::cout << "ValueError :: Percentage allocated with more than 100 or less than 0" << std::endl;
		exit(EXIT_FAILURE);
		return;
	} percentage::value = p;
}

// Virtually identical to the constructor, but for reallocating the percentage
void percentage::realloc(unsigned int v) 
{
	if(v <0 || v >100) {
		std::cout << "ValueError :: Percentage allocated with more than 100 or less than 0" << std::endl;
		exit(EXIT_FAILURE);
		return;
	} this->value = v;
}

// Simple math - Uses realloc to catch value errors
void percentage::addp(percentage p) { this->realloc(this->value + p.value); }
void percentage::subp(percentage p) { this->realloc(this->value - p.value); }
void percentage::mulp(percentage p) { this->realloc(this->value * p.value); }

// Simple math, yet with potential for /0 bugs
void percentage::divp(percentage p) 
{ 
	if(p.value != 0) { this->realloc(this->value / p.value); return; }
	std::cout << "Divide by zero in percentage::divp()" << std::endl;
	exit(EXIT_FAILURE);
}
void percentage::modp(percentage p) 
{ 
	if(p.value != 0) { this->realloc(this->value % p.value); return; }
	std::cout << "Divide by zero in percentage::modp()" << std::endl;
	exit(EXIT_FAILURE);
}

// Actual code for conversions - Evidently they serve as wrappers
int 		percentage::toInt(void) 	{ return (int)value; 				}
float 		percentage::toFloat(void) 	{ return (float)value; 				}
double 		percentage::toDouble(void) 	{ return (double)value; 			}
std::string percentage::toString(void) 	        { return std::to_string(value); 		}

// Exponentiation using a multiplication-loop
void percentage::expp(unsigned int e) { 
	percentage *p = this; unsigned int tmp = 1;
	while(e >0) {
		tmp *= p->value;
		--e;
	} this->realloc(tmp);
}
