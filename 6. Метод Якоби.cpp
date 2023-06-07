#include <windows.h>
#include <iostream>

using namespace std;

// Будем перегружать: -(vect, vect); = friend, определены вне класса
// =(vect), *(vect), [](i);
// Если оператор внутри класса - то, что до него = this, то, что после - автоматич. в скобках
// ДОМА: friend: *(n, vect)
// intro: +(vect),*(n), -(),
// Оператор = функция, но название другое
// this нужен, чтобы избегать конфликта имён

class vector {
private:
    int dim; // размерность вектора, то, какое мерное пространство. dim = dimencion
    double* v; // звездочка говорит о том, что это массив, одномерный массив v.
    int number; // номер - нужно чтобы отличать один вектор от другого без распечатывания
    friend vector& operator-(vector& op, vector& vect);
    friend vector& operator*(int n, vector& vect);
    friend class matr;
    friend vector jacobi(class matr& A, vector& B);
public:
    static int count; // про статик читаем сами отдельно. переменная - член класса. Значит, она создана изначально
    // count - порядковый номер вектора.
    // инициализируется один раз, удаляется тоже один раз, когда прога завершена, значение можно менять.
    // Отложенное объявление функций класса:
    void print(); // процедура распечатывания
    vector(); // Конструктор без параметров - пустой массив, ВСЕГДА В НАШЕМ СЛУЧАЕ, МЫ ТАК РЕШИЛИ
    vector(int d); // Создаст вектор заполнен нулями
    vector(int d, double* var); // DZ
    vector(vector& vect); // передали по ссылке какой-то вектор
    ~vector();
    double operator*(vector& vect); // Оператор умножения вект на вект
    vector& operator*(int n); // умножение вектора на число
    vector& operator+(vector& vect); //сложим два вектора
    vector& operator-(); // переворот вектора на отрицание
    bool operator!=(vector& vect);
    double operator[](int i); // Вытащить конкретный элемент вектора
    vector& operator=(vector& vect); //присваивание vector&
};

// статическую переменную нельзя задавать значением внтури класса, так что:

int vector::count = 0;

vector& vector::operator*(int n) {  // умножение вектора на число (не friend)
    cout << "Multiplication vector #" << number << " with number " << n << endl;
    static vector tmp(dim);  // создаём вектор размерности dim, заполненный нулями
    // это было для нового вектора
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = n * v[i];
    }
    return tmp;
}

bool vector::operator!=(vector& vect) {
    cout << "Vector inequality #" << number << " with vector #" << vect.number << endl;
    int m = 0;
    for (int i = 0; i < dim; i++) {
        if (v[i] != vect.v[i]) {
            m++;
        }
    }
    if (m != dim) {
        return true;
    }
    else if (m == dim) {
        return false;
    }
}

vector& operator*(int n, vector& vect) {  // умножение вектора на число (friend)
    cout << "FRIEND Multiplicating vector#" << vect.number << " with number " << n << endl;
    static vector tmp(vect.dim);  // новый вектор для результата (пока там нули)
    for (int i = 0; i < vect.dim; i++) {
        tmp.v[i] = vect.v[i] * n;
    }
    return tmp;
}

vector& vector::operator+(vector& vect) {
    cout << "Summarizing vector #" << number << " with vector #" << vect.number << endl;
    static vector tmp(dim); // создали вектор той же размерности, но заполнили в начале нулями
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = v[i] + vect.v[i];
    }
    return tmp;
}

vector& vector::operator-() {
    cout << "Negation vector #" << number << endl;
    static vector tmp(dim); // создали вектор той же размерности, но заполнили в начале нулями
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = -v[i];
    }
    return tmp;
}


double vector::operator*(vector& vect) { // Записываем скалярное умножение вектора на вектор
    static double tmp = 0;
    for (int i = 0; i < dim; i++) {
        tmp += v[i] * vect.v[i];
    }
    cout << "Scalar Multiplication (vector #" << number << ", vector #" << vect.number << ") = " << endl;
    return tmp;
}

double vector::operator[](int i) {
    cout << "Getting element #" << i << " from vector #" << number << endl;
    return v[i];
}

vector& vector::operator=(vector& vect) {
    cout << "Equating vector #" << number << " to vector #" << vect.number << endl;
    for (int i = 0; i < dim; i++) {
        this->v[i] = vect.v[i]; // this можно не прописывать, а можно прописать, разницы не будет
    }
    return *this;
}

// Указатель this неявно используется внутри метода для ссылок на элементы объекта.В явном виде этот указатель применяется
// в основном для возвращения из метода указателя (return this;) или ссылки (return *this;) на вызвавший объект


vector& operator-(vector& op, vector& vect) {
    cout << "Substraсtion vector #" << vect.number << " from vector #" << op.number << endl;
    static vector tmp(op.dim); // создали вектор той же размерности, но заполнили в начале нулями для результата
    for (int i = 0; i < op.dim; i++) {
        tmp.v[i] = op.v[i] - vect.v[i];
    }
    return tmp;
}

// Доступ к элементам структур и классов может осуществляться двумя операциями:
// операцией точки(.) или операцией стрелки(->).
// Если доступ осуществляется через объект, то используется операция точка.


vector::~vector() {
    cout << "You deleted vector #" << number << endl;
    delete[]v;
}

