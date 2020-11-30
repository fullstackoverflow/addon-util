#pragma once

#include <functional>
#include <napi.h>
#include <iostream>
#include <vector>

namespace AddonTemplate
{
    template <typename T, int F = 0>
    class Array
    {
    private:
        std::vector<T> v;

    public:
        Array(std::vector<T> v)
        {
            this->v = v;
        }

        ~Array()
        {
        }

        std::vector<T> to_vector()
        {
            return this->v;
        }

        auto print()
        {
            std::cout << "[";
            for (auto value : this->v)
            {
                std::cout << value << ",";
            }
            std::cout << "]";
            return *this;
        }

        template <typename U>
        auto map(U f)
        {
            std::vector<typename std::result_of<U(int, T)>::type> out;
            int index = 0;
            for (auto value : this->v)
            {
                out.push_back(f(index, value));
            }
            return Array<typename std::result_of<U(int, T)>::type, F + 1>(out);
        }
    };
} // namespace AddonTemplate