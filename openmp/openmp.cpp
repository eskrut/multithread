#include <stdlib.h>
#include <assert.h>

int someExample();
int someExampleParallel();

int main(int argc, char**argv) {

    someExample();

    someExampleParallel();

    return 0;
}

int someExample() {
    int value1;
    //code to evaluate value1
    //may require significant ammount of time
    value1 = 3;
    int value2;
    //code to evaluate value2
    //may require significant ammount of time
    value2 = 3;

    //Now use some fancy algorythm using values
    int result = value1 + value2;
    assert(result == 6);

    return result;
}

#include <omp.h>
int someExampleParallel() {
    int value1;
    int value2;
#pragma omp parallel sections
    {
#pragma omp section
        {
            //code to evaluate value1
            //may require significant ammount of time
            value1 = 3;
        }
#pragma omp section
        {
            //code to evaluate value2
            //may require significant ammount of time
            value2 = 3;
        }
    }//here we wait for all blocks

    //Now use some fancy algorythm using values
    int result = value1 + value2;
    assert(result == 6);

    return result;
}
