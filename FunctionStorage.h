#ifndef __FUNCTION_STORAGE_H__
#define __FUNCTION_STORAGE_H__
#include "TLFunction_traits.h"
#include "Any.h"
#include <type_traits>
#include <unordered_map>
using namespace std;

class FunctionStorage {
public:
    template <typename ReturnType, typename ClassType, typename... Args,
              typename = enable_if<is_same<void, ReturnType>::value>>
    static void registCallEvent(string e, ReturnType (ClassType::*f)(Args...),
                                ClassType *cls)
    {
        using Func = ReturnType (ClassType::*)(Args...);
        static_assert(function_traits<Func>::arity() == 1, 
            "function_traits param num must be 1");

        auto func = to_function(f, cls);
        string funcSign = typeid(void(typename decay<Args>::type...)).name();
        string key      = e + funcSign;
        _mapSignFunc.insert(make_pair(key, template_learning::any(func)));

        return;
    }

    template <typename... Args>
    static int publishCallEvent(string e, Args &&...args)
    {
        using function_type = function<void(Args...)>;
        string funcSign = typeid(void(typename decay<Args>::type...)).name();
        string key      = e + funcSign;
        auto   range    = _mapSignFunc.equal_range(key);
        auto   ans      = 0;
        for (auto it = range.first; it != range.second; it++) {
            auto f =
                it->second
                    .fCast<function_traits<function_type>::stl_function_type>();
            f(forward<Args>(args)...);
            ans++;
        }
        return ans;
    }
    static unordered_multimap<string, template_learning::any>  _mapSignFunc;
};

#endif // __FUNCTION_STORAGE_H__