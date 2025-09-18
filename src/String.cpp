/* 	Copyright 2025 Dorian Bell Jr.
	Licensed under the Apache License, Version 2.0.
	See LICENSE and NOTICE files for full details.
*/

#include "../include/cpps/String.h"
#include "../include/cpps/detail/alias.h"

// Definition of the cpps::String clas

/*  Recall the std nicknames (defined in String.h)
	std::string = string
	std::string_view = view
	std::size_t = size_t
*/

// ============== Constructors & Destructor =================
namespace cpps
{
	using namespace detail::alias;

	String::String()
		: text("")
	{ }

	String::String(const String& rhs) noexcept
		: text(rhs)
	{ }

	String::String(String&& rhs) noexcept
		: text(std::move(rhs.text))
	{ }

	String::String(const view text) noexcept
		: text(text)
	{ }

	String::String(const char* lit) noexcept
		: String(std::string_view(lit)) { }

	String::String(const char symbol) noexcept
		: text()
	{
		text += symbol;
	}

	explicit String::String(std::string&& text) noexcept
		: text(std::move(text))
	{ }

	String::~String() { }


	// ==================== Operator Overloads ======================

	// =============== ASSIGNMENT =================
	String& String::operator=(String&& rhs)
	{
		text = std::move(rhs);
		return *this;
	}

	String& String::operator=(const String& rhs) { }

	String& String::operator=(std::string_view rtext) { }

	String& String::operator=(char symbol) { }


	// =============== EQUIVALENCE =================
	bool String::operator == (String& rhs) const noexcept
	{
		// Check for shared occupation in memory
		if (this == std::addressof(rhs)) { return true; }
		return text == rhs.text;
	}

	bool String::operator == (std::string_view rtext) const noexcept
	{
		return text == rtext;
	}

	bool String::operator == (char symbol) const noexcept
	{
		if (text.length() == 1)
		{
			return text[0] == symbol;
		}
		return false;
	}


	// =============== NON-EQUIVALENCE =================
	bool String::operator != (String& rhs) const noexcept
	{
		return !(*this == rhs);
	}

	bool String::operator != (std::string_view rtext) const noexcept
	{
		return !(*this == rtext);
	}

	bool String::operator != (char symbol) const noexcept
	{
		return !(*this == symbol);
	}


	// =============== INDEXING =============
	char& String::operator[](size_t index)
	{
		if (index < text.length())
		{
			return text[index];
		}

		throw std::out_of_range("invalid index");
	}

	char String::operator[](size_t index) const
	{
		return text[index];
	}


	// =============== CONCAT =================
	String String::operator+(const String& rhs) const
	{
		// Call this->Std() to explictly convert String -> std::string
		string newText = this->Std();
		newText.append(rhs.text);
		return String(newText);
	}

	String String::operator+(const std::string_view rhs) const
	{
		String newString(*this);
		newString.Concat(rhs);
		return newString;
	}

	String String::operator+(const char symbol) const noexcept
	{
		string newText = text + symbol;
		return String(newText);
	}


	// =============== APPEND =================
	String& String::operator +=(String& rhs) noexcept
	{
		text += rhs.text;
		return *this;
	}

	String& String::operator +=(std::string_view rtext) noexcept
	{
		text += rtext;
		return *this;
	}

	String& String::operator +=(char symbol) noexcept
	{
		text += symbol;
		return *this;
	}


	// =============== SELF-CONCAT =================
	String String::operator*(size_t n) const noexcept
	{
		if (n == 0) { return String(""); }

		std::string newText;
		newText.reserve(text.size() * n);

		for (size_t i = 0; i < n; ++i) {
			newText += text;
		}

		return String(newText);
	}

	String& String::operator *=(const size_t n)
	{
		if (n == 0) { text.clear(); return *this; }

		std::string original = text;
		text.reserve(original.size() * n);

		for (size_t i = 1; i < n; ++i) {
			text += original;
		}
		return *this;
	}



	// ==================== Conversion Methods ====================
	String::operator std::string_view() const noexcept
	{
		return text;
	}

	std::string_view String::View() const noexcept
	{
		return text;
	}

	std::string String::Std() const noexcept
	{
		return text;
	}


	// =============== Basic Search Functions ===============

	// TODO: make nullor<char>
	char String::At(size_t index) const noexcept
	{
		// return Nullor<char>(text[index], index < text.length());
	}

	int String::Find(char target) const noexcept
	{
		for (size_t i = 0; i < text.length(); ++i)
		{
			if (text[i] == target) { return i; }
		}
		return -1;
	}

	int String::FindLast(char target) const noexcept
	{
		for (size_t i = text.length() - 1; i >= 0; --i)
		{
			if (text[i] == target) { return i; }
		}
		return -1;
	}

	constexpr bool String::Includes(char target) const
	{
		for (char i : text)
		{
			if (i == target)
			{
				return true;
			}
		}
		return false;
	}

	constexpr bool String::StartsWith(std::string_view prefix) const noexcept
	{
		return text.starts_with(prefix);
	}

	constexpr bool String::EndsWith(std::string_view suffix) const noexcept
	{
		return text.ends_with(suffix);
	}



