#include <stdlib.h>
#include <iostream>
#include <thread>
#include <assert.h>
#include <list>

int main(int argc, char**argv) {
    int dataRaceTarget = 0;

    int numCycles = 1000;

    auto taskP = [](int volatile &dataRaceTarget,
            int numCycles){
        for(size_t ct = 0; ct < numCycles; ++ct)
            dataRaceTarget++;
        return 0;
    };
    auto taskM = [](int volatile &dataRaceTarget,
            int numCycles){
        for(size_t ct = 0; ct < numCycles; ++ct)
            dataRaceTarget--;
        return 0;
    };
    std::list<std::thread> threads;
    for(size_t ct = 0; ct < std::thread::hardware_concurrency(); ++ct) {
        if(ct % 2)
            threads.push_back(std::thread(std::bind(
                                              taskP,
                                              std::ref(dataRaceTarget),
                                              numCycles)));
        else
            threads.push_back(std::thread(std::bind(
                                              taskM,
                                              std::ref(dataRaceTarget),
                                              numCycles)));
    }
    for(auto &t : threads) {
        t.join();
    }
    std::cout << "result: " << dataRaceTarget << std::endl;
    return 0;
}
