#include "../include/cpps/Natural.h"
#include "../Util.h"

// TODO : It's not good to repeat logic a bunch. I'll use a lambda and std::invoke for abstraction helper

namespace cpps {
	// =============== Construction / Destruction ===============
	constexpr Nat::Nat() noexcept
		: value(0)
	{ }

	constexpr Nat::Nat(const Nat& rhs) noexcept
		: value(rhs.value)
	{ }

	constexpr Nat::Nat(int n) noexcept
		: value(n < 0 ? 0 : n)
	{
		if (n < 0) {
			WARN_CPPS("Warning: Nat does NOT store negatives. Clamped negative to 0.");
		}
	}

	constexpr Nat::Nat(diff_t n) noexcept
		: value(n < 0 ? 0 : n)
	{
		if (n < 0) {
			WARN_CPPS("Warning: Nat does NOT store negatives. Clamped negative to 0.");
		}
	}


	// =============== Conversions ===============

	constexpr Nat::operator diff_t() const noexcept { return value; }
	constexpr explicit Nat::operator int() const noexcept { return static_cast<int>(value); }



	// =============== Arithmetic Operators ===============
	constexpr Nat& Nat::operator += (const Nat& rhs) noexcept
	{
		this->value += rhs.value; return *this;
	}

	constexpr Nat& Nat::operator -= (const Nat& rhs) noexcept
	{
		// N is not closed on subtraction.
		// Specifically, the result exits N IFF RHS exceeds LHS
		if (rhs.value > this->value) {
			this->value = 0;
			WARN_CPPS("RHS > LHS. Clamped result to 0.");
		}
		else {
			this->value -= rhs.value;
		}
		return *this;
	}

	constexpr Nat& Nat::operator *= (const Nat& rhs) noexcept
	{
		this->value *= rhs.value;
		return *this;
	}

	constexpr Nat& Nat::operator /= (const Nat& rhs) noexcept
	{
		ASSERT_CPPS(rhs.value > 0, "Divide by 0 error.");
		this->value /= rhs.value;
		return *this;
	}



	// Symmetric Arithmetic
	constexpr Nat operator + (Nat left, const Nat& right) noexcept
	{
		return left.value += right.value;
	}

	constexpr diff_t operator - (Nat left, const Nat& right) noexcept
	{
		return left -= right;
	}

	constexpr Nat operator * (Nat left, const Nat& right) noexcept
	{
		return left *= right;
	}

	constexpr double operator / (Nat left, const Nat& right) noexcept
	{
		return left /= right;
	}



	// Cross-Type Arithmetic
	template <std::integral T>
	constexpr auto operator + (Nat& positive, T other) noexcept -> Nat::OpResultType<T>
	{
		using Result = Nat::OpResultType<T>;
		if constexpr (std::is_same_v<Result, Nat>)
		{
			return Nat(lhs.value + rhs);
		}
		else { return static_cast<Result>(lhs.value + rhs); }
	}

	template <std::integral T>
	constexpr auto operator + (T other, Nat& positive) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator * (Nat& positive, T other) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator * (T other, Nat& positive) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator / (Nat& positive, T other) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator / (T other, Nat& positive) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator - (Nat& positive, T other) noexcept -> Nat::OpResultType<T>
	{ }

	template <std::integral T>
	constexpr auto operator - (T other, Nat& positive) noexcept -> Nat::OpResultType<T>
	{ }



	// Comparisons
	//constexpr auto operator<=>(const Nat&, const Nat&) = default;

	// Stream Output
	std::ostream& operator<<(std::ostream& os, const Nat& positive) {
		return os << positive.value;
	}

	// Natural is an official alias for Nat -- longer but better clarity
	using Natural = cpps::Nat;
}
