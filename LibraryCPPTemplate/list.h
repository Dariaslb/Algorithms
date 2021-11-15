#ifndef LIST_H
#define LIST_H
#include <functional>
#include "cstddef"

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() const { return _data; }
        explicit Item(Data data, Item* next = nullptr, Item* prev = nullptr): _data(data), _next(next), _prev(prev) {}
        void setPrev(Item* item) {_prev = item;}
        void setNext(Item* item) {_next = item;}
    private:
        // internal data here
        Item* _next;
        Item* _prev;
        Data _data;
    };

    // Creates new list
    List() : _head(nullptr), _tail(nullptr)
    {

    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* current = _head;
        while (current != _tail) {
            _head = current->next();
            delete current;
            current = _head;
        }
        delete _head;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return _head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        if (_head == nullptr) {
            _head = new Item(data);
            _tail = _head;
            return _tail;
        } else {
            Item* newItem = new Item(data);
            _head->setPrev(newItem);
            newItem->setNext(_head);
            _head = newItem;
            return newItem;
        }
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        // Создаём новый Item
        Item* newItem = new Item(data);
        // Указывем, какой Item будет после него
        newItem->setNext(item->next());
        // Если следуйщий элемент узла не nullptr, то этому элементу,в качестве предыдущего, мы указываем созданный узел
        if (item->next() != nullptr) {
            item->next()->setPrev(newItem);
        }
        // Указываем для нового Item предыдущий для него
        newItem->setPrev(item);
        // И для того узла, после которого мы вставляем новый элемент, указываем в качестве следующего этот элемент
        item->setNext(newItem);
        // Возвращаем новый элемент.
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        auto* prev = item->prev();
        auto* next = item->next();
        if (prev != nullptr) {
            prev->setNext(item->next());
        } else {
            _head = next;
        }
        if (next != nullptr) {
            next->setPrev(item->prev());
        } else {
            _tail = prev;
        }
        delete item;
        return next;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void foreach(std::function<void(Data const& item)> fun) {
        for (auto item = this->first() ; item ; item = item->next())
        {
            fun(item->data());
        }
    }
private:
    // private data should be here
    //List *data_list; Нинада так больше
    Item* _tail;
    Item* _head;
};

#endif
