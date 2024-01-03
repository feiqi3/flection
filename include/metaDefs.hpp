#pragma once
#ifndef METADEFS_HPP_
#define METADEFS_HPP_

#define RFL_CLASS(...) __attribute__((annotate("reflect_class",#__VA_ARGS__)))
#define RFL_PROPERTY(...) __attribute__((annotate("reflect_property",#__VA_ARGS__)))
#define RFL_FUNC(...) __attribute__((annotate("reflect_func",#__VA_ARGS__)))

#endif