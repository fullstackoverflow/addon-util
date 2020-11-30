#include <napi.h>
#include <iostream>
#include "AsyncWorker.hpp"
#include "Vector.hpp"
#include <functional>
#include <tuple>

class Util : public Napi::ObjectWrap<Util>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Util(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value AsyncWorker(const Napi::CallbackInfo &info);
    Napi::Value Map(const Napi::CallbackInfo &info);
};

Napi::Object Util::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "Util", {InstanceMethod("AsyncWorker", &Util::AsyncWorker), InstanceMethod("Map", &Util::Map)});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Util", func);
    return exports;
}

Util::Util(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Util>(info)
{
}

Napi::FunctionReference Util::constructor;

Napi::Value Util::AsyncWorker(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    int input_1 = info[0].As<Napi::Number>().Uint32Value();
    int input_2 = info[1].As<Napi::Number>().Uint32Value();
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);
    auto worker = new AddonTemplate::AsyncWorker(
        env, deferred,
        [input_1, input_2]() {
            return std::tuple<int, bool>(input_1 + input_2, true);
        },
        [](Napi::Env env, Napi::Promise::Deferred deferred, std::tuple<int, bool> result) {
            Napi::Object output = Napi::Object::New(env);
            output.Set("tag", Napi::Boolean::New(env, std::get<1>(result)));
            output.Set("result", Napi::Number::New(env, std::get<0>(result)));
            deferred.Resolve(output);
        },
        [](Napi::Promise::Deferred deferred, Napi::Error const &error) {
            deferred.Reject(error.Value());
        });
    worker->Queue();
    return deferred.Promise();
}

Napi::Value Util::Map(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::Array arr = info[0].As<Napi::Array>();
    std::vector<int> input;
    for (int i = 0; i < arr.Length(); i++)
    {
        input.push_back(arr.Get(i).As<Napi::Number>().Uint32Value());
    }
    AddonTemplate::Array array(input);
    std::vector<double> out = array.map([](int index, int value) {
                                    return double(value * 2);
                                })
                               .print()
                               .to_vector();
    Napi::Array arr_out = Napi::Array::New(env, out.size());
    for (int i = 0; i < out.size(); i++)
    {
        arr_out.Set(i, Napi::Number::New(env, out[i]));
    }
    return arr_out;
}

// Initialize native add-on
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Util::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)