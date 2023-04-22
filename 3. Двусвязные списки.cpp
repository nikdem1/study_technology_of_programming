#include <iostream>

using namespace std;

struct poison {
    string name;
    string book;
    string author;
    poison* next;
    poison* prev;
};

void printnode(poison* toxin) {
    if (toxin == NULL) {
        cout << "This is NULL not node\n";
    }
    else {
        cout << "\n\tProduct: " << toxin->name << "\n\tMemoryAddr: " << toxin << "\n\tNext: " << toxin->next << "\n\tPrev: " << toxin->prev << endl;
    }
}

void addfirst(poison*& toxin, string nm, string pr, string am) {

    poison* newpoison = new poison;
    newpoison->name = nm;
    newpoison->book = pr;
    newpoison->author = am;

    newpoison->next = toxin; // голову перемещаем за новый элемент 
    newpoison->prev = NULL; // предыдущий - пустота, т.к это первый элемент

    if (toxin != NULL) { // Если у нас голова не ноль - то есть, добавляем мы просто первые элемент, а не самый первый в списке
        toxin->prev = newpoison; // То тогда и ещё одна ссылка нужна - от головы назад к новой голове
    }

    toxin = newpoison;
}


void addlast(poison*& toxin, string nm, string pr, string am) {
    if (toxin == NULL) {
        addfirst(toxin, nm, pr, am);
        return;
    }

    poison* tmp = toxin;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    poison* newpoison = new poison;
    newpoison->name = nm;
    newpoison->book = pr;
    newpoison->author = am;

    newpoison->next = NULL; // Следом - пусто
    newpoison->prev = tmp; // Предыдущий элемент - тот, который раньше был последним
    tmp->next = newpoison; // у предыдущего элемента обновили ссылку на следующий

}



void addafter(poison*& toxin, string nm, string pr, string am, string af_name) {

    if (toxin == NULL) cout << "The list is empty\n";

    poison* tmp = toxin;

    while (tmp->next != NULL && tmp->name != af_name) {
        tmp = tmp->next;
    }

    if (tmp->next == NULL && tmp->name != af_name) {
        cout << "Element not found in list\n";
        return;
    }

    poison* newpoison = new poison;
    newpoison->name = nm;
    newpoison->book = pr;
    newpoison->author = am;

    newpoison->next = tmp->next; // следом за новым элементом
    newpoison->prev = tmp; // предыдущий - тот, после чего вставляем
    if (tmp->next != NULL) { // Если вставляем не последний элемент, то нужна ссылка от следующего назад
        tmp->next->prev = newpoison;
    }
    tmp->next = newpoison; // Обновили ссылку от пердыдущего к новому элементу

}

void addbefore(poison*& toxin, string nm, string pr, string am, string inc_name) {

    // Список пустой, если голова пустая

    if (toxin == NULL) {
        cout << "The list is empty\n";
        return;
    }

    //Голова - то перед чем хотим вставить

    if (toxin->name == inc_name) {
        addfirst(toxin, nm, pr, am);
        return;
    }

    //Две временные переменные в которые передаем указатель на голову
    poison* tmp = toxin;

    while (tmp->next != NULL && tmp->name != inc_name) {
        tmp = tmp->next;
    }

    // Если дошли до конца, и не нашли
    if (tmp->next == NULL && tmp->name != inc_name) {
        cout << "Element not found in list\n";
        return;
    }

    //Создаём узел
    poison* newpoison = new poison;
    newpoison->name = nm;
    newpoison->book = pr;
    newpoison->author = am;

    newpoison->next = tmp; // вставили наш элемент перед нужным
    newpoison->prev = tmp->prev; // Сказали, какой элемент предыдущий
    tmp->prev->next = newpoison; // обновили "следующий за предыдущим"
    tmp->prev = newpoison; // Обновили предыдущий для следующего

}

//void swap2(poison*& toxin, string inc_name1, string inc_name2) {}

void swap(poison*& toxin, string inc_name1, string inc_name2) {

    if (toxin == NULL) cout << "The list is empty\n";

    // Ищем первый узел

    poison* tmp = toxin;

    while (tmp->next != NULL && tmp->name != inc_name1) {
        tmp = tmp->next;
    }
    if (tmp->next == NULL && tmp->name != inc_name1) {
        cout << "Element not found in list\n";
        return;
    }
    poison* node1 = tmp;

    // Ищем второй узел

    tmp = toxin;

    while (tmp->next != NULL && tmp->name != inc_name2) {
        tmp = tmp->next;
    }
    if (tmp->next == NULL && tmp->name != inc_name2) {
        cout << "Element not found in list\n";
        return;
    }
    poison* node2 = tmp;



    poison* next1 = node1->next;
    poison* prev1 = node1->prev;
    poison* next2 = node2->next;
    poison* prev2 = node2->prev;

    if (node1->next == node2) {

        node1->next = next2;
        node1->prev = node2;

        node2->prev = prev1;
        node2->next = node1;

        if (node1->next != NULL) next2->prev = node1;
        if (node2->prev != NULL) prev1->next = node2;

    }
    else if (node2->next == node1) {

        node1->next = node2;
        node1->prev = prev2;

        node2->next = next1;
        node2->prev = node1;

        if (node2->next != NULL) next1->prev = node2;
        if (node1->prev != NULL) prev2->next = node1;

    }
    else {
        // cout«"Node1 before:\n";
        // printnode(node1);
        // cout«"Node2 before:\n";
        // printnode(node2);

        node1->prev = prev2;
        node1->next = next2;
        node2->prev = prev1;
        node2->next = next1;


        // cout«"tmp1 :\n";
        // printnode(tmp1);
        // cout«"tmp2 :\n";
        // printnode(tmp2);

        if (prev1 != NULL) {
            prev1->next = node2;
        }
        if (next1 != NULL) {
            next1->prev = node2;
        }
        if (prev2 != NULL) {
            prev2->next = node1;
        }
        if (next2 != NULL) {
            next2->prev = node1;
        }
    }

    // cout«"Node1 after:\n";
    // printnode(node1);
    // cout«"Node2 after:\n";
    // printnode(node2);

    if (node1->prev == NULL) {
        toxin = node1;
    }
    if (node2->prev == NULL) {
        toxin = node2;
    }
}

