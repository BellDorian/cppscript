#pragma once
#include <string>  // for std::string
#include <cstdlib> // for std::size_t
#include <memory>

namespace cpps::detail::alias
{
	// Std types
	//using string = std::string;
	using view = std::string_view;
	using size_t = std::size_t;
	using string = std::string;

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template <typename T>
	using Shared = std::shared_ptr<T>;
}