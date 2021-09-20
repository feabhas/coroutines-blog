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
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>
#include "generator.h"

Generator<std::unique_ptr<int>> range(int limit=5)
{
    for (int i = 0; i < limit; ++i) {
        co_yield std::make_unique<int>(i);
    }
}

int main()
{
    for (auto&& it: range()) {
        std::cout << **it << std::endl;
    }  

    auto numbers = range();
    auto vec = std::vector<std::optional<std::unique_ptr<int>>>{};
    vec.reserve(5);
    std::ranges::copy(numbers.begin(), numbers.end(), std::back_inserter(vec));

    for (auto&& it: vec) {
        std::cout << **it << std::endl;
    }

    return 0;
}