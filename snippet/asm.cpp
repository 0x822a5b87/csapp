#include "iostream"

int add(int a, int b, int c);

void invoke();

int add(int a, int b, int c)
{
	return a + b + c;
}

void invoke()
{
	add(1, 2, 3);
}


int main(int argc, char **argv)
{
	invoke();
}