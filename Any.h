#include <typeindex>
#include <memory>
class any {
    // any():m_tpIdx {}
    // explixt any(any& that)
private:
    class base;
    typedef unique_ptr<base> basePtr;
    //using basePtr = unique_ptr<base>;
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
             return BasePtr(new derived<T>(m_value));
        }

        T m_value;
    };

private:
    std::type_index m_tpIdx;
};