#pragma once
#include <stdio.h>
#include <iostream>

struct node
{
	int number = 0;
	node* Left, * Right;

	node(int num)
	{
		number = num;
		Left = Right = NULL;
	}

	~node()
	{
		delete Left;
		delete Right;
		Left = Right = NULL;
	}

	int getNumber() const { return number; }
	void printNum() const  { std::cout << number << " "; }
};