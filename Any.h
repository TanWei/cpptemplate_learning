#ifndef __ANY_H__
#define __ANY_H__

#include <typeindex>
#include <memory>
using namespace std;
namespace template_learning {

class any {
public:
    any(void):m_tpIdx(std::type_index(typeid(void))) {}
    any(any& that) : m_ptr(that.clone()), m_tpIdx(that.m_tpIdx) {}
    any(any&& that) : m_ptr(std::move(that.m_ptr)), m_tpIdx(that.m_tpIdx) {}
    template<class U, 
        class = typename std::enable_if<!is_same<typename std::decay<U>::type, any>::value,U>::type>
    any(U&& value) : m_ptr(new derived<typename decay<U>::type>(forward<U>(value))), m_tpIdx(type_index(typeid(typename decay<U>::type))) {}
    
    // template<class U >
	// U& AnyCast()
	// {
	// 	if (!Is<U>())
	// 	{
    //         throw std::bad_cast();
	// 	}
	// 	auto dd = dynamic_cast<derived<U>*> (m_ptr.get());
	// 	return dd->m_value;
	// }

    template<class U >
    U& fCast()
    {
        // warning :
        // @todo : reinterpret_cast<> == static_cast<> ;
        auto  dd = reinterpret_cast< derived<U>* >(m_ptr.get());
        return dd->m_value;
    }
private:
    class base;
    using basePtr = std::unique_ptr<base>;
    class base {
    public:
        virtual ~base() {}
        virtual basePtr clone() const=0;
    };
    template<class T>
    class derived : public base
    {
    public:
        template<class U>
        derived(U && value) : m_value(forward<U>(value)) {}
        basePtr clone() const {
             return basePtr(new derived<T>(m_value));
        }

        T m_value;
    };

    basePtr clone() const
	{
		if (m_ptr != nullptr)
			return m_ptr->clone();
		return nullptr;
	}

private:
    std::type_index m_tpIdx;
    basePtr m_ptr;
};
}

#endif // __ANY_H__