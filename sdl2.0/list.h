#include <cstdio>
#include <iostream>
#include <string>

#pragma once

using namespace std;

const int STRSIZE = 100;

template<class T>
struct node
{
	string key;
	T value;
	node* next;
};

template<class T>
class list
{
public:
	list();
	~list();

	void insert(string key, T value);
	bool search(string key);
	void remove(string key);

	bool empty();
	int size();

	T& operator[](int index);
	T& operator[](string key);

private:
	node<T>* head;
	int length;
};

//list.cpp

template<class T>
list<T>::list()
{
	head = NULL;
	length = 0;
}

template<class T>
list<T>::~list()
{
	node<T>* victim = head;
	while (victim != NULL)
	{
		head = head->next;
		delete victim;
		victim = head;
	}
}

//insert to front
template<class T>
void list<T>::insert(string key, T value)
{
	node<T>* newnode = new node<T>;
	newnode->key = key;
	newnode->value = value;
	newnode->next = head;
	
	head = newnode;
	length++;
}

//search list, true if found, false otherwise
template<class T>
bool list<T>::search(string key)
{
	node<T>* ptr;
	for(ptr=head; ptr!=NULL; ptr=ptr->next)
	{
		if (ptr->key == key)
			return true;
	}
	return false;
}

//removes a node matching given key
template<class T>
void list<T>::remove(string key)
{
	node<T>* victim;
	node<T>* prev;
	for(victim=head; victim!=NULL; victim=victim->next)
	{
		//found node with matching key
		if (victim->key == key)
		{
			//if head, shift head
			if (victim == head)
				head = head->next;
			//if mid, redirect previous
			else
				prev->next = victim->next;

			length--;
			delete victim;
			return;
		}
		prev = victim;
	}
}

template<class T>
T& list<T>::operator[](int index)
{
	//search history
	static node<T>* prev_ptr = NULL;
	static int		prev_i	 = -1;
	if (prev_i != -1 && prev_i == index)
		return prev_ptr->value;

	//search entire list, skip if index past prev
	node<T>* ptr = head;
	int i = 0;
	if (prev_i >= 0 && prev_i < index)
	{
		i = prev_i;
		ptr = prev_ptr;
	}
	for(; i<index; i++)
	{
		ptr=ptr->next;
	}

	prev_i = i;
	prev_ptr = ptr;

	return ptr->value;
}


template<class T>
T& list<T>::operator[](string key)
{
	if (key == "")
		return head->value;


	//search history
	static node<T>* prev = NULL;
	if (prev != NULL && prev->key == key)
		return prev->value;

	//search entire list
	node<T>* ptr;
	for(ptr=head; ptr!=NULL; ptr=ptr->next)
	{
		if (ptr->key == key)
		{
			prev = ptr;
			return ptr->value;
		}
	}

	//create new node if unlisted
	insert(key, T());
	prev = head;
	//assuming insert front
	return head->value;
}


template<class T>
bool list<T>::empty()
{
	return head == NULL ? true : false;
}

template<class T>
int list<T>::size()
{
	return length;
}