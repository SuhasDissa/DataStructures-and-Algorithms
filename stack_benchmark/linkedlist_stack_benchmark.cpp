#include <iostream>
#include <chrono>

using namespace std::chrono;

class Node
{
public:
    int data;
    Node *next = NULL;

    Node(int d)
    {
        this->data = d;
    }
};

class Stack
{
private:
    Node *head = NULL;

public:
    Stack() {}

    void push(int data)
    {
        Node *new_node = new Node(data);
        new_node->next = this->head;
        this->head = new_node;
    }

    void pop()
    {
        if (this->head == NULL)
        {
            return;
        }
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }

    void display()
    {
        Node *current = this->head;
        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    bool isEmpty()
    {
        return (this->head == NULL);
    }

    int stackTop()
    {
        return this->head->data;
    }
};

int bm()
{
    Stack myStack;

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