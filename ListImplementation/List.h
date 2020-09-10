#include "Node.h"
#include <utility>

template<typename T>
class List
{
private:
	int theSize;
	Node<T>* head;
	Node<T>* tail;
	
	void init()
	{
		theSize = 0;
		head = new Node<T>;
		tail = new Node<T>;
		head->next = tail;
		tail->prev = head;
	}
	void clear() {}
public:
	// iterators for list
	class const_iterator
	{
	protected:
		Node<T>* current;
		T& retrieve() const { return current->data; }
		const_iterator(Node<T>* p) : current{ p } {}
		
		friend class List <T>;
	public:
		const_iterator() : current{ nullptr } {}
		const T& operator*() const { return retrieve(); }
		const_iterator& operator++() // pre increment operator
		{
			current = current->next;
			return *this;
		}
		const_iterator operator++(int) // post increment operator
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator==(const const_iterator& it)
		{ return current == it.current; }
		bool operator!=(const const_iterator& it)
		{
			return !(*this == it);
		}
	};
	class iterator : public const_iterator
	{
	protected:
		iterator(Node<T>* p) : const_iterator{ p } {}

		friend class List<T>;
	public:
		iterator() {}
		T& operator*() { return const_iterator::retrieve; }
		const T& operator*() { return const_iterator::operator*(); }
		iterator& operator++()
		{
			this->current = this->current->next;
			return *this;
		}
		const iterator operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
	};

	List() { init(); }
	List(const List<T>& source) // copy constructor
	{
		init();
		for (auto& x : source)
			push_back(x);
	}
	List<T>& operator=(const List<T>& source) // copy assignment
	{
		List copy = source;
		std::swap(*this, source);
		return *this;
	}
	List(List<T>&& source)
		: theSize{ source.theSize }, head{ source.head }, tail{ source.tail }
	{
		source.theSize = 0;
		source.head = nullptr;
		source.tail = nullptr;
	}
	List<T>& operator=(List<T>&& source)
	{
		std::swap(theSize, source.theSize);
		std::swap(head, source.head);
		std::swap(tail, source.tail);

		return *this;
	}
	~List()
	{
		clear();
		delete head;
		delete tail;
	}

	void push_back(Node<T>& data) {}
	// insertion x before it
	iterator insert(iterator it, const T& x)
	{
		Node<T>* p = it.current;
		++theSize;
		return { p->prev = p->prev->next = new Node<T>{x, p->prev, p} };
	}
	iterator insert(iterator it, T&& x)
	{
		Node<T>* p = it.current;
		++theSize;
		return { p->prev = p->prev->next = new Node<T>{std::move(x), p->prev, p} };
	}

	// erase item at it
	iterator erase(iterator it)
	{
		Node<T>* p = itr.current;
		iterator retVal{ p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		--theSize;
	
		return retVal;
	}
	// range erase 
	iterator erase(iterator from, iterator to)
	{
		for (iterator it = from; it != to;)
			it = erase(it);

		return to;
	}
};