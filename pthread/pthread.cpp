#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void* someParallelTask(void *arg) {
    int *preciousValue =
            reinterpret_cast<int*>(arg);
    *preciousValue = 1;
}

int main(int argc, char**argv) {

    pthread_t thread;
    int value, othreValue;

    pthread_create(&thread,
                   nullptr,
                   someParallelTask,
                   &value);
    someParallelTask(&othreValue);
    pthread_join(thread, nullptr);
    assert(value == othreValue);

    return 0;
}
