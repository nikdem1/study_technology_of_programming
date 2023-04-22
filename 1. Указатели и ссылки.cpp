#include <iostream>

using namespace std;

int main()
{
    std::cout.setf(std::ios_base::boolalpha); // добавляем флаг boolalpha, чтобы вместо 0 или 1 выводилось false или true

    int x = 42; // опеределяем переменную x со значением 42
    int& ref = x; // задаём ссылку на переменную x с названием "ref"
    int* ptr = &x; // задаём указатель "ptr" на ссылку на переменную "x"

    cin >> x; // задаём переменную x со значением 42
    ++x; // увеличиваем значение переменной x на 1
    cout << ref << endl; // выводим ссылку ref
    cout << *ptr << endl; // выводим указатель ptr
    cout << bool(ref == *ptr) << endl; // сравниваем значения

    return 0;
}