	// =============== Portioning Methods ===============
	String String::Segment(size_t start, size_t end, bool blankIfOverflow = false) const noexcept
	{
		// Case A: Bad range --> early return
		// This also covers the edge case where text is empty
		if (start >= text.length() || end <= start) { return String(); }

		// Case B: Requested string is too long AND user wants us to return blank
		if (blankIfOverflow && (end > text.length()))
		{
			return String();
		}
		// Case C: Default behavior: just truncate if overflow occurs/
		else
		{
			// Making end exlusive allows for simple calculations regarding segments. 
			std::string seg(text.substr(start, end - start));
			return String(std::move(seg));
		}
	}

	String String::Substring(size_t start, size_t length, bool blankIfOverflow = false) const noexcept
	{
		// Case A: Early return for nonsense start index
		// This also covers the edge case where text is empty
		if (start >= text.length()) { return String(); }

		// Case B: Return empty for overflow if flag is set.
		// The flag means overflow must return empty String instead of a truncated String
		if (blankIfOverflow && ((start + length) > text.length()))
		{
			return String();
		}

		// Case C: Default behavior: just truncate if overflow occurs. 
		return String(text.substr(start, length));
	}

	String String::Prefix(size_t length, bool blankIfOverflow = false) const noexcept
	{
		if (text.length() == 0 || length == 0)
		{
			// Case A: Early return for empty request or empty this->text member
			return String();
		}
		else if (text.length() > length)
		{
			// Case B: No overflow occurred
			return String(text.substr(0, length));
		}
		else if (blankIfOverflow)
		{
			// Case C: Overflow occurred AND the user wants blank return
			return String();
		}
		else
		{
			// Either case D or E
			// Case D: The user requested the full string
			// Case E: Overflow occurred but we can do the default behavior of truncating to this
			return String(*this);
		}
	}

	String String::Suffix(size_t length, bool blankIfOverflow = false) const noexcept
	{
		if (text.length() == 0 || length == 0)
		{
			// Case A: Early return for empty request or empty this->text member
			return String();
		}
		else if (text.length() > length)
		{
			// Case B: No overflow occurred
			return String(text.substr(text.length() - length));
		}
		else if (blankIfOverflow)
		{
			// Case C: Overflow occurred AND the user wants blank return
			return String();
		}
		else
		{
			// Either case D or E
			// Case D: The user requested the full string
			// Case E: Overflow occurred but we can do the default behavior of truncating to this
			return String(*this);
		}
	}



	// =============== Synthesis Methods ===============
	String String::Concat(const String& rhs) const noexcept
	{
		return String(*this).Append(rhs);
	}

	String String::Concat(std::string_view rtext) const noexcept
	{
		return String(*this).Append(rtext);
	}

	String String::Concat(char symbol) const noexcept
	{
		return String(text).Append(symbol);
	}


	String& String::Append(const String& rhs) noexcept
	{
		text.reserve(text.length() + rhs.text.length());
		text.append(rhs.text);
		return *this;
	}

	String& String::Append(std::string_view rtext) noexcept
	{
		text.reserve(text.length() + rtext.length());
		text.append(rtext);
		return *this;
	}

	String& String::Append(char symbol) noexcept
	{
		text.push_back(symbol);
		return *this;
	}


	String& String::Prepend(const String& rhs) noexcept
	{
		text = String(rhs).Append(text);
		return *this;
	}

	String& String::Prepend(std::string_view rtext) noexcept
	{
		text = String(rtext).Append(text);
		return *this;
	}

	String& String::Prepend(char symbol) noexcept
	{
		String(symbol) += text;
	}



	// =============== String Formatting ===============
	String String::New() const noexcept
	{
		return String(*this);
	}

	inline String String::Clone() const noexcept
	{
		return New();
	}

	void String::Camel() noexcept
	{ }

	void String::Snake() noexcept
	{ }

	void String::Pascal() noexcept { }

	void String::ToLower() noexcept
	{ }

	void String::ToUpper() noexcept
	{ }

	void String::ApplyCase() noexcept { }

	void String::Reverse() noexcept
	{
		// Two-pointer all the way
		if (text.length() < 2) { return; }

		for (size_t l = 0, r = text.length() - 1; l < r; ++l, --r)
		{
			std::swap(text[l], text[r]);
		}
	}

	void String::Trim() noexcept
	{ }

	void String::TrimStart() noexcept
	{ }

	void String::TrimEnd() noexcept
	{ }

	void String::PadStart(size_t n, char pad = ' ')
	{
		if (text.length() < n)
		{
			text.insert(0, n - text.length(), pad);
		}
	}

	void String::PadEnd(size_t n, char pad = ' ')
	{
		if (text.length() < n)
		{
			text.append(n - text.length(), pad);
		}
	}

	void String::Repeat(size_t n)
	{ }



	// =============== Deprecated Methods for STL Compatibility ===============
	std::string::iterator String::begin() { return text.begin(); }
	std::string::iterator String::end() { return text.end(); }

	const std::string::const_iterator String::begin() const { return text.begin(); }
	const std::string::const_iterator String::end() const { return text.end(); }


	// =============== Static Methods ===============
	constexpr int String::Asc(char target)
	{
		return static_cast<int>(target);
	}

	LexiCompare String::Compare(std::string_view left, std::string_view right) { }

}