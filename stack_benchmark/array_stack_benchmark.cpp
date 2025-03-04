#include <iostream>
#include <chrono>

using namespace std::chrono;

class Stack
{
private:
    int *mystack;
    int pointer = 0;
    int size;

public:
    Stack(int s)
    {
        size = s;
        mystack = (int *)malloc(sizeof(int) * s);
    }

    void push(int data)
    {
        if (this->isFull())
            return;
        this->mystack[this->pointer++] = data;
    }

    int pop()
    {
        if (this->isEmpty())
            return 0;
        return this->mystack[--this->pointer];
    }

    void display()
    {
        if (!(this->isEmpty()))
        {
            for (int i = this->pointer - 1; i >= 0; i--)
            {
                printf("%i ", this->mystack[i]);
            }
        }
        printf("\n");
    }

    bool isEmpty()
    {
        return (this->pointer == 0);
    }

    bool isFull()
    {
        return (this->pointer == this->size);
    }

    int stackTop()
    {
        if (this->isEmpty())
            return 0;
        return this->mystack[this->pointer - 1];
    }
};

int bm()
{
    Stack myStack(10);

    auto start = high_resolution_clock::now();
    myStack.push(8);
    myStack.push(10);
    myStack.push(5);
    myStack.push(11);
    myStack.push(15);
    myStack.push(23);
    myStack.push(6);
    myStack.push(18);
    myStack.push(20);
    myStack.push(17);
    myStack.display();
    for (int i = 0; i < 5; i++)
    {
        myStack.pop();
    }
    myStack.display();
    myStack.push(4);
    myStack.push(30);
    myStack.push(3);
    myStack.push(1);
    myStack.display();
    auto finish = high_resolution_clock::now();
    int duration = duration_cast<nanoseconds>(finish - start).count();
    return duration;
}

int main()
{
    int n = 100000;
    long total = 0;

    for (int i = 0; i < n; i++)
    {
        total += bm();
    }

    printf("Benchmark Result\n%ld\n====", total / n);

    return 0;
}