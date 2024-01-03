#define RFL_CLASS(...) __attribute__((annotate("reflect_class",#__VA_ARGS__)))
#define RFL_PROPERTY(...) __attribute__((annotate("reflect_property",#__VA_ARGS__)))
#define RFL_FUNC(...) __attribute__((annotate("reflect_func",#__VA_ARGS__)))

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
