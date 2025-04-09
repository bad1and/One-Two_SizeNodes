#include <iostream> // подключаем ввод/вывод
using namespace std; // чтобы не писать std:: каждый раз

// даем определение типа узла двусвязного списка
struct DNode {
    int value; // значение элемента
    DNode *prev; // указатель на предыдущий узел
    DNode *next; // указатель на следующий узел

    DNode(int v, DNode *p = nullptr, DNode *n = nullptr) { // конструктор
        value = v; // запомним значение
        prev = p; // предыдущий узел
        next = n; // следующий узел
    }
};

// сам класс списка
class DoubleLinkedList {
    DNode *head, *tail; // начало и конец списка
    int elementCount; // количество элементов в списке

public:
    DoubleLinkedList() { // конструктор пустого списка
        head = nullptr; // изначально список пуст — ни начала, ни конца
        tail = nullptr;
        elementCount = 0; // ноль элементов
    }

    ~DoubleLinkedList() { // деструктор — удалим всё из памяти
        while (!empty()) { // пока не опустеет
            popFront(); // удаляем первый элемент
        }
    }

    bool empty() const { // проверить пуст ли список
        return elementCount == 0; // вернем true если элементов нет
    }

    int size() const { // вернуть размер списка
        return elementCount;
    }

    DNode* getNode(int index) { // получить указатель на элемент по индексу
        if (index < 0 || index >= elementCount) return nullptr; // проверим границы
        DNode* n = head; // начнем с головы
        for (int i = 0; i < index; i++) // пробежимся index раз
            n = n->next;
        return n; // вернем указатель
    }

    int& operator[](int index) { // оператор [] — получить значение по индексу
        return getNode(index)->value; // достаем значение
    }

    void pushFront(int value) { // добавить в начало
        DNode *newNode = new DNode(value, nullptr, head); // создаем новый узел, указ на след = head
        if (head != nullptr) // если список не пуст
            head->prev = newNode; // теперь предыдущий у старой головы — новый узел
        head = newNode; // сдвигаем голову
        if (tail == nullptr) // если был пуст
            tail = head; // и хвост тоже теперь указывает на новый узел
        elementCount++; // увеличим счетчик
    }

    void pushBack(int value) { // добавить в конец
        DNode *newNode = new DNode(value, tail, nullptr); // создаем узел, prev = tail
        if (tail != nullptr) // если список не пуст
            tail->next = newNode; // старый хвост указывает на новый узел
        tail = newNode; // сдвигаем хвост
        if (head == nullptr) // если список был пуст
            head = tail; // и голова тоже указывает на новый
        elementCount++; // счетчик++
    }

    void popFront() { // удаление из начала
        if (head == nullptr) return; // если пуст — ничего не делаем
        DNode *temp = head; // запомним старую голову
        head = head->next; // сдвигаем голову на след элемент
        if (head != nullptr) // если есть след элемент
            head->prev = nullptr; // обнуляем prev
        else
            tail = nullptr; // если список стал пуст
        delete temp; // удалим старую голову
        elementCount--; // уменьшаем размер
    }

    void popBack() { // удалить из конца
        if (tail == nullptr) return; // если пуст — выходим
        DNode *temp = tail; // запомним старый хвост
        tail = tail->prev; // сдвигаем хвост
        if (tail != nullptr) // если есть предыдущий
            tail->next = nullptr; // обнулим указатель вперёд
        else
            head = nullptr; // если список стал пуст
        delete temp; // удалим элемент
        elementCount--; // уменьшим размер
    }

    void insertAfter(DNode *node, int value) { // вставка после узла
        if (node == nullptr) return; // если указатель пустой — выходим
        DNode *newNode = new DNode(value, node, node->next); // создаем новый узел (prev=node, next=node->next)
        if (node->next != nullptr) // если после node что-то было
            node->next->prev = newNode; // у следующего обновим prev
        else
            tail = newNode; // если вставили в конец — двигаем tail
        node->next = newNode; // у текущего элемента обновим next
        elementCount++; // увеличим размер
    }

    void insertBefore(DNode *node, int value) { // вставка перед узлом
        if (node == nullptr) return;
        DNode *newNode = new DNode(value, node->prev, node); // prev и next соответствующие
        if (node->prev != nullptr) // если перед node что-то есть
            node->prev->next = newNode; // связываем
        else
            head = newNode; // если вставили в голову — двигаем head
        node->prev = newNode; // у текущего prev = новый
        elementCount++;
    }

    void eraseAfter(DNode *node) { // удаление узла после указанного
        if (node == nullptr || node->next == nullptr) return; // если нечего удалять
        DNode *toDelete = node->next; // сохраним того, кого удалим
        node->next = toDelete->next; // пропустим удаляемый
        if (toDelete->next != nullptr) // если есть узел после удаляемого
            toDelete->next->prev = node; // у него обновим prev
        else
            tail = node; // если удалили хвост — обновим tail
        delete toDelete; // удалим
        elementCount--;
    }

    void eraseNode(DNode *node) { // удаление по указателю
        if (node == nullptr) return;
        if (node == head)
            popFront(); // если это голова — поп фронт
        else if (node == tail)
            popBack(); // если хвост — поп бэк
        else {
            node->prev->next = node->next; // перепрыгиваем через удаляемый узел
            node->next->prev = node->prev;
            delete node;
            elementCount--;
        }
    }

    void print() const { // вывод элементов в прямом порядке
        for (DNode *n = head; n; n = n->next)
            cout << n->value << " ";
        cout << "\n";
    }

    void printReverse() const { // вывод в обратном порядке
        for (DNode *n = tail; n; n = n->prev)
            cout << n->value << " ";
        cout << "\n";
    }
};

// тестим всё в main
int main() {
    DoubleLinkedList dl; // создаем список

    dl.pushFront(10); // вставим 10 в начало
    dl.pushBack(20); // добавим 20 в конец
    dl.pushBack(30); // ещё один конец
    dl.pushFront(5); // 5 в самое начало

    dl.print(); // печатаем слева направо
    dl.printReverse(); // справа налево

    dl.insertAfter(dl.getNode(1), 15); // вставим 15 после 10
    dl.print();

    dl.insertBefore(dl.getNode(3), 17); // вставим 17 перед 20
    dl.print();

    dl.eraseAfter(dl.getNode(1)); // удалим 15
    dl.print();

    dl.eraseNode(dl.getNode(2)); // удалим 17 напрямую
    dl.print();

    dl.popFront(); // удалим начало (5)
    dl.popBack(); // удалим конец (30)
    dl.print();

    dl[0] = 100; // меняем 10 на 100
    dl[1] = 200; // 20 на 200
    dl.print(); // финальный вывод
}
