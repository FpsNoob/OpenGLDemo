#pragma once

#define MAX_SIZE 5000

template<typename T> struct SqStack {
	T data[MAX_SIZE];
	int top;
};


template<typename T> void InitStack(SqStack<T> *& S)
{
	S = new SqStack<T>;
	S->top = -1;
}

template<typename T> bool Push(SqStack<T>* &S, T e)
{
	if (S->top == MAX_SIZE - 1)
		return false;
	S->top++;
	S->data[S->top] = e;
	return true;
}

template<typename T> bool Pop(SqStack<T>* &S, T &e)
{
	if (S->top == -1)
		return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

template<typename T> void DestroyStack(SqStack<T>* &S)
{
	delete S;
}

template<typename T> void DispStack(SqStack<T>* S)
{
	while (S->top != -1)
	{
		cout << '\t' << S->data[S->top];
		S->top--;
	}
	cout << endl;
}

template<typename T> bool StackEmpty(SqStack<T> * S)
{
	return (S->top == -1);
}

template<typename T> bool GetTop(SqStack<T> *s, T &e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}
