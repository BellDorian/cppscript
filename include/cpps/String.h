#pragma once
#include <string>
#include <iterator>

namespace cpps
{
	// Helper enum classes coupled with String	
	enum class LexiCompare : int
	{
		Before = -1,
		Same = 0,
		After = 1
	};

	enum class NumCompare : int
	{
		Less = -1,
		Equal = 0,
		More = 1
	};

	/**
	 * @class String
	 * @brief A super lightweight wrapper around std::string.
	 * Offers a more comfortable interface + convenient methods.
	 */
	class String
	{
	protected:
		std::string text;

	public:
		// =============== Constructors & Destructor =================

		/// @brief Nullary Constructor
		String();

		/// @brief Copy Constructor
		/// @param rhs the String to copy
		String(const String& rhs) noexcept;

		/// @brief Move Coonstructor
		/// @param rhs the String to move
		explicit String(String&& rhs) noexcept;

		/**
		 * Initializing Constructor (I).
		 * Copies from a std::string_view
		 *
		 * @param text source data
		 */
		String(const std::string_view text) noexcept;

		/**
		 * Initializing Constructor (II).
		 * Copies from a string-literal
		 *
		 * @param lit a string literal
		 */
		String(const char* lit) noexcept;

		/**
		 * Initializing Constructor (III).
		 * Copies from a single character
		 *
		 * @param symbol a single symbol
		 */
		String(const char symbol) noexcept;

		/**
		 * Initializing Move Constructor
		 *
		 * Moves source data from a std::string to this String
		 *
		 * @param text source data
		 */
		explicit String(std::string&& text) noexcept;

		/// @brief Destructor.
		~String();

		// =============== Operator Overloads =================

		/**
		 * Move Assignment enabled.
		 *
		 * @param rhs the String to move.
		 * @returns this String with the modification done.
		 */
		String& operator=(String&& rhs);

		String& operator = (const String& rhs);

		/**
		 * Assignment from std::string enabled.
		 *
		 * @param rtext the new contents for this String.
		 * @returns this String with new text
		 */
		String& operator = (std::string_view rtext);

		/**
		 * Assignment from char enabled.
		 *
		 * @param symbol a character to assign to this String.
		 * @returns this String, with new text
		 */
		String& operator = (char symbol);


		/**
		 * Equivalence with another String.
		 *
		 * @param rhs a String
		 * @returns true if this->text matches rhs.text
		 */
		bool operator == (String& rhs) const noexcept;

		/**
		 * Equivalence with a std::string_view.
		 *
		 * @param rtext a std::string_view
		 * @returns true if this->text matches rtext
		 */
		bool operator == (std::string_view rtext) const noexcept;

		/**
		 * Equivalence with a char
		 *
		 * @param rhs a String
		 * @returns true if this->text is length 1 and matches symbol.
		 */
		bool operator == (char symbol) const noexcept;


		/**
		 * Non-Equivalence with another String.
		 *
		 * @param rhs a String
		 * @returns true if this String's text does not match rhs.text
		 */
		bool operator != (String& rhs) const noexcept;

		/**
		 * Non-Equivalence with a std::string_view.
		 *
		 * @param rtext a std::string_view
		 * @returns true if this String's text does not match rtext
		 */
		bool operator != (std::string_view rtext) const noexcept;

		/**
		 * Non-Equivalence with a char.
		 *
		 * @param symbol a character
		 * @returns true if this->text is not a single char matching symbol.
		 */
		bool operator != (char symbol) const noexcept;


		/**
		 * Overloaded [] for char access.
		 * Returns the char at the specified index.
		 *
		 * @param index the index of the desired character
		 * @returns the char at the index
		 */
		char& operator[](size_t index) noexcept;

		/**
		 * Overloaded [] for char access.
		 * Returns the char at the specified index.
		 *
		 * @param index the index of the desired character
		 * @returns a copy of the char at the index
		 */
		char operator[](size_t index) const noexcept;


		/**
		 * Overloaded + for Concatenation Operator. (I)
		 * Concatenates this String with rhs, in a new object.
		 *
		 * @param rhs a String
		 * @returns a new String object with the result
		 */
		String operator+(const String& rhs) const noexcept;

