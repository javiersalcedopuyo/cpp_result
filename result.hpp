#include <variant>
#include <type_traits>

template<typename Value, typename Error>
class [[nodiscard]] Result
{
    static_assert(std::is_enum<Error>() || std::is_integral<Error>(),
                  "The error type must be an enum (recommended) or an integer (legacy).");

public:
    Result() = delete;
    Result(Value&& val) noexcept : v(std::move(val))    {}
    Result(Error error) noexcept : v(error) {}

    // True if it holds a Value, false if it holds an Error
    constexpr explicit operator bool() const noexcept
    {
        return std::holds_alternative<Value>(v);
    }
    constexpr auto has_value() const noexcept -> bool { return bool(*this); }

    // Unwraps the contained Value. If instead it contains an Error, throws an exception
    constexpr auto value() const noexcept(false) -> const Value&&
    {
        return std::move( std::get<Value>(v) );
    }

    // Returns the contained Value, or the provided alternative if it holds an Error
    constexpr auto value_or(Value&& other) const noexcept -> const Value&&
    {
        return has_value()  ? value()
                            : std::forward<Value>(other);
    }

    // Returns the contained Value, or the provided alternative if it holds an Error
    constexpr auto value_or(Value& other) const noexcept -> const Value&&
    {
        return value_or( std::forward<Value>(other) );
    }

    // Unwraps the contained Error. If instead it contains an Value, throws an exception
    constexpr auto error() const noexcept(false) -> Error
    {
        return std::get<Error>(v);
    }

private:
    std::variant<Value, Error> v;
};
