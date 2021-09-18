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
#include "generator.h"

// read float co-routine
Generator<float> read_stream(std::istream& in)
{
    uint32_t data;
    int count{};
    uint8_t byte;
    while (in >> byte) {
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

static constexpr float threshold{21.0};

std::ostream& operator<<(std::ostream& out, const std::optional<DataPoint>& dp)
{
    if (dp) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(8) << dp->timestamp 
                  << std::setw(8) << dp->data
                  << (dp->data > threshold ? " ***Threshold exceeded***" : "");
    }
    return out;
}

// read struct coroutine
Generator<DataPoint> read_data(std::istream& in)
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

int main()
{
    // std::cout << "Time (ms)   Data" << std::endl;
    // for (auto&& dp: read_data(std::cin)) {
    //     std::cout << dp << std::endl;
    // }

    auto stream = read_data(std::cin);
    std::cout << "Time (ms)   Data" << std::endl;
    ranges::copy(stream.begin(), stream.end(), 
        std::ostream_iterator<std::optional<DataPoint>>(std::cout,"\n"));

    return 0;
}