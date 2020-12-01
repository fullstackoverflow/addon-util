#pragma once

#include <functional>
#include <napi.h>
#include <iostream>
#include <vector>
#include <algorithm>

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

        template <typename A>
        auto fill(A input)
        {
            std::vector<A> out(this->v.size(), input);
            return Array<A, F + 1>(std::move(out));
        }

        auto some(std::function<bool(T element, int index)> f)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                if (f(value, index) == true)
                {
                    return true;
                }
                index++;
            }
            return false;
        }

        auto filter(std::function<bool(T element, int index)> f)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                bool result = f(value, index);
                if (result == true)
                {
                    out.push_back(value);
                }
                index++;
            }
            return Array<T>(std::move(out));
        }

        T find(std::function<bool(T element, int index)> f)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                bool result = f(value, index);
                if (result == true)
                {
                    return value;
                }
                index++;
            }
            return NULL;
        }

        bool includes(T element)
        {
            std::vector<T> out;
            for (auto value : this->v)
            {
                if (element == value)
                {
                    return true;
                }
            }
            return false;
        }

        int findIndex(std::function<bool(T element, int index)> f)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                bool result = f(value, index);
                if (result == true)
                {
                    return index;
                }
                index++;
            }
            return -1;
        }

        int indexOf(T element)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                if (element == value)
                {
                    return index;
                }
                index++;
            }
            return -1;
        }

        template <typename... Args>
        int push(T arg, Args... args)
        {
            if (sizeof...(args) > 0)
            {
                this->push(args...);
            }
            else
            {
                this->v.emplace_back(arg);
            }
            return this->v.size();
        }

        void pop()
        {
            this->v.erase(this->v.end());
        }

        void shift()
        {
            this->v.erase(this->v.begin());
        }

        template <typename... Args>
        auto unshift(T arg, Args... args)
        {
            if (sizeof...(args) > 0)
            {
                this->unshift(args...);
            }
            else
            {
                this->v.insert(this->v.begin(), arg);
            }
            return this->v.size();
        }

        auto concat(Array<T> input)
        {
            std::vector<T> out;
            out.insert(out.end(), this->v.begin(), this->v.end());
            out.insert(out.end(), input.to_vector().begin(), input.to_vector().end());
            return Array<T>(std::move(out));
        }

        void forEach(std::function<void(T element, int index)> f)
        {
            std::vector<T> out;
            int index = 0;
            for (auto value : this->v)
            {
                if (f(value, index) == true)
                {
                    f(index, std::move(value));
                }
                index++;
            }
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

        auto length()
        {
            return this->v.size();
        }

        template <typename B, typename C>
        auto reduce(B f, C out)
        {
            int index = 0;
            for (auto value : this->v)
            {
                out = std::move(f(out, std::move(value), index));
                index++;
            }
            return out;
        }

        auto slice(int begin, int end)
        {
            std::vector<T> out = {};
            if (begin < 0)
            {
                begin = this->v.size() + begin;
                if (begin > 0)
                {
                    return Array<T>(std::move(out));
                }
            }
            if (end < 0)
            {
                end = this->v.size() + end;
            }
            int index = 0;
            for (auto value : this->v)
            {
                if (index > begin && index < end)
                {
                    out.push_back(std::move(value));
                }
                index++;
                if (index >= end)
                {
                    break;
                }
            }
            return Array<T>(std::move(out));
        }

        template <typename U>
        auto map(U f)
        {
            std::vector<typename std::result_of<U(int, T)>::type> out;
            int index = 0;
            for (auto value : this->v)
            {
                out.push_back(f(std::move(value), index));
                index++;
            }
            return Array<typename std::result_of<U(int, T)>::type, F + 1>(std::move(out));
        }

        auto reverse()
        {
            std::reverse(this->v.begin(), this->v.end());
            return *this;
        }
    };
} // namespace AddonTemplate