#include "stdafx.h"
#include "Cross_Zero.h"

using namespace std;

void main(void)
{
	cout << "Welcome to GAME you would like to have CROSS(1) or ZERO(0)? " << endl;
	int elem;
	while (1)
	{
		cin.clear();
		cin.sync();

		cin >> elem;
		if ( elem == 1 || elem == 0)
		{
			break;
		}
		cout << "You should to choise '0' or '1'" << endl;
	}

	Field myField;
	int place;
	int k = 0;
	bool f = true;

	while ( !Win(myField,1) && !Win(myField,0) ) /*until the winning - play*/
	{
		if ( !elem && f)
		{
			f = false;
			goto m;
		}

		cout << " Get position to stay and Enter" << endl;
		cin >> place;
		while ( !Play(myField,elem,place) ) /*until not made the right move - do it*/
		{
			cout << "Cell is not empty, or wrong position, try again" << endl;
			cin >> place;
		}
		k++;
		if ( k == 5) /*in this game we have no more than 5 moves*/
		{
			break;
		}
m:		PcPlay(myField,!elem); /*PC Play*/
		ShowGame(myField);
	}


	if ( Win(myField,1) )
	{
		cout << "\n X - win";
	}
	else if ( Win(myField,0) )
	{
		cout << "\n 0 - win";
	}

	cout << "\n\n End=) !!!" << endl;

	system("@pause");
}
