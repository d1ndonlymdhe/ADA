#include <iostream>
#include <functional>
#include <vector>
#include "gettime.h"
using namespace std;

class Stack
{
    int *elements;

public:
    size_t size = 0;
    size_t max = 0;

    Stack(size_t size)
    {
        elements = (int *)(calloc(size, sizeof(int)));
        max = size;
    }
    int top()
    {
        if (size > 0)
        {
            return elements[size - 1];
        }
        throw out_of_range("Nothing on top");
    }
    int pop()
    {
        if (size == 0)
        {
            throw out_of_range("Nothing to pop");
        }
        int ret = elements[size - 1];
        size--;
        return ret;
    }
    int &operator[](size_t index)
    {
        if (index > size - 1)
        {

            throw out_of_range("Index out of range");
        }
        return elements[index];
    }
    void push(int value)
    {
        if (size + 1 <= max)
        {
            elements[size] = value;
            size++;
        }
        else
        {
            throw out_of_range("Stack is full");
        }
    }
};

int main()
{
    vector<int> sizes;
    sizes.push_back(10000000);
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + 5000);
    }
    for (size_t i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        Stack s(size);
        auto push_items = [&]()
        {
            for (int i = 0; i < s.max; i++)
            {
                s.push(i);
            }
        };

        cout << "Time taken to push " << size << " items: " << getTime(push_items) << " nanoseconds\n";
    }
    for (size_t i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        Stack s(size);

        for (int i = 0; i < s.max; i++)
        {
            s.push(i);
        }

        auto pop_items = [&]()
        {
            while (s.size > 0)
            {
                s.pop();
            }
        };

        cout << "Time taken to pop " << size << " items: " << getTime(pop_items) << " nanoseconds\n";
    }
    return 0;
}
