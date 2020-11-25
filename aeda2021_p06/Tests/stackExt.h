# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> all;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
	return all.empty();
}

template <class T> 
T& StackExt<T>::top()
{
    return all.top();
}

template <class T> 
void StackExt<T>::pop()
{
    if(all.top() == min.top())
        min.pop();
    all.pop();
}

template <class T> 
void StackExt<T>::push(const T & val)
{
    if(min.empty())
        min.push(val);

    else if(val < all.top()){
        min.push(val);
    }
    all.push(val);
}

template <class T> 
T& StackExt<T>::findMin()
{
    return min.top();
}

