#include <iostream>

using namespace std;

class vector
{

private:

    int dim; // размерность вектора

    double* v; // одномерный массив 

    int number; // номер вектора

    friend vector& operator-(vector& op, vector& vect);
    friend vector& operator*(int n, vector& vect);
    friend class matr;

public:

    static int count;

    void print();

    vector(); // конструктор
    vector(int d);
    vector(int d, double* var); //DZ
    vector(vector& vect);
    ~vector(); // DZ

    double operator*(vector& vect); //умножение векторов
    vector& operator*(int n); // умножение вектора на число
    vector& operator+(vector& vect); // сложение векторов
    vector& operator-(); // отрицание

    double operator[](int i); // определеннный элемент вектора
    vector& operator=(vector& vect);  //  vector& operator=(const vector& vect);
    vector& operator++();

};

int vector::count = 0; // задаем статическую переменную


// ВЫЧИТАНИЕ ВЕКТОРОВ
vector& operator-(vector& op, vector& vect)
{
    cout << "Substraction vector #" << vect.number << " from vector #" << op.number << endl;
    static vector tmp(op.dim);
    for (int i = 0; i < op.dim; i++)
    {
        tmp.v[i] = op.v[i] - vect.v[i];
    }
    return tmp;
}

// ПРИРАВНИВАНИЕ ВЕКТОРОВ
vector& vector::operator=(vector& vect)
{
    cout << "Equating vector #" << number << " to vector #" << vect.number << endl;
    for (int i = 0; i < dim; i++)
    {
        v[i] = vect.v[i];
    }
    return *this;
}


// ВЫВОД ЭЛЕМЕНТА
double vector::operator[](int i)
{
    cout << "Getting element " << i << " from vector #" << number << " : == " << v[i] << endl;
    return v[i];
}


// УМНОЖЕНИЕ ВЕКТОРА НА ВЕКТОР
double vector::operator*(vector& vect)
{
    double tmp = 0;
    for (int i = 0; i < dim; i++)
    {
        tmp += v[i] * vect.v[i];
    }
    cout << "Scalar multiplication (vector #" << number << ", vector #" << vect.number << ") = " << tmp << endl;
    return tmp;
}

// ++
vector& vector::operator++()
{
    cout << "Vector #" << number << " adds 1" << endl;
    for (int i = 0; i < dim; i++) {
        this->v[i] = v[i] + 1;
    }
    return *this;
}

// КОНСТРУКТОРЫ ВЕКТОРОВ
vector::vector(int d)
{
    count++;

    number = count;

    cout << "Constructor vector(d) made vector #" << number << endl;
    dim = d;

    v = new double[dim];
    for (int i = 0; i < dim; i++)
    {
        v[i] = 0;
    }

}

// ДЕСТРУКТОР
vector::~vector()
{
    cout << "\nDeleting vector #" << number << endl;
    delete[]v;
}

// ПУСТОЙ ВЕКТОР
vector::vector()
{

    count++;

    number = count;

    cout << "Constructor vector() made vector #" << number << endl;

    dim = 0;

    v = new double[dim];

}


vector::vector(int d, double* var) // создаем вектор (д - размерность, вар - массив с координатами вектора)
{

    count++;

    number = count;

    cout << "Constructor vector(d,vector&) made vector #" << number << endl;

    dim = d;

    v = new double[dim];

    for (int i = 0; i < dim; i++)
    {

        v[i] = var[i];

    }

}

// конструктор такого же вектора
vector::vector(vector& vect)
{

    count++;

    number = count;

    cout << "Constructor vector(vector&) made vector #" << number << " by coping vector #" << vect.number << endl;

    dim = vect.dim;

    v = new double[dim];

    for (int i = 0; i < dim; i++)
    {

        v[i] = vect.v[i];

    }

}


void vector::print()
{

    if (dim != 0)
    {

        cout << "Vector #" << number << ": (";

        for (int i = 0; i < dim; i++)
        {

            cout << v[i] << ",";

        }

        cout << ")" << endl;

    }

    else
    {

        cout << "Vector #" << number << " with dim = 0\n";

    }

}

// МАТРИЦЫ ........................................................................


class matr {
    int dim;  // квадратные матрицы, одномерная размерность
    double** b; // двумерный массив b
    int number;  // порядковый номер
    friend matr& operator*(double c, matr& m);  // friend operator умножение матрицы на число, есть
    friend class vector; // Дружественный класс векторов

public:
    static int countmatr;

    matr();  // матрица с дим 0
    matr(int d); // матрица заполнена 0
    matr(int d, double** x);  // матрица заполнена чем-то из массива
    matr(int d, int o);
    matr(matr& m);  // матрица копия другой матрицы
    ~matr();  // деструктор

