#include <utility>

template<typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;

	Node(const T& d = T{}, Node* p = nullptr, Node* n = nullptr)
		: data{ d }, prev{ p }, next{ n }
	{	}

	Node(T&& d, Node* p = nullptr, Node* n = nullptr)
		: data{ std::move(d) }, prev{ p }, next{ n }
	{ }
};

