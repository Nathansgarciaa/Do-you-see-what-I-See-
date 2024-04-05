#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <exception>
#include <stdexcept>

template<typename T>
class MonoStack {
public:
    MonoStack(int initialSize, char o); // Constructor with size and order
    ~MonoStack();

    void push(T i);
    T pop();
    T peek();
    bool isEmpty();
    bool isFull();
    int getSize();

private:
    T* stackArray;
    int top;
    int mSize;
    char order; // 'i' for increasing, 'd' for decreasing

};

template<typename T>
MonoStack<T>::MonoStack(int initialSize, char o) : mSize(initialSize), top(-1), order(o) {
    if (o != 'i' && o != 'd') {
        throw std::invalid_argument("Order must be either 'i' for increasing or 'd' for decreasing.");
    }
    
    stackArray = new T[mSize];
}

template<typename T>
MonoStack<T>::~MonoStack() {
    delete[] stackArray;
}

template<typename T>
void MonoStack<T>::push(T i) {
    const int MAX_SIZE = 100; // Or any other suitable value representing the maximum size of your stack
    
    if (isFull()) {
        throw std::overflow_error("Stack is full");
    }

    // Directly enforce order within push method
    if (order == 'i') {
        while (!isEmpty() && peek() > i) {
            pop(); // Pop elements that are greater than the new element in an increasing stack
        }
    }
    else if (order == 'd') {
        int poppedElements[MAX_SIZE];
        int poppedIndex = -1;

        // Process the current height
        while (!isEmpty() && peek() < i) {
            // Pop elements that are smaller than the new element
            poppedElements[++poppedIndex] = pop();
        }

        // Insert the new element after ensuring order
        stackArray[++top] = i;

        // Add back the popped elements that are still visible
        for (int j = poppedIndex; j >= 0; j--) {
            if (poppedElements[j] < i) {
                stackArray[++top] = poppedElements[j];
            }
        }
    }
}

template<typename T>
T MonoStack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return stackArray[top--];
    
}

template<typename T>
T MonoStack<T>::peek() {
    if (isEmpty()) {
        //throw std::underflow_error("Stack is empty");
        return 0;
    }
    return stackArray[top];
}

template<typename T>
bool MonoStack<T>::isEmpty() {
    return top == -1;
}

template<typename T>
bool MonoStack<T>::isFull() {
    return top == mSize - 1;
}

template<typename T>
int MonoStack<T>::getSize() {
    return top + 1;
}

#endif 