    void print() const;
    matr& ObrDiag(matr& m);

    // по ссылке не происходит копирования, а без - происходит

    matr operator+(const matr& m) const;  // доделать
    matr& operator-(const matr& m);  // указатель на матрицу, есть
    matr& operator-();  // отрицание матрицы, есть
    matr operator*(const matr& m) const;  // доделать
    matr& operator=(const matr& m);  // есть
    matr& operator*(double c);  // умножение на число, DZ
    vector& operator*(const vector& vect) const;  // next lesson
    matr& operator+=(const matr& m) const;


};

int matr::countmatr = 0;

matr& matr::operator*(double c) { // умножение матрицы на число (не friend)
    cout << "Multiplicating matrix #" << number << " with number " << c << endl;
    static matr tmp(dim); // создали новую матрицу с 0, в которую вложим результаты
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] * c;
        }
    }

    return tmp;
}


vector& matr::operator*(const vector& vect) const {

    cout << "Multiplicating matrix #" << number << " with vector #" << vect.number << endl;

    static vector tmp(dim);

    for (int i = 0; i < dim; i++) {
        double n = 0;
        for (int j = 0; j < dim; j++) {
            n += vect.v[j] * b[i][j];
        }
        tmp.v[i] = n;
    }

    return tmp;
}


matr matr::operator*(const matr& m) const { // умножение двух матриц

    cout << "Multiplicating matrix #" << number << " with matrix #" << m.number << endl;
    matr tmp(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = 0;
            for (int k = 0; k < dim; k++) {
                tmp.b[i][j] += b[i][k] * m.b[k][j];
            }
        }
    }
    return tmp;
}


matr& matr::operator-() { // отрицание всех элементов матрицы

    cout << "Negation matrix #" << number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = -b[i][j];
        }
    }

    return tmp;
}

matr& matr::operator-(const matr& m) { // вычитание двух матриц

    cout << "Subtraction matrix #" << m.number << " from matrix #" << number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] - m.b[i][j];
        }
    }
    return tmp;
}

matr matr::operator+(const matr& m) const { // сложение двух матриц

    cout << "Summarizing matrix #" << number << " with matrix #" << m.number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] + m.b[i][j];
        }
    }
    return tmp;
}


matr& matr::operator=(const matr& m) {  // оператор присваивания для матриц

    cout << "Equating matrix #" << number << " to matrix #" << m.number << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            b[i][j] = m.b[i][j];
        }
    }
    return *this;
}

matr& operator*(double c, matr& m) {  // умножение на число

    cout << "Multiplicating matrix #" << m.number << " with number" << c << endl;
    static matr tmp(m.dim);
    for (int i = 0; i < m.dim; i++) {
        for (int j = 0; j < m.dim; j++) {
            tmp.b[i][j] = c * m.b[i][j];
        }
    }

    return tmp;
}

// +=: x = x + y
matr& matr::operator+=(const matr& m) const {

    cout << "Matrix #" << number << " = matrix #" << number << " + matrix #" << m.number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] += m.b[i][j];
        }
    }
    return tmp;
}


matr::matr(int d, double** x) {

    countmatr++;
    number = countmatr;
    cout << "Constructor mart(int d, double** x) made new matrix #" << number << endl;
    this->dim = d;
    this->b = (double**) new double* [dim];

    for (int i = 0; i < dim; i++) {
        this->b[i] = new double[dim];

        for (int j = 0; j < dim; j++) {
            this->b[i][j] = x[i][j];
        }
    }
}

matr::matr(int d, int o) { // о - декоративный элемент, который нам не нужен. 
    //чисто для отличия от другого конструктора
    countmatr++;
    number = countmatr;
    cout << "Constructor matr(int,int) created matrix #" << number << endl;

    dim = d;

    b = new double* [dim];
    for (int i = 0; i < dim; i++) {
        b[i] = new double[dim];
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << "Enter elem #(" << i << "," << j << ") : ";
            cin >> b[i][j];
        }
    }
}

matr::matr() {

    countmatr++;
    number = countmatr;
    cout << "Constructor matr() made new matrix #" << number << " with dim = 0" << endl;

    dim = 0;
    b = new double* [dim];
}

matr::matr(int d) {  // создаёт матрицу размерности d и заполняет её нулями

    countmatr++;
    number = countmatr;
    cout << "Constructor matr(int d) made new matrix #" << number << " with dim = " << d << endl;

    this->dim = d;
    this->b = new double* [dim];

    for (int i = 0; i < dim; i++) {
        this->b[i] = new double[dim];
        for (int j = 0; j < dim; j++) {
            this->b[i][j] = 0;
        }
    }
}

