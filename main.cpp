#include "XList.h"
#include "Shape.h" 

#include <time.h>

int main ()
{
	srand(time(NULL));

	XList < Printable * > figures_list;

	Printable * shape_1 = new Point ( "shape_1", 2., 2. );
	figures_list.PushBack ( shape_1 );

	Printable * shape_2 = new Circle ( "shape_2", Point ( "A", 2., 2. ), 2. );
	figures_list.PushBack ( shape_2 );

	Printable * shape_3 = new Rect ( "shape_3", Point ( "A1", 0., 0. ), Point ( "A2", 4., 5. ) );
	figures_list.PushBack ( shape_3 );

	Printable * shape_4 = new Square ( "shape_4", Point ( "B", 1., 1. ), 7. );
	figures_list.PushBack ( shape_4 );

	int number_of_points = 6;
	Polyline * shape_5 = new Polyline ( "shape_5" );
	for ( int i = 1 ; i <= number_of_points ; ++i ) {
	int x = rand() % 10;
	int y = rand() % 10;
	shape_5->AddPoint ( Point ( "point_1", x, y) );
	}
	figures_list.PushBack ( shape_5 );

	std::cout << "Number of figures: " << Shape::GetCount() << std::endl;

	std::cout << "Figures info:"<< std::endl;

	XList < Printable * >::Iterator it = figures_list.begin();

	for( int i = 0; i != figures_list.GetSize(); ++i )
	{
		std::cout << *(*it) << std::endl;
		++it;
	}

	XList < Printable * >::Iterator shape = figures_list.begin();

	for ( int i = 0; i != figures_list.GetSize(); ++i)
	{
		delete * shape;
		++shape;
	}

	figures_list.DeleteList();

	std::cout << "Number of figures: " << Shape::GetCount() << std::endl; 
	system("pause");
	return 0;
}