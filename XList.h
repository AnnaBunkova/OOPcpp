#ifndef XLIST_OOP
#define XLIST_OOP

#include <exception>

template < class T > 

class XList 
{
	private:
		struct ListNode {
			T m_value;
			ListNode * next;
			ListNode * prev;

		ListNode () 
			:m_value ()
			,next ( nullptr ) 
			,prev ( nullptr )  {} 
			
		
		ListNode ( T const & input_data )
			:m_value ( input_data )	
			,next ( nullptr ) 
			,prev ( nullptr ) {} 
			

		~ListNode() {}	
	};

public:

	class ListIsEmpty: public std::exception
	{
		virtual char const * what() const throw() { return "List is empty."; };
	};

	class Iterator
	{
	public:
		Iterator( ListNode * pointer ) { m_list_element = pointer; }

		T & operator * () { return m_list_element->m_value; }

		Iterator & operator ++ ()
		{
			m_list_element = m_list_element->next;
			return *this;
		}

		Iterator & operator -- ()
		{
			m_list_element = m_list_element->prev;
			return *this;
		}

	private:
		ListNode * m_list_element;
	};

	XList()
		:m_begin( nullptr )
		,m_end ( nullptr )
		,m_size( 0 ) {}

	XList ( const XList & some_list )
	{
		m_begin = some_list.m_begin;
		m_end = some_list.m_end;
		m_size = some_list.m_size;
	}

	~XList () { DeleteList(); }

	ListNode * begin() { return m_begin; }
	ListNode * end() { return m_end; }
	size_t GetSize() const { return m_size; }
	bool IsEmpty() const { return ( nullptr == m_begin ); }

	void DeleteList () {
		ListNode * pointer = m_begin;
		while( pointer != nullptr )
		{
			ListNode* temp_pointer = pointer;
			pointer = pointer->next;
			delete temp_pointer;
		}
		m_begin = nullptr;
		m_end = nullptr;
		m_size = 0;
		}

	void PushFront ( T const & data )
	{
		if ( IsEmpty() )
		{
			m_begin = new ListNode( data );
			m_end = m_begin;	
		}
		else
		{
			ListNode * element = new ListNode( data );			
			element->next = m_begin;

			m_begin->prev = element;
			m_begin = element;
		}
		++m_size;
	}

	void PopFront()
	{
		if ( !IsEmpty() )
		{
			ListNode * first_element = m_begin->next;
			delete m_begin;
			m_begin = first_element;
			m_begin->prev = nullptr;

			--m_size;
		}
		else
		{
			ListIsEmpty();
		}
	}

	void PushBack ( T const & data )
	{
		if ( IsEmpty() )
		{
			m_end = new ListNode ( data );
			m_begin = m_end;
		}
		else
		{
			ListNode * new_last_element = new ListNode ( data );			
			new_last_element->prev = m_end;

			m_end->next = new_last_element;
			m_end = new_last_element;
		}
		++m_size;
	}

	void PopBack()
	{
		if ( m_end != nullptr )
		{
			ListNode * element = m_end->prev;
			delete m_end;
			m_end = element;
			m_end->next = nullptr;

			--m_size;
		}
		else
		{
			ListIsEmpty();
		}
	}

	T GetFirst() const
	{
		if ( !IsEmpty() )
		{
			return m_begin->m_value;
		}
		else
		{
			ListIsEmpty();
		}		
	}

	T GetLast() const
	{
		if ( !IsEmpty() )
		{
			return m_end->m_value;		
		}
		else
		{
			ListIsEmpty();
		}
	}

	private:
		ListNode * m_begin;
		ListNode * m_end;
		size_t m_size;

	};

#endif
