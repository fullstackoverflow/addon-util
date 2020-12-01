# 简介

使用模板简化部分nodejs addon开发

# 使用

### 通用AsyncWorker模板
1. 构造函数的三个lambda分别为处理函数，返回值封装，错误处理函数(在处理函数中throw时触发，抛出const char *类型的错误会被正确视为message设置到SetError,其他类型的错误message为Unknow Error)
2. 处理函数捕获列表必须为拷贝复制(该函数执行时上下文变量已经被回收了)
```
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

```

### 通用Array模板
1. 构造函数的入参为vector
2. map方法会使模板进行一层展开增加一个节点，链式调用该方法过多会导致编译时间变长

### 支持的方法

- [x] fill
- [x] map
- [x] some
- [x] slice
- [x] reduce
- [x] forEach
- [x] find
- [x] findIndex
- [x] concat
- [x] includes
- [x] indexOf
- [x] push
- [x] pop(由于删除元素的访问问题,函数返回值为void)
- [x] shift(由于删除元素的访问问题,函数返回值为void)
- [x] unshift
- [ ] splice
- [ ] toString
- [ ] flat
- [ ] flatMap
```
std::vector<int> input = {1, 2, 3, 4, 5};
AddonTemplate::Array array(input);
std::vector<double> out = array.map([](int index, int value) {
                                   return double(value * 2);
                               })
                              .print()
                              .reverse()
                              .print()
                              .to_vector();
```