#include <iostream>

class MyClass {
public:
    int value;

    // ����������� �� ���������
    MyClass() {
        // �� ����� ���������������� value, ��� �������� ��� ��������������������.
        // value = 0; // ��� ����� �������������
    }

    void display() const {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    // ���������� ������������ ������� �� 5 �������� ������ MyClass
    MyClass myArray[5];

    // ����� ��������
    /*for (int i = 0; i < 5; ++i) {
        myArray[i].display(); // ��� ����� �������� �������������� ��������
    }*/

    return 0;
}
