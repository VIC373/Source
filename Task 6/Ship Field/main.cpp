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
	myField.Show();

	/*insert ships*/
	Init(4,1,myField);
	Init(3,2,myField);
	Init(2,3,myField);
	Init(1,4,myField);
	
	cout << endl;
	system("@pause");
}
