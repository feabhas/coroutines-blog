// -----------------------------------------------------------------------------
// main program
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------

#include <coroutine>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include "future.h"


// read float co-routine
Future<float> read_stream(std::istream& in)
{
    uint32_t data;
    int count{};
    char byte;
    while (in.get(byte)) {
        data = data << 8 | byte;
        if (++count == 4) {
            co_yield *reinterpret_cast<float*>(&data);
            data = 0;
            count = 0;
        }
    }
}

struct DataPoint
{
    float timestamp;
    float data;

};

// read struct coroutine
Future<DataPoint> read_data(std::istream& in)
{
    std::optional<float> first{};
    auto raw_data = read_stream(in);
    while (auto next = raw_data.next()) {
        if (first) {
            co_yield DataPoint{*first, *next};
            first = std::nullopt;
        }
        else {
            first = next;
        }
    }
}

namespace ranges = std::ranges;
static constexpr float threshold{21.0};

int main()
{
    // auto raw_data = read_stream(std::cin);
    // while (auto next = raw_data.next()) {
    //     std::cout << *next << std::endl;
    // }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Time (ms)   Data" << std::endl;
    auto values = read_data(std::cin);
    while (auto n = values.next()) {
        std::cout << std::setw(8) << n->timestamp 
                  << std::setw(8) << n->data
                  << (n->data > threshold ? " ***Threshold exceeded***" : "")
                  << std::endl;
    }

    return 0;
}