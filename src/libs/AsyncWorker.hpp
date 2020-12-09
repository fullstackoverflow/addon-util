#pragma once

#include <functional>
#include <napi.h>

namespace AddonTemplate
{
    template <typename F1, typename F2, typename F3>
    class AsyncWorker : public Napi::AsyncWorker
    {
    private:
        F1 execute;
        F2 onok;
        F3 onerror;
        Napi::Promise::Deferred deferred;

    public:
        typename std::result_of<F1()>::type result;

        AsyncWorker(Napi::Env &env, Napi::Promise::Deferred &deferred, F1 f1, F2 f2, F3 f3) : Napi::AsyncWorker(env), deferred(deferred), execute(f1), onok(f2), onerror(f3)
        {
        }
        ~AsyncWorker()
        {
        }

        void Execute()
        {
            try
            {
                this->result = this->execute();
            }
            catch (const char *str)
            {
                Napi::AsyncWorker::SetError(str);
            }
            catch (...)
            {
                Napi::AsyncWorker::SetError("Unknow Error");
            }
        }

        void OnOK()
        {
            this->onok(Env(), this->deferred, this->result);
        }

        void OnError(Napi::Error const &error)
        {
            this->onerror(this->deferred, error);
        }
    };
} // namespace AddonTemplate