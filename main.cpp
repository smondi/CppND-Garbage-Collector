#include "gc_pointer.h"
#include "LeakTester.h"

#include <iostream>


int main()
{
    Pointer<int> p = new int(19);
    Pointer<int> q = new int(10);

    p = q;
    
    Pointer<int, 10> arr1 = new int[10];
    Pointer<int, 10> arr2;

    for (int i = 0; i < 10; ++i) {
        arr1[i] = i;
    }

    arr2 = arr1;

    for (int i = 0; i < 10; ++i) {
        std::cout << arr2[i] << std::endl;
    }    

    return 0;
}
