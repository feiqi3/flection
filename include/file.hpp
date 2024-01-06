#pragma once

#include "metaDefs.hpp"
namespace This_is_a_reflection_namespace {

 class RFL_CLASS() Bar{
    public:
    RFL_ALL(This_is_a_reflection_namespace::Bar);
    private:
    int HELLO;
    RFL_PROPERTY()
    int world;
    RFL_PROPERTY()
    int hola;
        RFL_PROPERTY()
    int holao;
        RFL_PROPERTY()
    int holaa;
    RFL_FUNC()
    virtual void func(int a,int b,int c)noexcept;
};

 struct RFL_CLASS() Foo :public Bar{
    RFL_FUNC()
    int func(double);
};
}