void delet(poison*& toxin, string del_name) {

    //Случай, когда у нас нет элементов 

    if (toxin == NULL) {
        cout << "*************************************\n";
        cout << "The list is empty\n";
    }

    poison* tmp = toxin;


    //Случай, когда у нас ОДИН элемент и мы ХОТИМ его удалить 

    if (toxin->next == NULL && toxin->name == del_name) {
        //toxin = NULL;
        delete toxin;
        return;
    }

    //Случай, когда удаляем первый элемент 

    if (toxin->name == del_name) {
        toxin = toxin->next;
        delete tmp;
        toxin->prev = NULL;
        return;
    }


    //Случай, когда у нас ОДИН элемент и мы НЕ ХОТИМ его удалять. Иначе tmp будет NULL 

    if (toxin->next == NULL && toxin->name != del_name) {
        cout << "*************************************\n";
        cout << "Element not found in list\n";
        return;
    }

    //Базовый случай 

    while (tmp->next != NULL && tmp->name != del_name) {
        tmp = tmp->next;
    }


    //Случай, когда у нас нет элемента в списке, но элементов больше одного 

    if (tmp->next == NULL && tmp->name != del_name) {
        cout << "*************************************\n";
        cout << "Element not found in list\n";
        return;
    }


    tmp->prev->next = tmp->next;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp->prev;
    }

    delete tmp;
}


void printlistrev(poison* toxin) {
    if (toxin == NULL) {
        cout << "This list is empty\n";
    }
    else {
        poison* prev = nullptr;
        poison* tmp = toxin;
        while (tmp != NULL) {
            prev = tmp;
            tmp = tmp->next;

        }
        tmp = prev;
        while (tmp != NULL) {
            cout << "\nProduct: " << tmp->name << "\nbook: " << tmp->book << "\nauthor: " << tmp->author << endl;
            tmp = tmp->prev;
        }
    }
}

void printlist(poison* toxin) {
    if (toxin == NULL) {

        cout << "This list is empty\n";
    }
    else {
        poison* tmp = toxin;
        while (tmp != NULL) {
            cout << "\nProduct: " << tmp->name << "\nbook: " << tmp->book << "\nauthor: " << tmp->author << endl;
            tmp = tmp->next;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    poison* toxin = NULL;

    string name1 = "Стрихнин";
    string book1 = "Загадочное происшествие в Стайлзе";
    string author1 = "Агата Кристи";

    string name2 = "Кантарелла";
    string book2 = "Невеста Борджа";
    string author2 = "Джинн Калогридис";

    string name3 = "Белый олеандр";
    string book3 = "Белый олеандр";
    string author3 = "Джанет Фитч";

    string name4 = "Мышьяк";
    string book4 = "Королева Марго";
    string author4 = "Александр Дюма";

    string name5 = "Настой Белены";
    string book5 = "Гамлет, принц Датский";
    string author5 = "Уильям Шекспир";

    string name6 = "Цианистый калий";
    string book6 = "Таймлесс";
    string author6 = "Керстин Гир";

    string name7 = "Наперстянка";
    string book7 = "Свидание со смертью";
    string author7 = "Агата Кристи";

    printlist(toxin);

    cout << "*************************************";
    addfirst(toxin, name1, book1, author1);
    printlist(toxin);

    cout << "*************************************";
    addfirst(toxin, name2, book2, author2);
    printlist(toxin);

    cout << "*************************************";
    addbefore(toxin, name3, book3, author3, "Стрихнин");
    printlist(toxin);

    cout << "*************************************";
    addlast(toxin, name4, book4, author4);
    printlist(toxin);



    cout << "*************************************";
    addlast(toxin, name6, book6, author6);
    printlist(toxin);

    cout << "*************************************";
    addafter(toxin, name7, book7, author7, "Цианистый калий");
    printlist(toxin);

    cout << "*************************************";
    addafter(toxin, name5, book5, author5, "Белый олеандр");
    printlist(toxin);


    cout << "SWAP*************************************";
    swap(toxin, "Белый олеандр", "Настой Белены");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Настой Белены", "Кантарелла");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Стрихнин", "Мышьяк");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Кантарелла", "Белый олеандр");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Мышьяк", "Кантарелла");
    printlist(toxin);


    cout << "*************************************";
    delet(toxin, "Кантарелла");
    delet(toxin, "Белый олеандр");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Мышьяк", "Кантарелла");
    printlist(toxin);

    cout << "SWAP*************************************";
    swap(toxin, "Мышьяк", "Стрихнин");


    //Удаление всех элементов списка, можно проверить - работает
    // 
    //delet(toxin, "Настой Белены");
    //delet(toxin, "Стрихнин");
    //delet(toxin, "Мышьяк");
    //delet(toxin, "Цианистый калий");
    //delet(toxin, "Наперстянка");





    printlist(toxin);



    return 0;
}