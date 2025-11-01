#include <cassert>
#include "../../alias.h"
// TODO : Modulo, Exponents

namespace cpps {
	using namespace alias;

	class Nat final
	{
		static_assert(std::regular<Nat>);
		static_assert(std::totally_ordered<Nat>);


		template<std::integral T>
		struct op_result_type {
			using type =
				// Case 1: Rhs is a Nat --> return Nat
				std::conditional_t < std::is_same_v<T, Nat>, Nat,

				// Case 2: Rhs is a signed type smaller than diff_t --> return diff_t
				std::conditional_t<std::is_signed_v<T> && sizeof(T) < sizeof(std::ptrdiff_t),
				std::ptrdiff_t,

				// Case 3: Rhs is bigger than diff_t --> return typeof(Rhs)
				T>>;
		};

		template<std::integral T>
		using OpResultType = typename op_result_type<T>::type;

	private:
		diff_t value;

	public:
		constexpr Nat() noexcept;
		constexpr Nat(const Nat& rhs) noexcept;
		constexpr Nat(int n) noexcept;
		constexpr Nat(diff_t n);


		constexpr operator diff_t() const noexcept;
		constexpr explicit operator int() const noexcept;

		// Arithmetic Operators
		constexpr Nat& operator += (const Nat& rhs) noexcept;
		constexpr Nat& operator *= (const Nat& other) noexcept;
		constexpr Nat& operator /= (const Nat& other) noexcept;
		constexpr Nat& operator -= (const Nat& rhs) noexcept;

		// Symmetric Arithmetic
		friend constexpr Nat operator + (Nat left, const Nat& right) noexcept;
		friend constexpr Nat operator * (Nat left, const Nat& right) noexcept;
		friend constexpr double operator / (Nat left, const Nat& right) noexcept;
		friend constexpr diff_t operator - (Nat left, const Nat& right) noexcept;

		// Cross-Type Arithmatic
		template <std::integral T>
		friend constexpr auto operator + (Nat& positive, T other) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator + (T other, Nat& positive) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator * (Nat& positive, T other) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator * (T other, Nat& positive) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator / (Nat& positive, T other) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator / (T other, Nat& positive) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator - (Nat& positive, T other) noexcept -> OpResultType<T>;
		template <std::integral T>
		friend constexpr auto operator - (T other, Nat& positive) noexcept -> OpResultType<T>;



		// Comparisons
		constexpr bool operator == (const Nat& rhs);
		constexpr bool operator != (const Nat& rhs);
		constexpr bool operator > (const Nat& rhs);
		constexpr bool operator >= (const Nat& rhs);
		constexpr bool operator < (const Nat& rhs);
		constexpr bool operator <= (const Nat& rhs);

		// Symmetric Comparisons
		friend constexpr bool operator == (Nat left, const Nat& right) noexcept;
		friend constexpr bool operator != (Nat left, const Nat& right) noexcept;
		friend constexpr bool operator > (Nat left, const Nat& right) noexcept;
		friend constexpr bool operator >= (Nat left, const Nat& right) noexcept;
		friend constexpr bool operator < (Nat left, const Nat& right) noexcept;
		friend constexpr bool operator <= (Nat left, const Nat& right) noexcept;

		// Cross-Type Comparisons
		template <std::integral T>
		friend constexpr bool operator == (Nat& positive, T other) noexcept;
		template <std::integral T>
		friend constexpr bool operator != (T other, Nat& positive) noexcept;
		template <std::integral T>
		friend constexpr bool operator > (Nat& positive, T other) noexcept;
		template <std::integral T>
		friend constexpr bool operator >= (T other, Nat& positive) noexcept;
		template <std::integral T>
		friend constexpr bool operator < (Nat& positive, T other) noexcept;
		template <std::integral T>
		friend constexpr bool operator <= (T other, Nat& positive) noexcept;


		// Stream Output
		friend std::ostream& operator<<(std::ostream& os, const Nat& positive);
	};

	// Natural is an official alias for Nat -- longer but better clarity
	using Natural = Nat;

}