		/**
		 * Overloaded + for Concatenation Operator. (II)
		 * Concatenates this String with rhs, in a new object.
		 *
		 * @param rtext a std::string_view
		 * @returns a new String object with the result
		 */
		String operator+(const std::string_view rtext) const noexcept;

		/**
		 * Overloaded + for Concatenation Operator. (III)
		 * Concatenates this String with rhs, in a new object.
		 *
		 * @param symbol a single character
		 * @returns a new String object with the result
		 */
		String operator+(const char symbol) const noexcept;


		/**
		 * Overloaded += for Append Operator. (I)
		 * Appends rhs to this String.
		 *
		 * @param rhs a String
		 * @returns this String, post-mutation.
		 */
		String& operator +=(String& rhs) noexcept;

		/**
		 * Overloaded += for Append Operator. (II)
		 * Appends rtext to this String.
		 *
		 * @param rtext a String
		 * @returns this String, post-mutation.
		 */
		String& operator +=(std::string_view rtext) noexcept;

		/**
		 * Overloaded += for Append perator. (III)
		 * Appends symbol to this String.
		 *
		 * @param symbol a char
		 * @returns this String, post-mutation
		 */
		String& operator +=(char symbol) noexcept;


		/**
		 * Overloaded * for Self-Concatenation Operator.
		 * Makes a new String using the text of this String
		 * in n self-concatenations
		 *
		 * @note n = 0 results in an empty string ""
		 *
		 * @param n number of times to repeat this String
		 * @returns a new String object
		 */
		String operator*(const size_t n) const noexcept;

		/**
		 * Overloaded *= for Self-Concatenation Operator.
		 * Mutates this string by replacing its text with
		 * the original content repeated n times.
		 *
		 * @note n = 0 results in an empty string ""
		 *
		 * @param n number of times to repeat this String
		 * @returns a new String object
		 */
		String& operator *=(const size_t n);



		// =============== Conversion Methods ===============

		/// @brief Implicit conversion TO std::string_view
		/// @returns A std::string_view object
		operator std::string_view() const noexcept;

		/**
		 * Converts String to std::string_view.
		 *
		 * Returns the underlying text of this String as a new std::string_view.
		 *
		 * @returns A std::string_view object.
		 * @warning The std::string_view is only valid until this String is mutated
		 */
		std::string_view View() const noexcept;

		/**
		 * Converts String to std::string.
		 *
		 * @returns the text of this String, stored in a new std::string
		 */
		std::string Std() const noexcept;

		// =============== Character Queries ===============

		/**
		 * Gives the value of the char at the specified index.
		 *
		 * @param index an index within this String
		 * @return the text of this String, stored in a new std::string
		 */
		char At(size_t index) const noexcept;

		/**
		 * Returns the index at which the target char first appears.
		 * If the specified char is not found, it returns -1.
		 *
		 * @param target the char to find
		 * @return the first index where the target appears, or -1.
		 */
		int Find(char target) const noexcept;

		/**
		 * Returns the last index at which the target char appears.
		 * If the specified char is not found, it returns -1.
		 *
		 * @param target the char to find
		 * @return the last index where the target appears, or -1.
		 */
		int FindLast(char target) const noexcept;

		/**
		 * Determines if the target char exists within this String.
		 *
		 * @param target the character to look for
		 * @returns true if the target exists in this String.
		 */
		bool Includes(char target) const noexcept;

		/**
		 * Determines if this String begins with the given prefix.
		 *
		 * @note Example : "Hel" is a valid prefix of "Hello World!".
		 *
		 * @param prefix The potential prefix of the String
		 * @returns true if this String begins with the same chars as prefix.
		 */
		bool StartsWith(std::string_view prefix) const noexcept;

		/**
		 *  Determines if this String ends with the given suffix.
		 *
		 * @note Example: "ld!" is a valid suffix of "Hello World!".
		 */
		bool EndsWith(std::string_view suffix) const noexcept;



		// =============== Substring Queries ===============

