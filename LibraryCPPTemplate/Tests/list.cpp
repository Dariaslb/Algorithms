#include <iostream>
#include "list.h"

typedef List<int> MyList;

int main()
{
    MyList *list = new MyList;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list->erase(list->first());

    if (list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List: ";
    list->foreach([&](int data) {
        std::cout << data << " ";
    });
    std::cout << "\n";
    std::cout << "Comariki" << std::endl;

    delete list;
}
