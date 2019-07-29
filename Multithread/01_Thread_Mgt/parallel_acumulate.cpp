#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <iterator>


#define MIN_BLOCK_SIZE 1000

template<typename iterator, typename T>
void accumulate(iterator start, iterator end, T & ref)
{
    ref = std::accumulate(start, end, 0);
}


template<typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T & ref)
{
    int input_size = std::distance(start, end);
    int allowed_threads_by_elements = (input_size) / MIN_BLOCK_SIZE;

    int allowed_threads_by_hardware = std::thread::hardware_concurrency();
    
    int num_threads = std::min(allowed_threads_by_elements, allowed_threads_by_hardware);

    int block_size = (input_size + 1) / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    iterator last;

    for (int i = 0; i < num_threads-1; i++)
    {
        last = start;
        std::advance(last, block_size);
        threads[i] = std::thread(accumulate<iterator, T>, start, last, std::ref(results[i]));

        start = last;
    }
    results[num_threads-1] = std::accumulate(start, end, 0);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(). results.end(), ref);
}

void run()
{
    const int size = 8000;
    int * array = new int[size];
    int ref = 0;

    srand(0);

    for (size_t i = 0; i < size; i++)
    {
        array[i] = rand() % 10;
    }

    int rer_val = parallel_accumulate<int*, int>(array, array+size, ref);
    std::cout << "Accumulated value: " << rer_val << std::endl;
}

int main(int argc, char const *argv[])
{
    run();
    return 0;
}
