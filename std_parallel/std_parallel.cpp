#include <stdlib.h>
#include "parallel/algorithm"

#include <iostream>
#include <chrono>
#include <functional>
#include <random>
#include <algorithm>

using hr_clock = std::chrono::high_resolution_clock;

struct Stopwatch {
    hr_clock::time_point start_;
    hr_clock::time_point stop_;
    void start() {start_ = hr_clock::now();}
    double stop() {
        stop_ = hr_clock::now();
        return (std::chrono::duration_cast<std::chrono::duration<double>>(stop_ - start_)).count();
    }
};

int main(int argc, char**argv) {

    Stopwatch sw;
    {
        const size_t length = 0.1 /*Gb*/
                * 1024ull /*Mb*/
                * 1024 /*Kb*/
                * 1024 /*b*/
                / sizeof(size_t) /*count*/;
        std::vector<size_t> vecOrigin;
        vecOrigin.reserve(length);
        for(size_t ct = 0; ct < length; ++ct)
            vecOrigin.push_back(ct);


        auto vecToSort = vecOrigin;
        std::shuffle(vecToSort.begin(), vecToSort.end(),
                     std::default_random_engine(
                         hr_clock::now().time_since_epoch().count()
                         )
                     );

        auto vecToSort2 = vecToSort;

        size_t max;
        sw.start();
        max = *std::max_element(vecToSort.begin(), vecToSort.end());
        std::cout << "max_element seq " << sw.stop() << std::endl;

        size_t max2;
        sw.start();
        max2 = *std::__parallel::max_element(vecToSort2.begin(), vecToSort2.end());
        std::cout << "max_element par " << sw.stop() << std::endl;

        if(max != length-1) throw std::runtime_error("Cant evaluete max with sequential max_element");
        if(max2 != length-1) throw std::runtime_error("Cant evaluete max with parallel max_element");

        sw.start();
        std::sort(vecToSort.begin(), vecToSort.end());
        std::cout << "sort seq " << sw.stop() << std::endl;

        sw.start();
        std::__parallel::sort(vecToSort2.begin(), vecToSort2.end());
        std::cout << "sort par " << sw.stop() << std::endl;

        for(size_t ct = 0; ct < length; ++ct)
            if( vecToSort[ct] != ct ) throw std::runtime_error("Cant sort in sequential mode");
        for(size_t ct = 0; ct < length; ++ct)
            if( vecToSort2[ct] != ct ) throw std::runtime_error("Cant sort in parallel mode");
    }

    {
        const size_t lengthData = 25000;
        const size_t lengthVector = 4 /*Gb*/
                * 1024ull /*Mb*/
                * 1024 /*Kb*/
                * 1024 /*b*/
                / sizeof(size_t) /*count*/
                / lengthData;
        std::vector<std::vector<size_t>> dataBundle;
        dataBundle.resize(lengthData, std::vector<size_t>(lengthVector, 0));
        auto gen = std::default_random_engine(
                    hr_clock::now().time_since_epoch().count()
                    );
        for(auto &vec : dataBundle) {
            for(auto &value : vec) {
                value = gen();
            }
        }

        std::vector<size_t> maxes(lengthData, 0);
        sw.start();
        std::for_each(
                    dataBundle.cbegin(),
                    dataBundle.cend(),
                    [&dataBundle, &maxes](const std::vector<size_t> &vec)
        {
            size_t index = &vec - dataBundle.data();
            maxes[index] = *std::max_element(vec.begin(), vec.end());
        }
        );
        std::cout << "for_each seq " << sw.stop() << std::endl;

        std::vector<size_t> maxes2(lengthData, 0);
        sw.start();
        std::__parallel::for_each(dataBundle.cbegin(),
                                  dataBundle.cend(),
                                  [&dataBundle, &maxes2](const std::vector<size_t> &vec)
        {
            size_t index = &vec - dataBundle.data();
            maxes2[index] = *std::max_element(vec.begin(), vec.end());
        }
        );
        std::cout << "for_each par " << sw.stop() << std::endl;
    }
    return 0;
}
