#include <stdlib.h>
#include <windows.h>
#include <assert.h>

DWORD WINAPI someParallelTask(void *arg) {
    int *preciousValue =
            reinterpret_cast<int*>(arg);
    *preciousValue = 1;
}

int main(int argc, char**argv) {

    HANDLE thread;
    int value, othreValue;

    thread = CreateThread(
                NULL,
                0,
                someParallelTask,
                &value,
                0,
                NULL
                );
    someParallelTask(&othreValue);
    WaitForSingleObject(thread, INFINITE);
    assert(value == othreValue);

    return 0;
}
