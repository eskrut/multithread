#include <stdlib.h>
#include <thread>
#include <assert.h>

void someParallelTask(int &value) {
    value = 1;
}

int main(int argc, char**argv) {

    std::thread thread;
    int value, othreValue;

    thread = std::thread(
                someParallelTask,
                std::ref(value));
    someParallelTask(othreValue);
    thread.join();
    assert(value == othreValue);

    return 0;
}
