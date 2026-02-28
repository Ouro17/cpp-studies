#include <stdlib.h>
#include "Triangle.hpp"


int main(){

    Triangle first = Triangle();
    Triangle second = Triangle(1.0, 2.0, 3.0);

    first.print();

    first.setSideA(3.0);
    first.setSideB(4.0);
    first.setSideC(5.0);

    first.print();
    second.print();

    return EXIT_SUCCESS;
}