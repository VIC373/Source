#include "stdafx.h"
#include "ShipField.h"

void main(void)
{
	short size;
	cout << "What zise of field you would like to have?" << endl;
	
	while (1)
	{
		cin >> size;
		if (size >= 10)
		{
			break;
		}
		cout << "You should put size > 10. Because we need to place 10 ships" << endl;
	}

	Field myField(size);
	Field pcField(size);
	
	myField.Show();
	
	/*insert ships */
	Init(4,1,myField);
	Init(3,2,myField);
	Init(2,3,myField);
	Init(1,4,myField);

	cout << "PC initialize his ships" << endl;
	InitPc(pcField);
	

	cout << "GAME START !" << endl;

	short x,y;
	while ( myField.Win() || pcField.Win() ) /*until have not winner - game*/
	{
				myField.Show();
userAgain:		cout << "Fire!" << endl;
				cin >> x >> y;
		
				if ( pcField.Fire(x,y) )
				{
					cout << "HIT, again" << endl;
					goto userAgain;
				}

pcAgain:		srand(time(0));
				x = rand() % (size - 1) + 2;
				x = rand() % (size - 1) + 2;

				if ( myField.Fire(x,y) )
				{
					cout << "PC HIT" << endl;
					goto pcAgain;
				}
				pcField.Show();
				cout << "THIS IS PC FIELD" << endl;
				Sleep(4000);

	}
	cout << endl << "Game over" << endl;
	system("@pause");
}