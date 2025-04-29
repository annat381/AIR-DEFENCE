#include <iostream>

class MyClass {
public:
    int value;

    // Конструктор по умолчанию
    MyClass() {
        // Он может инициализировать value, или оставить его неинициализированным.
        // value = 0; // Для явной инициализации
    }

    void display() const {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    // Объявление статического массива из 5 объектов класса MyClass
    MyClass myArray[5];

    // Вывод значений
    /*for (int i = 0; i < 5; ++i) {
        myArray[i].display(); // Это может выводить неопределенные значения
    }*/

    return 0;
}
