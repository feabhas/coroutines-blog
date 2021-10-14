// -----------------------------------------------------------------------------
// coroutine template
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
#include <cstddef>
#include <iterator>

template <typename T>
class Generator
{
    class Promise
    {
    public:
        using value_type = std::optional<T>;

        Promise() = default;
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { 
            std::rethrow_exception(std::move(std::current_exception()));
        }

        std::suspend_always yield_value(T value) {
            this->value = std::move(value);
            return {};
        }

        // void return_value(T value) {
        //     this->value = std::move(value);
        // }

        void return_void() {
            this->value = std::nullopt;
        }

        inline Generator get_return_object();
        
        value_type get_value() {
            return std::move(value);
        }

        bool finished() {
            return !value.has_value();
        }
        
    private:
        value_type value{};
    };

public:
    using value_type = T;
    using promise_type = Promise;

    explicit Generator(std::coroutine_handle<Promise> handle)
        : handle (handle) 
    {}

    ~Generator() {
        if (handle) { handle.destroy(); }
    }
   
    Promise::value_type next() {
        if (handle) {
            handle.resume();
            return handle.promise().get_value();
        }
        else {
            return {};
        }
    }

    struct end_iterator {};

    class iterator
    {
    public:
        using value_type = Promise::value_type;
        using difference_type =  std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        iterator(Generator& generator) : generator{&generator}
        {}

        value_type operator*() const { 
            if (generator) {
                return generator->handle.promise().get_value();
            }
            return {}; 
        }

        value_type operator->() const { 
            if (generator) {
                return generator->handle.promise().get_value();
            }
            return {}; 
        }

        iterator& operator++() {
            if (generator && generator->handle) {
                generator->handle.resume();
            }
            return *this;
        }

        iterator& operator++(int) {
            if (generator && generator->handle) {
                generator->handle.resume();
            }
            return *this;
        }

        bool operator== (const end_iterator&) const {
            return generator ? generator->handle.promise().finished() : true;
        }

    private:
        Generator* generator{};
    };
    
    iterator begin() {
        iterator it{*this};
        return ++it;
    }

    end_iterator end() {
        return end_sentinel;
    }

private:
    end_iterator end_sentinel{};
    std::coroutine_handle<Promise> handle;    
};


template <typename T>
inline Generator<T> Generator<T>::Promise::get_return_object()
{
    return Generator{ std::coroutine_handle<Promise>::from_promise(*this) };
}
