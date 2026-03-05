#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class Stack {
private:
    // Структура для элемента стека (узла)
    struct Node {
        T data;         // Данные типа T
        Node* next;     // Указатель на следующий узел

        // Конструктор для удобного создания узла
        Node(const T& value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };

    Node* head;  // Указатель на вершину стека

public:
    // Конструктор по умолчанию
    Stack() : head(nullptr) {}

    // Деструктор (важно для освобождения памяти!)
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Добавление элемента на вершину
    void push(const T& value) {
        head = new Node(value, head);
    }

    // Удаление элемента с вершины
    void pop() {
        if (!isEmpty()) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Получение значения на вершине (без удаления)
    T top() const {
        if (!isEmpty()) {
            return head->data;
        }
        throw std::runtime_error("Stack is empty!");
    }

    // Проверка, пуст ли стек
    bool isEmpty() const {
        return head == nullptr;
    }
};

#endif // STACK_H