		/**
		 * Makes a new String copied from a portion of this String.
		 * The portion is specified by ENDPOINTS [start, end).
		 *
		 * @note The start index is inclusive, but the end index is EXCLUSIVE.
		 * @note Overflow: when `end` exceeds this String's length.
		 * @note Bad range: when `start > end`.
		 * @note Segment is endpoint-based while Substring is length-based
		 *
		 * @warning Bad range returns an empty String.
		 * @warning Overflow truncates by default, but can be toggled to return blank.
		 *
		 * @param start Inclusive start index.
		 * @param end excLusive end index.
		 * @param blankIfOverflow If true, overflow returns a blank String; otherwise, it truncates.
		 * @returns A new String object.
		 */
		String Segment(size_t start, size_t end, bool blankIfOverflow = false) const noexcept;

		/**
		 * Uses a specified length-based portion of this String to make a new String.
		 * The portion is specified by STARTING POSITION and LENGTH.
		 *
		 * @note Substring is similar to Prefix/Suffix, but with a variable start index.
		 *
		 * @warning Bad range returns an empty String.
		 * @warning Overflow truncates by default, but can be toggled to return blank.
		 *
		 * @param start Inclusive start index.
		 * @param length Number of characters in the desired segment.
		 * @param blankIfOverflow If true, overflow returns a blank String; otherwise, it truncates.
		 * @returns A new String object.
		 */
		String Substring(size_t start, size_t length, bool blankIfOverflow = false) const noexcept;

		/**
		 * Makes a new String containing a prefix of this String.
		 *
		 * @warning Overflow truncates by default, but can be toggled to return blank.
		 *
		 * @param length Number of characters in the desired prefix.
		 * @param blankIfOverflow If true, overflow returns a blank String; otherwise, it truncates.
		 * @returns A new String object.
		 */
		String Prefix(size_t length, bool blankIfOverflow = false) const noexcept;

		/**
		 * Makes a new String containing a suffix of this String.
		 *
		 * @warning Overflow truncates by default, but can be toggled to return blank.
		 *
		 * @param length Number of characters in the desired suffix.
		 * @param blankIfOverflow If true, overflow returns a blank String; otherwise, it truncates.
		 * @returns A new String object.
		 */
		String Suffix(size_t length, bool blankIfOverflow = false) const noexcept;




		// =============== Synthesis Methods ===============

		/**
		 * Non-Mutating concatenation.
		 * Makes a new String to store the concatenation of this
		 * String's text and the text of rhs.
		 *
		 * @note Concat is const, but Append is mutating.
		 * @param rhs a String
		 */
		String Concat(const String& rhs) const noexcept;

		/**
		 * Non-Mutating concatenation.
		 * Makes a new String to store the concatenation of this
		 * String's text and rtext.
		 *
		 * @note Concat is const, but Append is mutating.
		 * @param rtext a std::string_view
		 */
		String Concat(std::string_view rtext) const noexcept;

		/**
		 * Non-Mutating concatenation.
		 * Makes a new String to store the concatenation of this
		 * String's text and the text of rhs.
		 *
		 * @note Concat is const, but Append is mutating.
		 * @param symbol a character
		 */
		String Concat(char symbol) const noexcept;


		/**
		 * Appending (I)
		 * Adds the rhs to the end of this String.
		 *
		 * @param rhs a String object
		 */
		String& Append(const String& rhs) noexcept;

		/**
		 * Appending (II)
		 * Adds the rtext to the end of this String.
		 *
		 * @param rtext a std::string_view
		 */
		String& Append(std::string_view rtext) noexcept;

		/**
		 * Appending (III)
		 * Adds the symbol to the end of this String.
		 *
		 * @param symbol a character
		 */
		String& Append(char symbol) noexcept;

		/**
		 * Prepending (I)
		 * Adds the rhs to the start of this String.
		 *
		 * @param rhs a String object
		 */
		String& Prepend(const String& rhs) noexcept;

		/**
		 * Prepending (II)
		 * Adds the rtext to the start of this String.
		 *
		 * @param rtext a std::string_view
		 */
		String& Prepend(std::string_view rtext) noexcept;

		/**
		 * Mutating concatenation (III)
		 * Adds the symbol to the start of this String.
		 *
		 * @param symbol a character
		 */
		String& Prepend(char symbol) noexcept;

		/**
		 * Self-Appends this String n times.
		 *
		 * @note Example : String("Segfault").Repeat(2) --> "SegfaultSegfault"
		 */
		void Repeat(size_t n);



