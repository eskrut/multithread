#include <stdlib.h>
#include <future>
#include <assert.h>

int someExample();
int someExampleParallel();

int main(int argc, char**argv) {
    int value, othreValue;

    othreValue = 1;

    auto futureOfValue = std::async(
                [](){return 1;}
                );
    value = futureOfValue.get();

    assert(value == othreValue);

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

int someExampleParallel() {

    auto futureValue1 = std::async([](){
        int value1;
        //code to evaluate value1
        //may require significant ammount of time
        value1 = 3;
        return value1;
    });

    auto futureValue2 = std::async([](){
        int value2;
        //code to evaluate value2
        //may require significant ammount of time
        value2 = 3;
        return value2;
    });

    //Now use some fancy algorythm using values
    int result = futureValue1.get() + futureValue2.get();
    assert(result == 6);

    return result;
}
