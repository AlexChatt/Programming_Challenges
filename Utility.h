#pragma once
#include <stdio.h>
#include <iostream>

template <typename T>
struct node
{
	T value;
	node* Left, * Right;

	node(T num)
	{
		value = num;
		Left = Right = NULL;
	}

	~node()
	{
		delete Left;
		delete Right;
		Left = Right = NULL;
	}

	T getValue() const { return value; }
	void printValue() const  { std::cout << value << " "; }
};