matr::matr(matr& m) {

    countmatr++;
    number = countmatr;
    cout << "Constructor matr(matr& m) made new matrix #" << number << " by coping matr# " << m.number << endl;

    this->dim = m.dim;
    b = (double**) new double* [dim];
    for (int i = 0; i < dim; i++) {
        b[i] = (double*) new double[dim];
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            this->b[i][j] = m.b[i][j];
        }
    }

}

matr::~matr() {

    cout << "The matr you`ve deleted is number " << number << endl;
    for (int i = 0; i < dim; i++) {
        delete[]b[i];
    }
    delete[]b; //удалили основной массив. Это деструктор вложенного объекта
}

matr& matr::ObrDiag(matr& m) {
    cout << "Obr Diag Matrix #" << m.number << ":\n";


    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == j) {
                if (b[i][j] == 0) {
                    cout << "Unfortunately, there is a zero on the main diagonal of the matrix. But I will return to you what I have already processed. Change the matrix and try again." << endl;
                    return m;
                }
                else {
                    double n = m.b[i][j];
                    m.b[i][j] = 1 / n;
                }

            }
            else {
                m.b[i][j] = 0;
            }
        }
    }
    return m;
}


void matr::print() const {
    cout << "Matrix #" << number << ":\n";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
}



int main()

{
    cout << "\n*** VECTOR ***\n";

    int d1 = 3;
    double* arr_d1 = new double[d1];
    for (int i = 0; i < d1; i++)
    {
        cout << "Enter elem #" << i << ": ";
        cin >> arr_d1[i];
    }

    int d2 = 3;
    double* arr_d2 = new double[d2];
    for (int i = 0; i < d2; i++)
    {
        cout << "Enter elem #" << i << ": ";
        cin >> arr_d2[i];
    }

    cout << "\n*** CONSTRUSTION ***\n";
    vector vect_d1(d1, arr_d1);
    vect_d1.print();

    vector vect_d2(d2, arr_d2);
    vect_d2.print();

    cout << "\n*** MULTIPLICATION ***\n";
    double mult_val = vect_d1 * vect_d2;
    //cout << "mult_val = " << mult_val << endl;

    cout << "\n*** EXTRACTION ***\n";
    vect_d2[0];

    cout << "\n*** CONSTRUCTION ***\n";
    int d3 = 3;
    vector vect_d3(d3);
    vect_d3.print();

    cout << "\n*** EQUATING ***\n";
    vect_d3 = vect_d2;
    cout << "Now ";
    vect_d3.print();

    cout << "\n*** CONSTRUCTION ***\n";
    vector vect_d4(3);
    vect_d4.print();

    cout << "\n*** SUBSTRACTION ***\n";
    vect_d4 = vect_d2 - vect_d1;
    vect_d4.print();

    cout << "\n*** ++ ***\n";
    vector vect_10(d1);
    vect_10 = ++vect_10;
    vect_10.print();

    cout << "\n*** MATRIX ***\n";

    int d = 3;
    int o = 0;

    matr matr_1(d, o);
    matr_1.print();

    matr matr_2(d, o);
    matr_2.print();

    matr matr_3(matr_1);
    matr_3.print();

    matr matr_4(3);
    matr_4.print();


    cout << "\n*** SUM ***\n" << endl;

    matr matr_5(3);
    matr_5 = matr_2 + matr_1;
    matr_5.print();


    cout << "\n*** SUB ***\n" << endl;

    matr matr_6(3);
    matr_6 = matr_4 - matr_2;
    matr_6.print();

    cout << "\n*** NO ***\n" << endl;

    matr matr_7(3);
    matr_7 = -matr_3;
    matr_7.print();

    cout << "\n*** MUL ***\n" << endl;

    matr matr_8(3);
    matr_8 = matr_6 * 2;
    matr_8.print();

    cout << "\n*** MATR MUL ***\n" << endl;

    matr matr_9(3);
    matr_9 = matr_6 * matr_7;
    matr_9.print();

    cout << "\n*** VECT MATR MUL ***\n" << endl;

    int m1 = 3;
    double* arr_m1 = new double[m1];
    for (int i = 0; i < m1; i++) {
        cout << "Enter elem #" << i << ": ";
        cin >> arr_m1[i];
    }

    cout << "\n*** += ***\n" << endl;
    matr matr_10(3);
    matr_10 = matr_6 += matr_7;
    matr_10.print();

    return 0;

}
