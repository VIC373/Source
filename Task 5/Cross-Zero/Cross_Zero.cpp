#include "stdafx.h"
#include "Cross_Zero.h"

using namespace std;

Field::Field()
{
	for (char i = 0; i < 9; i++)
	{
		cell[i].empty = true;
		cell[i].cross = false;
		cell[i].zero = false;
	}
}

bool Win(const Field& field, bool el)
{
	if (el) //Check for cross
	{	//horizontal
		if (field.cell[0].cross == true && field.cell[1].cross == true && field.cell[2].cross == true)
		{
			return true;
		}
		if (field.cell[3].cross == true && field.cell[4].cross == true && field.cell[5].cross == true)
		{
			return true;
		}
		if (field.cell[6].cross == true && field.cell[7].cross == true && field.cell[8].cross == true)
		{
			return true;
		}
		//vertical
		if (field.cell[0].cross == true && field.cell[3].cross == true && field.cell[6].cross == true)
		{
			return true;
		}
		if (field.cell[1].cross == true && field.cell[4].cross == true && field.cell[7].cross == true)
		{
			return true;
		}
		if (field.cell[2].cross == true && field.cell[5].cross == true && field.cell[8].cross == true)
		{
			return true;
		}
		//diagonal
		if (field.cell[6].cross == true && field.cell[4].cross == true && field.cell[2].cross == true)
		{
			return true;
		}
		if (field.cell[0].cross == true && field.cell[4].cross == true && field.cell[8].cross == true)
		{
			return true;
		}
		return false;
	}
	else//Check for zero
	{
		if (field.cell[0].zero == true && field.cell[1].zero == true && field.cell[2].zero == true)
		{
			return true;
		}
		if (field.cell[3].zero == true && field.cell[4].zero == true && field.cell[5].zero == true)
		{
			return true;
		}
		if (field.cell[6].zero == true && field.cell[7].zero == true && field.cell[8].zero == true)
		{
			return true;
		}
		//vertical
		if (field.cell[0].zero == true && field.cell[3].zero == true && field.cell[6].zero == true)
		{
			return true;
		}
		if (field.cell[1].zero == true && field.cell[4].zero == true && field.cell[7].zero == true)
		{
			return true;
		}
		if (field.cell[2].zero == true && field.cell[5].zero == true && field.cell[8].zero == true)
		{
			return true;
		}
		//diagonal
		if (field.cell[6].zero == true && field.cell[4].zero == true && field.cell[2].zero == true)
		{
			return true;
		}
		if (field.cell[0].zero == true && field.cell[4].zero == true && field.cell[8].zero == true)
		{
			return true;
		}
		return false;
	}
}

bool Play(Field& field, bool el, UI n)
{
	if (n > 9 || n < 1) //we have 9 cells
	{
		return false; 
	}

	if (field.cell[n-1].empty == true) 
	{
		if (el) /*if cross*/
		{
			field.cell[n-1].cross = true; 
			field.cell[n-1].empty = false; 
			return true;
		}
		else /*set zero*/
		{
			field.cell[n-1].zero = true;
			field.cell[n-1].empty = false;
			return true; 
		}
	}
	else
	{
		return false; /*no empty*/
	}
}

void ShowGame(const Field& field)
{
	system("cls");
	char line = 0;
	for (char i = 0; i < 9; i++)
	{
		line++;
		if ( field.cell[i].empty )
		{
			cout << "   ";
		}
		if ( field.cell[i].cross )
		{
			cout << " X ";
		}
		
		if ( field.cell[i].zero )
		{
			cout << " 0 ";
		}
		
		if ( line == 3)
		{
			line = 0;
			cout << endl << endl;
		}
	}
}

void PcPlay(Field& field, bool el)
{
	srand(time(0));
	int pos = -1;
	while ( !Play(field,el,pos + 1) ) /* [1 ; 9] */
	{
		pos = rand() % 8;
	}
}
