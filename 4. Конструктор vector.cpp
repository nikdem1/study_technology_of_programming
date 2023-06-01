#include <iostream>

using namespace std;

class vector {
private:
    int dim; // Размерность
    double* v; // Массив
    int number; // Количество векторов
public:
    static int count; // Количество векторов, передаваемых в number
    void print();
    vector(); // Пустой конструктор
    vector(int d, double* var); // Задаваемый конструктор (д/з)
    vector(vector& vect); // Копия конструктора
    ~vector(); // Дестрекутор, задаваемый с конца до начала (д/з)
};

int vector::count = 0;


vector::~vector() {
    cout << "Destructor ~vector() deletes vector #" << number << endl;
    delete v;
}


vector::vector() {
    count++; // Увеличиваем счетчик объектов
    number = count; // Присваиваем номер текущего объекта
    cout << "Constructor vector() made vector #" << number << endl;
    dim = 0; // Присваиваем размерность
    v = new double[dim]; // Выделяем память под массив значений
}

vector::vector(int d, double* var) {
    count++; // Увеличиваем счетчик объектов
    number = count; // Присваиваем номер текущего объекта
    cout << "Constructor vector(int d, double* var) made vector #" << number << endl;
    dim = d; // Присваиваем размерность
    v = new double[dim]; // Выделяем память под массив значений

    for (int i = 0; i < dim; i++) {
        v[i] = var[i]; // Заполняем массив значениями
    }
}

vector::vector(vector& vect) {
    count++;
    number = count;
    cout << "Constructor vector(vector&) made vector#" << number << " by coping vector #" << vect.number << endl;
    dim = vect.dim;
    v = new double[dim];
    for (int i = 0; i < dim; i++) {
        v[i] = vect.v[i];

    }
}



void vector::print() {
    if (dim != 0) {
        cout << "Vector" << number << "(";
        for (int i = 0; i < dim; i++) {
            cout << v[i] << ",";
        }
        cout << ")" << endl;
    }
    else {
        cout << "Vector #" << number << " with dim = 0\n";
    }
}

int main()
{
    int d1 = 3;
    double* arr_d1 = new double[d1];
    //vect_d1 = vector(d1, arr_d1);
    //vector& vect_d0 = vector();
    vector vect_d0;
    vector();
    vect_d0.print();
    vector();


    return 0;
}
