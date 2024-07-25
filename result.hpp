#if __cplusplus < 201402L
#error Minimum supported version is C++ 14.
#else // C++ 14 or newer

#if !defined(JSP_RESULT_HPP)
#define JSP_RESULT_HPP

#if defined(NDEBUG)
    #include <stdlib.h>
    #if !defined(JSP_REQUIRE)
        #define JSP_REQUIRE(condition) if (!condition) { abort(); }
    #endif // JSP_REQUIRE
#else // NDEBUG
    #include<assert.h>
    #if !defined(JSP_REQUIRE)
        #define JSP_REQUIRE(condition) assert(condition);
    #endif // JSP_REQUIRE
#endif // NDEBUG

#if !defined(JSP_NO_STL)
    #include <type_traits>
#endif // !JSP_NO_STL

namespace jsp
{
    template<typename Value, typename Error>
    class
#if __cplusplus >= 201703L
    [[nodiscard]]
#endif // C++ 17 or newer
    Result
    {
    #if !defined(JSP_NO_STL)
        static_assert(
            std::is_enum<Error>() || std::is_integral<Error>(),
            "The error type must be an enum (recommended) or an integer (legacy).");
    #endif // !JSP_NO_STL

    public:
        Result() = delete;
        Result(Value v) noexcept : val(v), flag(true)  {}
        Result(Error e) noexcept : err(e), flag(false) {}

        constexpr explicit operator bool() const noexcept { return flag; }

        // True if it holds a Value, false if it holds an Error
        constexpr auto has_value() const noexcept -> bool { return flag; }

        // Unwraps the held value, or returns the provided alternative if it holds an Error
        constexpr auto value_or(Value alternative) const noexcept -> Value
        {
            return has_value() ? val : alternative;
        }

        // Unwraps the held Value. If instead it holds an Error, it aborts the program
        constexpr auto value() const noexcept -> Value
        {
            JSP_REQUIRE( has_value() );
            return val;
        }

        // Unwraps the held Error. If instead it holds a Value, it aborts the program
        constexpr auto error() const noexcept(false) -> Error
        {
            JSP_REQUIRE( !has_value() );
            return err;
        }

    private:
        const union
        {
            Value val;
            Error err;
        };
        const bool flag;
    };
}
#endif // !JSP_RESULT_HPP
#endif // C++ version
