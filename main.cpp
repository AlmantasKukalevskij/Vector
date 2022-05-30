#include <vector>
#include "vector.h"
#include <chrono>
#include <iostream>

using namespace std;

int main()
{
    int reallocCounter = 0;
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int sz = 100000000; // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    for (int i = 0; i <= sz; ++i)
    {
        if (v1.size() == v1.capacity())
            reallocCounter++;
        v1.push_back(i);
    }

    auto time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start);
    cout << time.count() << endl;
    cout << "Allocations: " << reallocCounter << endl;
    // Baigti v1 užpildymo laiko matavimą

    // Pradėti v2 užpildymo laiko matavimą
    reallocCounter = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    customVector<int> v2;
    for (int i = 0; i <= sz; ++i)
    {
        if (v2.size() == v2.capacity())
            reallocCounter++;
        v2.push_back(i);
    }
    // Baigti v2 užpildymo laiko matavimą
    auto time2 = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start2);
    cout << time2.count() << endl;
    cout << "Allocations: " << reallocCounter << endl;

	return 0;
}