		// =============== String Formatting ===============
		/**
		 * Creates a new stack-allocated String (deep copy).
		 *
		 * @note
		 * Use this to apply transformations (e.g., casing or reversing)
		 * without modifying the original instance.
		 * @note
		 * Mutating methods affect the returned copy -- not the original.
		 * @note
		 * Example : String.New().Reverse().Camel();
		 *
		 * @returns A new, independent copy of this String.
		 */
		String New() const noexcept;

		/**
		 * An alias for the method C-Script calls New().
		 *
		 * Creates a new stack-allocated String (deep copy).
		 *
		 * @note
		 * Use this to apply transformations (e.g., casing or reversing)
		 * without modifying the original instance.
		 * @note
		 * Mutating methods affect the returned copy -- not the original.
		 * @note
		 * Example : String.Clone().Reverse().Camel();
		 *
		 * @returns A new, independent copy of this String.
		 *
		 * @see String::New()
		 */
		inline String Clone() const noexcept;

		/**
		 * Reverses the order of characters within this String.
		 *
		 * @note
		 * Example : "dorian" --> "nairod"
		 */
		void Reverse() noexcept;

		/**
		 * Attempts to convert this String into camelCase formatting.
		 * @note Example : "some phrase" --> "somePhrase"
		 */
		void Camel() noexcept;

		/**
		 * Attempts to convert this String into snake_case formatting.
		 *
		 * @note Example : "some phrase" --> "some_phrase"
		 */
		void Snake() noexcept;

		/**
		 * Attempts to convert this String into PascalCase formatting.
		 *
		 * @note Example : "some phrase" --> "SomePhrase"
		 */
		void Pascal() noexcept;

		/**
		 * Attempts to apply the specified case scheme to this String.
		 *
		 * @note Options : Camel | Pascal | Snake | Upper | Lower
		 * @note Example : some phrase --> somePhrase
		 */
		void ApplyCase() noexcept;

		// Maybe add a static void overload taking std::string_view param?

		/**
		 * Makes the alphabetical characters in this String lowercase.
		 *
		 */
		void ToLower() noexcept;

		/**
		 * Makes the alphabetical characters in this String uppercase.
		 *
		 */
		void ToUpper() noexcept;

		/**
		 * Removes leading and trailing spaces from this String.
		 *
		 * @note Example : "  hello word  " --> "hello world"
		 */
		void Trim() noexcept;

		/**
		 * Removes leading spaces from this String.
		 *
		 * @note Example : "  hello world  " --> "hello world  "
		 */
		void TrimStart() noexcept;

		/**
		 * Removes trailing spaces from this String.
		 *
		 * @note Example : "  hello world  " --> "  hello world"
		 */
		void TrimEnd() noexcept;


		/**
		 * Pads the start of this String until it reaches length n.
		 *
		 * @param n the number of pad characters to prepend to this string.
		 * @param pad the character to pad this String with.
		 */
		void PadStart(size_t n, char pad = ' ');

		/**
		 * Pads the end of this String until it reaches length n.
		 *
		 * @param n the number of pad characters to append to this String.
		 * @param pad the character to pad this String with.
		 */
		void PadEnd(size_t n, char pad = ' ');


		// =============== Regex Methods ===============
		/*
			Future: Match, Search, Replace
		*/


		// =============== Deprecated Methods for STL Compatibility ===============
		std::string::iterator begin();
		std::string::iterator end();

		const std::string::const_iterator begin() const;
		const std::string::const_iterator end() const;


		// =============== Static Methods ===============
		/**
		 * Returns the ASCII code associated with the target char.
		 *
		 * @note Non-ASCII characters return -1.
		 * @param target the char to convert to ASCII
		 * @return an ASCII code or -1
		 */
		static constexpr int Asc(char target);

		/**
		 * Determines whether the left string is lexically before, after, or the same as the right string.
		 *
		 *  e.g. Compare("dorian", "belljr")  → After
		 *
		 *  e.g. Compare("clean", "code")     → Before
		 *
		 * @note The comparison is LEFT TO RIGHT, like a typical binary comparison.
		 * @note If one string is a prefix of the other, the shorter string comes first.
		 *
		 * @param left  The string to compare.
		 * @param right The string to compare against.
		 * @returns The lexical position of `left` relative to `right`: Before, After, or Same.
		 */
		static LexiCompare Compare(std::string_view left, std::string_view right);

	};
}

//#include "String.inl";


