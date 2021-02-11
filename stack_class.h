#pragma once
template <typename T>
class Stack
{
private:
	struct elem 
	{
		elem(T value, elem* next = nullptr) :value(value), next(next) {};
		T value;
		elem* next;
	};
public:
	Stack() : parent(nullptr) {};
	~Stack() { clear(); };
	void push(T value)
	{
		parent = new elem(value, parent);
	}
	T pop()
	{
		elem* deleter = parent;
		parent = parent->next;
		T value = deleter->value;
		delete deleter;
		return value;
	}
	T top() const
	{
		return parent->value;
	}
	bool empty() const
	{
		return parent == nullptr;
	}
	void clear()
	{
		while (parent != nullptr)
		{
			elem* deleter = parent;
			parent = parent->next;
			delete deleter;
		}
	}
private:
	elem* parent;
};