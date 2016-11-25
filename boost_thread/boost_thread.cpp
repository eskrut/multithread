#include <stdlib.h>
#include "boost/thread.hpp"
#include <assert.h>

void someParallelTask() {
    while(true) { //forewer cycle
        boost::this_thread::disable_interruption di;
        //alloc some resources to work
        //do not interrupt me
        boost::this_thread::restore_interruption ri(di);

        //ok check if I should die (
        boost::this_thread::interruption_point();
    }
}

int main(int argc, char**argv) {

    auto thread = boost::thread( someParallelTask );

    //do some jod
    //And now I do not want to wait thread

    thread.interrupt();

    thread.join();

    return 0;
}
