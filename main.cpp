#include "FunctionStorage.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
// registCallEvent("ceshiji", &TBoardManager::init,
//                               this);
class A {
public:
    void init() {
        FunctionStorage::registCallEvent("doA199", &A::doA, this);
    }
    void doA(int n)
    {
        int n1=0;
        return;
    }
    void callDoA() {
        FunctionStorage::publishCallEvent("doA199", 199);
    }
};


int main() {
    const int  n1= 10;
    int n2= 99;
    auto n1i = type_index(typeid(n1));
    auto n2i = type_index(typeid(n2));
    std::string ss1 = n1i.name();
    std::string ss2 = n2i.name();
    A a;
    a.init();
    a.callDoA();
    //using ss = integral_constant<const char*, "ersdf">;
    // static constexpr char value[] = "ersdf";
    // unordered_multimap< int, template_learning::any > v;
    // template_learning::any n(9);
    // v.insert({1, n});
    // vector<template_learning::Any> v;
    // template_learning::Any n(9);
    // v.push_back(n);
    // template_learning::Any a(A());
    // v.push_back(a);
    return 0;
}