# cpp_result
A Simple Result Type For C++

Inspired by the exception-less way to manage errors in languages like *Rust*, *Swift* or *Zig*.

Provides a templated Result type that can hold either a `Value` or an `Error`.
`Value` can be any Type, but `Error` must be either an `enum` or an integer (for old-school
error codes such as `HRESULT`).

Since the underlying value can't be accessed directly (as with a raw pointer) and the compiler will
emit a warning if it's discarded, it forces the user to address the possiblity of a function or 
method failing and not returning the expected value.

The Error type also allows to return information about the failure that can be propagated upwards
accross the callstack, similar to an exception.

This removes the need of using C-style error codes + output parameters, simplifying the code.

Since it uses `std::variant`, this requires at least **C++ 17**.