# cpp_result
## A Simple Result Type For C++

Inspired by the exception-less way to manage errors in languages like *Rust*, *Swift* or *Zig*.

Provides a templated Result type that can hold either a `Value` or an `Error`.
`Value` can be any Type, but `Error` must be either an `enum` or an integer (for old-school
error codes such as `HRESULT`).
The Error type enforcing uses `<type_traits>` from the STL but it can be disabled by defining
`RESULT_WITHOUT_STL`, in case you don't want to include any STL headers

Since the underlying value can't be accessed directly (as with a raw pointer) and the compiler will
emit a warning if it's discarded, it forces the user to address the possiblity of a function or
method failing and not returning the expected value.

The Error type also allows to return information about the failure that can be propagated upwards
accross the callstack, similar to an exception.

This removes the need of using C-style error codes + output parameters, simplifying the code.

Minimum version required is C++ 14 because asserting inside a `constexpr` is not supported in older versions.
From C++ 17 onwards the compiler will issue a warning if the returned value of a function returning
a `jsp::Result` is discarded.

---

### `has_value() -> bool`
- *Returns*: `true` if it holds a `Value`, `false` if it holds an `Error`.

---

### `value_or(Value alternative) -> Value`
- *Parameters*
    - *alternative*: The `Value` to return if it holds an `Error`.
- *Returns*: The held `Value` if appropriate, otherwise the provided alternative.

---

### `value() -> Value`
Unwraps the held `Value`. If instead it holds an `Error`, it aborts the program.
On debug builds it asserts instead of aborting.
- *Returns*: The held `Value`.

---

### `error() -> Error`
Unwraps the held `Error`. If instead it holds a `Value`, it aborts the program.
On debug builds it asserts instead of aborting.
- *Returns*: The held `Error`.
