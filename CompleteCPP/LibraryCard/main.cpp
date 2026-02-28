#include <stdlib.h>
#include "LibraryCard.hpp"


int main(){

    LibraryCard first = LibraryCard("Person 1");
    LibraryCard second = LibraryCard("Person 2");

    first.checkoutBook();
    first.checkoutBook();
    second.checkoutBook();

    first.print();
    second.print();

    return EXIT_SUCCESS;
}