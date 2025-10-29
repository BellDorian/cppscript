#pragma once
#include <string>  // for std::string
#include <cstdlib> // for std::size_t, std::ptrdiff_t
#include <memory>  // for smart ptrs

namespace cpps
{
	namespace alias
	{
		// std namespace aliases
		using string = std::string;
		using view = std::string_view;
		using size_t = std::size_t;
		using diff_t = std::ptrdiff_t;
		using string = std::string;

		template <typename T>
		using Unique = std::unique_ptr<T>;

		template <typename T>
		using Shared = std::shared_ptr<T>;
	}
}