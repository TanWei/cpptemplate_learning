#ifndef __TLFUNCTION_TRAITS_H__
#define __TLFUNCTION_TRAITS_H__
#include <type_traits>
#include <functional>

using namespace std;
template <typename T>
struct function_traits;

//base normal function
template<typename Ret, typename ...Args>
struct function_traits<Ret(Args...)>
{
    typedef Ret function_type(Args...);
    typedef Ret return_type;
    using arity = integral_constant<int, sizeof...(Args)>;

    using stl_function_type = function<function_type>;
    typedef Ret(*Pointer)(Args...);

    template<size_t I>
    struct args
    {
        static_assert(I < arity(), "index is out of range,index must less than sizeof Args");
        using type = typename tuple_element < I, tuple<Args...>>::type;
    };

};

template<typename Ret, typename... Args>
struct function_traits < function<Ret(Args...)> > : public function_traits<Ret(Args...)> {};

// #define FUNCTION_TRAITS(...) \
// template <typename ReturnType , typename ClassType,typename... Args >  \
// 	struct function_traits< ReturnType(ClassType::*)(Args...) __VA_ARGS__> :public  function_traits<ReturnType(Args...)>  {}; 
template <typename ReturnType , typename ClassType,typename... Args >  
	struct function_traits< ReturnType(ClassType::*)(Args...) > :public  function_traits<ReturnType(Args...)>  {};  


// FUNCTION_TRAITS()
// FUNCTION_TRAITS(const)
// FUNCTION_TRAITS(volatile)
// FUNCTION_TRAITS(const volatile)


struct _tag_One {};

template<typename I>
struct _get_param;

template<>
struct _get_param< integral_constant<int,1> >
{
    using _param_type = _tag_One;
};

template<typename Function, typename ClassType>
typename function_traits<Function>::stl_function_type 
    _to_function(Function fn, ClassType& cls,_tag_One)
{
    typename function_traits<Function>::stl_function_type f 
        = bind(fn, cls, placeholders::_1);
    return f;
}

template<typename Function, typename ClassType>//, size_t I = function_traits<Function>::arity>
typename function_traits<Function>::stl_function_type
    to_function(Function fn, ClassType& cls)
{
    
    typename _get_param<function_traits<Function>::arity>::_param_type tag;
    auto f = _to_function(fn, cls,tag);
    return f;
};

#endif // __TLFUNCTION_TRAITS_H__