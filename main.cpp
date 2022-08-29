#include <iostream>
#include "Vector.h"

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Vector vec(arr, 10);
    std::cout << vec[2];
    return 0;
}