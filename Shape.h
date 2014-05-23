#ifndef SHAPE_OOP
#define SHAPE_OOP

#include <string>
#include <iostream>

class Named
{
public:
	Named( std::string const & name )
		:m_name( name ){}

	~Named() {}

	std::string const & GetName() const { return m_name; }

private:
	std::string m_name;
};

class Printable : public virtual Named {
	public:
		Printable( std::string const name ) : Named( name ) {}
		virtual void Print( std::ostream & stream ) const = 0;
		virtual ~Printable() {}
};

std::ostream & operator << ( std::ostream & _stream , Printable const & object ) {
	object.Print( _stream );
	return _stream;
}

class Shape : public virtual Named {
	public:
		Shape( std::string const name ) : Named( name ) { ++sm_count; }
		Shape( Shape const & other_shape ) : Named( other_shape.GetName() ) { ++sm_count; }
		virtual ~Shape() { --sm_count; }

		static int GetCount() { return sm_count; }

	private:
		static int sm_count;
};

int Shape::sm_count = 0;

class Point : public Shape , public Printable {

public:
	Point( std::string const & name , double const & x , double const & y ) 
		:Named( name ) 
		,Shape( name ) 
		,Printable( name ) 
		,m_x( x ) 
		,m_y( y ) {}

	~Point() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << GetName() <<" (" << m_x << "," << m_y << ")" << " - point." << std::endl; 
	}

	double GetX() const { return m_x; }
	double GetY() const { return m_y; }

private:
	double m_x;
	double m_y;

};

class Circle : public Shape , public Printable {

public:
	Circle( std::string const & name , Point const & center , double radius ) 
		:Named( name )
		,Shape( name ) 
		,Printable( name ) 
		,m_center( center ) 
		,m_radius( radius )
		,m_area ( 3.14*radius*radius ) {}

	~Circle() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << GetName() << " - circle. " << std::endl 
			<< "Center: " << GetCenter() 
			<< "Radius: " << GetRadius() << std::endl 
			<< "Area: " << GetArea() << std::endl;
	}

	double GetArea() const { return m_area; }
	double GetRadius() const { return m_radius; }
	Point const & GetCenter() const { return m_center; }

private:
	Point m_center;
	double m_radius;
	double m_area;

};

class Rect : public Shape , public Printable {
public:
	Rect( std::string const & name , Point const & top_left , Point const & bottom_right ) 
		:Named( name )
		,Shape( name ) 
		,Printable( name ) 
		,m_top_left( top_left ) 
		,m_bottom_right( bottom_right )
		{
			m_area = ( bottom_right.GetX() - top_left.GetX() ) * ( bottom_right.GetY() - top_left.GetY() );
		}

	~Rect() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << GetName() << " - rectangle." << std::endl 
			<< "Top left: (" << m_top_left.GetX() << "," << m_top_left.GetY() <<  ")" << std::endl 
			<< "Width: "<< GetWidth() << std::endl 
			<< "Heigth: " << GetHeight() << std::endl 
			<< "Area: " << GetArea() << std::endl;
	}

	double GetWidth() const { return m_bottom_right.GetX() - m_top_left.GetX(); }
	double GetHeight() const { return m_bottom_right.GetY() - m_top_left.GetY(); }
	double GetArea() const { return m_area; }
	Point const & GetTopLeft() const { return m_top_left; }
	Point const & GetBottomRight() const { return m_bottom_right; }

private:
	Point m_top_left;
	Point m_bottom_right;
	double m_area;

};

class Square : public Rect {

public:
	Square( std::string const & name , Point const & top_left , double side_length )
		:Named( name ) 
		,Rect( name , top_left , Point( "bottom right" , top_left.GetX() + side_length, top_left.GetY() + side_length ) ) 
		,m_side_length( side_length ) {}

	~Square() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << GetName() << " - square." << std::endl 
			<< "Top left:(" << Rect::GetTopLeft().GetX()  << "," << Rect::GetTopLeft().GetY() << ")" << std::endl 
			<< "Side Length: " << GetSideLength() << std::endl
			<< "Area: " << GetArea() << std::endl;
	}

	double GetSideLength() const { return m_side_length; }

private:
	double m_side_length;

};

class Polyline : public Shape , public Printable {

public:
	Polyline( std::string const & name ) 
		:Named( name ) 
		,Shape( name ) 
		,Printable( name ) 
		,m_length( 0. ) {}

	~Polyline() {}

	void AddPoint( Point const & point ) {
		if( m_points.IsEmpty() ) {
			m_points.PushFront( point );			
		}
		else {
			Point lastPoint = m_points.GetLast();
			m_points.PushBack( point );
			double dx = (lastPoint).GetX() - point.GetX();
			double dy = (lastPoint).GetY() - point.GetY();
			m_length += sqrt( dx * dx + dy * dy );
		}
	}

	virtual void Print( std::ostream & stream ) const { 
		if( m_points.IsEmpty() )
			stream << "Point list is empty";
		else
			stream << GetName() << " - polyline" << std::endl
			<< "Total length: " << GetLength() << std::endl
			<< "Number of points: " << m_points.GetSize() << std::endl;
	}

	double GetLength() const { return m_length; }

private:
	double m_length;
	XList< Point > m_points;

};
#endif