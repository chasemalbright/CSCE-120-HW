#ifndef PASSING_BY_REFERENCE
#define PASSING_BY_REFERENCE
struct example
{
	int value =2;
};

void function_one(int i, int& j);
void function_two(example& x);
void function_three(int *k, int &l);
void function_four(int x[], int size,int& lowest, int& highest);
#endif