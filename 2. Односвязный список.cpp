#include <iostream>

using namespace std;

struct actors {
    string name;
    string film;
    string genre;
    actors* next;
};

void addfirst(actors*& persons, string nm, string pr, string am) { // указатель на голову и элементы структуры
    actors* newactors = new actors; // выделяем память под новую структуру, адрес сохраняется в указатель
    newactors->name = nm;
    newactors->film = pr;
    newactors->genre = am;
    newactors->next = persons; // создание ссылки, содержащей адрес следующего элемента

    persons = newactors;
}


void addlast(actors*& persons, string nm, string pr, string am) { // указатель на голову и элементы структуры
    if (persons == NULL) { // если список пуст, то добавляем первый элемент
        addfirst(persons, nm, pr, am);
        return;
    }
    actors* tmp = persons; // создём указатель на голову самска, выделяем память
    while (tmp->next != NULL) { // пока не дошли до конца списка
        tmp = tmp->next; // продолжаем идти по списку
    }
    actors* newactors = new actors; // выделяем память под новую структуру, адрес сохраняется в указатель
    newactors->name = nm;
    newactors->film = pr;
    newactors->genre = am;
    newactors->next = NULL;
    tmp->next = newactors; // создание ссылки, содержащей адрес следующего элемента
}

void addbefore(actors*& persons, string nm, string pr, string am, string inc_name) { // указатель голову и на элементы структуры
    if (persons == NULL) cout << "The list is empty\n"; // список пуст
    if (persons->name == inc_name) { // inc_name - имя, до которого нужно добавить элемент
        addfirst(persons, nm, pr, am); // добавляем первый элемент перед inc_name
        return;
    }

    actors* tmp = persons; //создём указатель на голову списка, выделяем память
    actors* prev = persons; //создём указатель на предыдущий, устан. в голову, выделяем память

    while (tmp->next != NULL && tmp->name != inc_name) { // пока не вышли за пределы списка и пока tmp != inc_name
        if (tmp->next->name == inc_name) prev = tmp;
        tmp = tmp->next;
    }

    if (tmp->next == NULL && tmp->name != inc_name) { // элемент не в списке
        cout << "Element not found in list\n";
        return;
    }

    actors* newactors = new actors; // выделяем память под новую структуру, адрес сохраняется в указатель
    newactors->name = nm;
    newactors->film = pr;
    newactors->genre = am;

    newactors->next = tmp; // временная переменная на новый последний элемент
    prev->next = newactors;
}

void addafter(actors*& persons, string nm, string pr, string am, string af_name) {
    if (persons == NULL) cout << "The list is empty\n"; // список пуст
    actors* tmp = persons; // указываем голову списка

    while (tmp->next != NULL && tmp->name != af_name) { // идем по списку
        tmp = tmp->next;
    }
    if (tmp->next == NULL && tmp->name != af_name) {
        cout << "Element not found in list\n"; // элемент не списки
        return;
    }
    actors* newactors = new actors; // выделяем память под новую структуру, адрес сохраняется в указатель
    newactors->name = nm;
    newactors->film = pr;
    newactors->genre = am;
    newactors->next = tmp->next;
    tmp->next = newactors; // создание ссылки, содержащей адрес следующего элемента
}


void delet(actors*& persons, string del_name) {

    // случай, когда у нас нет элементов 

    if (persons == NULL) {
        cout << "*************************************\n";
        cout << "The list is empty\n";
    }

    actors* tmp = persons;
    actors* prev = persons;
    tmp = persons->next;

    // случай, когда удаляем первый элемент 

    if (persons->name == del_name) {
        persons = persons->next;
        delete prev;
        return;
    }

    // случай, когда у нас ОДИН элемент и мы ХОТИМ его удалить 

    if (persons->next == NULL && persons->name == del_name) {
        delete persons;
        return;
    }

    // случай, когда у нас ОДИН элемент и мы НЕ ХОТИМ его удалять. Иначе tmp будет NULL 

    if (persons->next == NULL && persons->name != del_name) {
        cout << "*************************************\n";
        cout << "Element not found in list\n";
        return;
    }

    // базовый случай 

    while (tmp->next != NULL && tmp->name != del_name) {
        prev = prev->next;
        tmp = tmp->next;
    }


    // случай, когда у нас нет элемента в списке, но элементов больше одного 

    if (tmp->next == NULL && tmp->name != del_name) {
        cout << "*************************************\n";
        cout << "Element not found in list\n";
        return;
    }


    prev->next = tmp->next;
    delete tmp;
}


void printlist(actors* persons) {
    if (persons == NULL) {
        cout << "*************************************\n";
        cout << "This list is empty\n";
    }
    else {
        cout << "*************************************\nГлавные герои в фильмах\n";
        actors* tmp = persons;
        while (tmp != NULL) {
            cout << "\nГлавный герой: " << tmp->name << "\nФильм: " << tmp->film << "\nЖанр: " << tmp->genre << endl;
            tmp = tmp->next;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    actors* persons = NULL;
    string name1 = "Крис Вашингтон";
    string film1 = "Прочь";
    string genre1 = "Ужасы/Триллер";

    string name2 = "Хантер";
    string film2 = "Глотай";
    string genre2 = "Драма/Психологический триллер";

    string name3 = "Эвелин Вонг";
    string film3 = "Всё, везде и сразу";
    string genre3 = "Фантастика/Комедия/Боевик";

    string name4 = "Стивен Мёрфи";
    string film4 = "Убийство священного оленя";
    string genre4 = "Драма/Психологический триллер";

    string name5 = "Марианна";
    string film5 = "Портрет девушки в огне";
    string genre5 = "Драма/Милодрама";

    printlist(persons);

    addfirst(persons, name1, film1, genre1);
    printlist(persons);

    addfirst(persons, name2, film2, genre2);
    printlist(persons);

    addbefore(persons, name3, film3, genre3, "Хантер");
    printlist(persons);

    addlast(persons, name4, film4, genre4);
    printlist(persons);

    addafter(persons, name5, film5, genre5, "Эвелин Вонг");
    printlist(persons);


    delet(persons, "Хантер");
    delet(persons, "Эвелин Вонг");
    printlist(persons);

    return 0;
}