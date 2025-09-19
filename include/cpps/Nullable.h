#pragma once

#include <utility>   // for std::forward
#include <functional> // for std::invoke
#include <type_traits> // for constexpr optimization


namespace cpps {
	/// @brief Nullable<T> is a lightweight container that represents a possibly "null" value.
	/// 
	/// Unlike std::optional, this class is designed to be a simple, minimal wrapper intended 
	/// primarily for short-lived nullable returns (equivalent to TypeScript's T | undefined), 
	/// but also safe and efficient enough for longer-term use if needed.
	///
	/// It stores the value in-place without heap allocation, tracks validity via a bool,
	/// and exposes only minimal methods to check nullness and resolve the value.
	///
	/// Typical usage:
	/// ```cpp
	/// Nullable<int> n = someFunction();
	/// if (!n.IsNull()) {
	///     int v;
	///     n.Resolve(v); // v now has the value
	/// }
	/// ```
	///
	/// Or, if ignoring null cases:
	/// ```cpp
	/// int x = 0;
	/// n.Resolve(x); // x updated if valid, otherwise unchanged
	/// ```
	///
	/// Additionally, TryUse() allows you to supply a callable to operate on the value if valid.
	template<typename T>
	class Nullable {
	private:
		bool isValid = false;

		// Placement storage for T with proper alignment
		alignas(T) unsigned char storage[sizeof(T)];

		// Accessor to stored object (non-const)
		T* ptr() noexcept {
			return reinterpret_cast<T*>(storage);
		}

		// Accessor to stored object (const)
		const T* ptr() const noexcept {
			return reinterpret_cast<const T*>(storage);
		}

		// Destroys the stored object if valid.
		void Destroy() noexcept {
			if (isValid) {
				ptr()->~T();
				isValid = false;
			}
		}

	public:
		// Nullary constructor creates null state.
		Nullable() noexcept = default;

		// Construct from const T& (copy)
		Nullable(const T& value)
			: isValid(true) {
			new (storage) T(value);
		}

		// Construct from T&& (move)
		Nullable(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>)
			: isValid(true) {
			new (storage) T(std::move(value));
		}

		// Copy constructor
		Nullable(const Nullable& rhs)
			: isValid(rhs.isValid) {
			if (isValid) {
				new (storage) T(*rhs.ptr());
			}
		}

		// Move constructor
		Nullable(Nullable&& rhs) noexcept(std::is_nothrow_move_constructible_v<T>)
			: isValid(rhs.isValid) {
			if (isValid) {
				new (storage) T(std::move(*rhs.ptr()));
				rhs.Destroy();
			}
		}

		// Copy assignment
		Nullable& operator=(const Nullable& rhs) {
			if (this != &rhs) {
				if (isValid && rhs.isValid) {
					*ptr() = *rhs.ptr();
				}
				else if (isValid) {
					Destroy();
				}
				else if (rhs.isValid) {
					new (storage) T(*rhs.ptr());
					isValid = true;
				}
			}
			return *this;
		}

		// Move assignment
		Nullable& operator=(Nullable&& rhs) noexcept(std::is_nothrow_move_assignable_v<T>&& std::is_nothrow_move_constructible_v<T>) {
			if (this != &rhs) {
				if (isValid && rhs.isValid) {
					*ptr() = std::move(*rhs.ptr());
					rhs.Destroy();
				}
				else if (isValid) {
					Destroy();
				}
				else if (rhs.isValid) {
					new (storage) T(std::move(*rhs.ptr()));
					isValid = true;
					rhs.Destroy();
				}
			}
			return *this;
		}

		// Destructor destroys the contained object if valid.
		~Nullable() {
			Destroy();
		}

		/// @brief Check whether the contained value is null.
		/// @return true if null (empty), false otherwise.
		bool IsNull() const noexcept {
			return !isValid;
		}

		/// @brief Allows idiomatic if (nullable) checks.
		explicit operator bool() const noexcept {
			return isValid;
		}

		/**
		 * @brief Attempts to copy the contained value into 'destination'.
		 * If null, does nothing and returns false.
		 * Otherwise, assigns to destination and returns true.
		 *
		 * This is the primary way to extract the value for further use.
		 *
		 * @warning Initialize the destination variable in case of null.
		 * @param destination Reference to store the contained value if valid.
		 * @return true if value was assigned, false if null.
		 */
		bool Resolve(T& destination) const noexcept {
			if (!isValid) return false;
			destination = *ptr();

			/**
			 * @brief Attempts to move the contained value into 'destination'.
			 * If null, does nothing and returns false.
			 * Otherwise, moves into destination and returns true.
			 *
			 * This is the way to extract the value for further use without copying.
			 *
			 * @warning Successful moves destroy this object. It will become null!
			 * @param destination Reference to store the contained value if valid.
			 * @return true if value was assigned, false if null.
			 */
			template<typename F>
			bool MoveResolve(T && destination) {
				if (!isValid) return false;
				destination = std::move(*ptr());
				Destroy();
				return true;
			}
		};
	};
}