vector::vector() { //
    count++; // каждый раз, когда мы обращаемся к конструктору - каунт увеличивается.
    number = count; // менять приватную переменную можно из любой функции внутри класса. Через функцию можно, напрямую нельзя
    cout << "Constructor vector() made vector #" << number << endl;
    dim = 0;
    v = new double[dim]; // Мы создали массив, длина которого dim
}

vector::vector(int d, double* var) {
    count++;
    number = count;
    cout << "Constructor vector(int d, double* var) made vector #" << number << endl;
    dim = d;
    v = new double[dim];
    for (int i = 0; i < dim; i++) {
        v[i] = var[i]; // приравниваем элемент массива v к элементу массива var
    }
}

vector::vector(int d) { // конструктор, принимающий только размерность
    // пространства и заполняющий вектор нулями
    count++;
    number = count;
    cout << "Constructor vector(int d) made vector #" << number << endl;
    dim = d;
    v = new double[dim];
    for (int i = 0; i < dim; i++) {
        v[i] = 0;
    }
}

vector::vector(vector& vect) {
    // Передали вектор в конструктор, который создаёт ещё один ТАКОЙ ЖЕ
    count++;
    number = count;
    cout << "Constructor vector(vector& vect) made vector #" << number << "by coping vector #" << vect.number << endl;
    // vect.number - номер того вектора, который мы копируем
    dim = vect.dim; // Размерность взяли из копируемого вектора. Обратились через точку. По ссылке.
    v = new double[dim];
    for (int i = 0; i < dim; i++) { // теперь мы заполняем массив,
        //берём первый элемент другого вектора и приравниваем к нему наш первый элемент нового вектора
        //А = (х1,х2,х3). И эти значения мы перекладываем в какое-то С, которое теперь тоже равно (x1,x2,x3).
        v[i] = vect.v[i];
    }
}

void vector::print() {
    if (dim != 0) {
        cout << "Vector #" << number << " (";
        for (int i = 0; i < dim; i++) {
            cout << v[i] << ",";
        }
        cout << ")" << endl;
    }
    else {
        cout << "Vector #" << number << " with dim = 0" << endl;
    }
}

class matr {
    int dim;
    double** b;
    int number;  // порядковый номер
    friend matr& operator*(double c, matr& m);  // friend operator умножение матрицы на число
    friend class vector; // Дружественный класс векторов
    friend vector jacobi(matr& A, vector& B);
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
    matr operator+(const matr& m) const;
    matr& operator-(const matr& m);  // указатель на матрицу
    matr& operator-();  // отрицание матрицы
    matr operator*(const matr& m) const;
    matr& operator=(const matr& m);
    matr& operator*(double c);  // умножение на число
    matr& operator++();
    vector& operator*(const vector& vect) const;
    void printSLU(vector& vector);
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

matr& matr::operator++() {
    cout << "Increase matrix #" << number << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            b[i][j] = b[i][j] + 1;
        }
    }
    return *this;
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

void matr::printSLU(vector& vector) {
    cout << "Матрица и вектор для СЛАУ: " << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << b[i][j] << "   ";
        }
        cout << "|" << vector.v[i] << endl;
    }
}

vector jacobi(matr& matrix, vector& vect) {
    const double eps = 0.001;
    int it = 0;
    int maxit = 100;
    vector fst(vect.dim);
    fst = vect;
    vector norm(vect.dim);
    vector tmp(matrix.dim);
    matr ed_m(matrix.dim, 9);
    matr matrix_1(matrix.dim);
    matrix_1 = matrix.ObrDiag(matrix);
    matr p1;
    p1 = (ed_m - (matrix_1 * matrix));
    vector p2;
    p2 = matrix_1 * vect;
    do {
        fst = p1 * fst + p2;
        norm = matrix * fst - vect;
    } while (norm * norm < eps && it != maxit);
    it++;
    return fst;
}
/*    if (it <= maxit){
        cout << "Решение найдено за " << it << " итераций:\n";
        first_step.print();
    }
    else {
        cout << "Не удалось достичь заданной точности за " << maxit << " итераций.";
        first_step.print();
    }
    norm = A.dim * X.v[0] - tmp.v[0];
    do {
       for (int i = 0; i < A.dim; i++) { // Вычисление очередной итерации
            tmp.v[i] = B.v[i];
            for (int g = 0; g < A.dim; g++) {
                if (i != g)
                    tmp.v[i] -= A.b[i][g] * X.v[g];
            }
            tmp.v[i] /= A.b[i][i];
        }
        for (int h = 0; h < A.dim; h++) {
            if (fabs(X.v[h] - tmp.v[h]) > norm)
                norm = fabs(X.v[h] - tmp.v[h]);
            X.v[h] = tmp.v[h]; //запись результата в искомый массив
        }
        it++; */

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru");

    int d1 = 3;
    double* arr_d1 = new double[d1];
    for (int i = 0; i < d1; i++) {
        cout << "Enter elem #" << i << ": ";
        cin >> arr_d1[i];
    }

    cout << "--------------------------------------------\n";
    cout << "ВЕКТОР" << endl;
    vector vect(d1, arr_d1);
    vect.print();

    int d = 3;
    int o = 0;
    cout << "--------------------------------------------\n";
    cout << "МАТРИЦА" << endl;

    matr matr_1(d, o);
    matr_1.print();

    cout << "--------------------------------------------\n";
    matr_1.printSLU(vect);

    cout << "--------------------------------------------\n";
    cout << "РЕАЛИЗАЦИЯ МЕТОДА ЯКОБИ\n";
    jacobi(matr_1, vect);

    return 0;
}