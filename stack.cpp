#include "stack.h"
#include <iostream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");

    // === Тест 1: Стек для целых чисел ===
    std::cout << "=== Стек для int ===" << std::endl;
    Stack<int> intStack;

    // Заполняем стек числами от 0 до 20
    for (int i = 0; i <= 20; i++) {
        intStack.push(i);
    }

    std::cout << "Содержимое стека int (вершина первая):" << std::endl;
    intStack.print();

    // Извлекаем несколько элементов
    int value;
    std::cout << "\nИзвлекаем 3 элемента:" << std::endl;
    for (int i = 0; i < 3; i++) {
        if (intStack.pop(value)) {
            std::cout << "Извлечено: " << value << std::endl;
        }
    }

    std::cout << "Вершина после извлечения: " << *intStack.peek() << std::endl;

    // === Тест 2: Стек для чисел с плавающей точкой ===
    std::cout << "\n=== Стек для double ===" << std::endl;
    Stack<double> doubleStack;

    doubleStack.push(3.14);
    doubleStack.push(2.718);
    doubleStack.push(1.618);

    std::cout << "Содержимое стека double:" << std::endl;
    doubleStack.print();

    // === Тест 3: Стек для строк ===
    std::cout << "\n=== Стек для string ===" << std::endl;
    Stack<std::string> stringStack;

    stringStack.push("Первый");
    stringStack.push("Второй");
    stringStack.push("Третий");

    std::cout << "Содержимое стека string:" << std::endl;
    stringStack.print();

    // Извлекаем строки
    std::string str;
    while (stringStack.pop(str)) {
        std::cout << "Извлечено из string: " << str << std::endl;
    }

    // === Тест 4: Использование fill() как в оригинале ===
    std::cout << "\n=== Тест метода fill() ===" << std::endl;
    Stack<int> filledStack;
    filledStack.fill(); // заполняет 21 элементом (по умолчанию)
    std::cout << "Стек после fill() (первые 5 элементов):" << std::endl;

    // Печатаем только первые 5 для краткости
    const int* valPtr;
    for (int i = 0; i < 5; i++) {
        valPtr = filledStack.peek();
        if (valPtr) {
            std::cout << *valPtr << std::endl;
            filledStack.pop(value); // двигаемся дальше
        }
    }

    return 0;
}
