#include "Any.h"
#include <vector>
#include <unordered_map>

class A {
private:
    int m_{99};
};

int main() {
    unordered_multimap< int, template_learning::any > v;
    template_learning::any n(9);
    v.insert({1, n});
    // vector<template_learning::Any> v;
    // template_learning::Any n(9);
    // v.push_back(n);
    // template_learning::Any a(A());
    // v.push_back(a);
    return 0;
}