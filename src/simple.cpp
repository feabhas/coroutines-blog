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
#include <optional>
#include <iostream>
#include <cassert>
#include <exception>

class Future;

struct Promise
{
    using value_type = const char*;
    const char* value{};

    Promise() = default;
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() { std::rethrow_exception(std::current_exception()); }

    std::suspend_always yield_value(const char* value) {
        this->value = std::move(value);
        return {};
    }

    // void return_value(const char* value) {
    //     this->value = std::move(value);
    // }

    void return_void() {
        this->value = nullptr;
    }

    Future get_return_object();
};

class Future
{
public:
    using promise_type = Promise;

    explicit Future(std::coroutine_handle<Promise> handle)
        : handle (handle) 
    {}

    ~Future() {
        if (handle) { handle.destroy(); }
    }
    
    Promise::value_type next() {
        if (handle) {
            handle.resume();
            return handle.promise().value;
        }
        else {
            return {};
        }
    }

private:
    std::coroutine_handle<Promise> handle{};    
};

Future Promise::get_return_object()
{
    return Future{ std::coroutine_handle<Promise>::from_promise(*this) };
}


// co-routine
Future Generator()
{
    co_yield "Hello ";
    co_yield "world";
    co_yield "!";
    //co_return;
}

int main()
{
    // auto generator = Generator();
    // std::cout << generator.next();
    // std::cout << generator.next();
    // std::cout << generator.next();
    // std::cout << std::endl;
	
	auto generator = Generator();
	while (const char* item = generator.next()) {
		std::cout << item;
	}
	std::cout << std::endl;

    return 0;
}