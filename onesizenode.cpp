#include <iostream>
using namespace std;


//даем определние типа узла
struct Node {
    int value; //значение элемента
    Node *next; // указатель на сл узел

    Node(int v, Node *n) { //конструктор
        value = v; // сохраним вал и некст заданные значения
        next = n;
    }
};

class LinkedList { //сам список
    Node *head, *tail;
    int elementCount; //чтоб спискок знал сколько в нем элементов

public: //конструктор, который создаст пустой список
    LinkedList() {
        head = nullptr; //если указатель никуда не ссылается = нулл значение
        tail = nullptr;
        elementCount = 0; // при создании списка - 0 элементов в нем
    }

    ~LinkedList() { // деструктор для очистки памяти (очистка динам памяти по оконачнии работы)
        //сначала пишем popFront который удаляет
        while(!empty()) {
            popFront(); // тупо будем вызывать удаление 1 элемента пока спискок не опустеет
        }
    }

    //получаем указатель на элемент по индексу(для добавление в разные места списка значений)
    Node *getNode(int index) {
        Node *n = head;
        for (int i = 0; i < index; i++)
            n = n->next;
        return n;
    }
    // int &operator [] (int index) {
    //     return getNode(index)->value;
    // }


    int size() const {
        return elementCount;
    }
    bool empty() const {
        return elementCount == 0;
    }



    //Добавление нового элемента в начало | когда списко пуст
    void pushFront(int value) {
        head = new Node(value, head); //(значение, сл узел) | сразу запишем адрес нового узла в head
        elementCount++;

        if(tail == nullptr)
            tail = head;
    }

    //Удаление элемента из начала
    void popFront() {
//тут короче загвоздка что если мы сначала удалим элемент то не найдем концы его
//или сначала удалим указатель - потярем элемент
// наш спаситель - временная переменная в которой сохрания укзаатель head -> next
        Node *nextHead = head->next; //временная переменная которая сохранит указатель
        delete head; // удалим элемент
        head = nextHead; //наша башка теперь это сл элемент который дернули из указателя временной переменной
        elementCount--;

        if (head == nullptr)
            tail = nullptr;
    }



    //добавление элемента по ИНДЕКСУ (l.getNode(ИндекС ЭлементА после которого вставить), элемент)
    void insterAfter(Node *elem, int value) {
        elem->next = new Node(value , elem->next);
        elementCount++;

        if (tail == elem)
            tail = tail->next; //переставим на сл эл если вставили в конец
    }

    //удаляение элемента по ИНДЕКСУ
    void eraseAfter(Node *elem) {
        Node *nextElem = elem->next; //вспомогат указ на удал элемент
        elem -> next = nextElem->next; //перекинем элемент в обход удаляемого
        delete nextElem;
        elementCount--;

        if(tail == nextElem)
            tail = elem; //если удалили ласт элемент
    }


    //на этом моменте мы добавим tail - указатель на последний элемент списка
    //так производительность добавление элемента в конце вырастет - не будет трогать getNode
    //Вставка в конец связного списка
    void pushBack(int value) {
        if (empty())
            pushFront(value);
        else
            insterAfter(tail, value);
    }

    //popBack эффективно не реализовать(

    //вывод элементов пробегает по всем узлам и выводит
    void print() const {
        for (Node *n = head; n; n = n-> next)
            cout << n->value<< " ";
        cout << "\n";

    }
};



int main() {

    LinkedList l;

    l.pushFront(12);
    l.pushFront(34);
    l.pushBack(56);

    l.insterAfter(l.getNode(1), 99);

    l.print();

    l.eraseAfter(l.getNode(1));

    l.print();
}