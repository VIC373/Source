/*
* Write a program that will determine the value of an arithmetic expression.
* For example, the (2 + 7) x 5 + 4. Arithmetic expression must be entered from the keyboard in a single line without spaces
* (Use the data type of char).
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

const int EXPR_SIZE = 100;
typedef unsigned int UI;
typedef unsigned char UC;

inline UI MyAtoi(const char* const str) /*only for unsigned numbers return 0 - err */
{
	UI val = 0;
	for (UC i = 0; str[i] >= '0' && str[i] <= '9' && str[i] != '\0'; i++) /*to end of number*/
	{
		val = 10 * val + str[i] - 0x30; /*ASCII code for numbers from 0x30*/
	}
	return val;
}

char* MyItoa(UI n) /*only for unsigned numbers*/
{
	UI len = log10(float(n)) + 1;
	char* text;

	try
	{
		text = new char[len+1];
	}
	catch(bad_alloc& ba)
	{
		cerr << ba.what();
	}

	text[len] = '\0';

	while ( n >= 10 )
	{
		UI num = n % 10;
		text[--len] = num + 0x30;
		n = (n - num) / 10;
	}
	text[--len] = n + 0x30;

	return text;
}

inline UI ResDo(UI lv, UI rv, char sign) /* return 0 - err */
{
	if ( sign == '-' )
	{
		return lv - rv;
	}
	else if ( sign == '+' )
	{
		return lv + rv;
	}
	else if ( sign == '*' )
	{
		return lv * rv;
	}
	else if ( sign == '/' )
	{
		return lv / rv;
	}
	return 0;
}

void DoBracket(const char* const line, char * const p1)
{
	UI lv, rv, res, sizeLv, sizeRv, sizeRes;
	char* sign;

	lv = MyAtoi(p1);					/* we have number after bracket (****+   */
	sizeLv = log10(float(lv)) + 1;		/* we have his langths **** 4  */

	sign = p1 + sizeLv;					/* after number we will have a sign (like + - / *) */

	rv = MyAtoi(sign + 1);				/* next number after the sign */
	sizeRv = log10(float(rv)) + 1;		/* we have his langths +*** 3  */

	res = ResDo(lv,rv,*sign);			/* result */
	sizeRes = log10(float(res)) + 1;	/* lengths of result */

	memmove( p1 - 1 + sizeRes, p1 - 1 + sizeLv + 1 + sizeRv + 2, strlen(line) ) ;

	char* tmp = MyItoa(res);

	for (char i = 0; i < sizeRes; i++)
	{
		*( p1 - 1  + i ) = *( tmp + i ) ;
	}

	delete[] tmp;
}

void Do(const char* const line, char * p1)/*  '*' or '/' or '+' or '-' */
{
	UI lv, rv, res, sizeLv, sizeRv, sizeRes;

	rv = MyAtoi(p1+1);	/*right value*/
	sizeRv = log10(float(rv))+1;
					
	int i = 0;
	while (1)
	{
		i--;
		if ( *(p1+i) == '+' || *(p1+i) == '-' || p1+i+1 == line )
		{
			break;
		}
	}
	lv = MyAtoi(p1+i+1); /*left value*/
	sizeLv = log10(float(lv))+1;
					
	res = ResDo(lv,rv,*p1); /*result*/
	sizeRes = log10(float(res))+1;
				
	p1 -= sizeLv;

	memmove( p1 + sizeRes, p1 + sizeLv + 1 + sizeRv, strlen(line) );

	char* tmp = MyItoa(res);
	for (char i = 0; i < sizeRes; i++)
	{
		*( p1 + i ) = *( tmp + i ) ;
	}
	delete[] tmp;
}

void Calculate(char* const line, char l, char r)
{
	char* p1 = NULL;
	for (UC i = 0; i < strlen(line); i++)
	{
		if ( ( line[i] == l ) || ( line[i] == r ) )
		{
			p1 = line + i;
		}
		if ( p1 )
		{
			Do(line,p1);
			i = 0;
			p1 = NULL;
		}
	}
}

bool IsValid(const char* const line)
{
	bool flag = true;
	for (UC i = 0; i < strlen(line); i++)
	{
		if (   ( line[i] >= '0' && line[i] <= '9' )	
			|| ( line[i] == ')' ) ||  ( line[i] == '(' )	//Is brackets?
			|| ( line[i] == '*' ) ||  ( line[i] == '/' )
			|| ( line[i] == '+' ) ||  ( line[i] == '-' ) )
		{
			//NULL
		}
		else
		{
			flag = false;
		}
	}
	return flag;
}

void main(void)
{
	cout << "Program for calculating arithmetic expression " << endl
		 << " 1) Sign '-' or '+' only like binary operation" << endl
		 << " 2) In brackets only two arguments (no less or more)" << endl
		 << " 3) Operations with zero does not support (like 5+0)" << endl
		 << " 4) You should to write expression without space" << endl << endl;

	char* line;

	while (1)
	{
		cout << "Please enter the expression" << endl;
		try
		{
			line = new char[EXPR_SIZE];
		}
		catch(bad_alloc& ba)
		{
			cout << ba.what();
		}
		cin >> line;				/*read line to space*/
		if ( IsValid(line) )
		{
			break;
		}
		else
		{
			delete[] line;
			cout << "Syntax error" << endl;
		}
	}

	char *p1 = NULL;

	/*Do vs brackets*/
	for (UC i = 0; i < strlen(line); i++)
	{ 
		if ( line[i] == '(' )
		{
			p1 = line + i + 1; /*next symbol after brackets*/
		}
		if ( line[i] == ')' && (p1) )	/* "(" vs ")" ? */
		{
			DoBracket(line,p1);
			i = 0;
			p1 = NULL;
		}
	}
	cout << "1) " << line << endl;

	Calculate(line,'*','/');
	cout << "2) " << line << endl;

	Calculate(line,'+','-');
	cout << "3) RESULT = " << line << endl;

delete[] line;
system("@pause");
}