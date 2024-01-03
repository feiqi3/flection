#include "metaDefs.hpp"
namespace This_is_a_reflection_namespace {

 class RFL_CLASS() Bar{
    int HELLO;
    RFL_PROPERTY()
    int world;
    RFL_PROPERTY()
    int hola;
    RFL_FUNC()
    virtual void func(int a,int b,int c)noexcept;
};

 struct RFL_CLASS() Foo :public Bar{
    RFL_FUNC()
    int func(double);
};
}
