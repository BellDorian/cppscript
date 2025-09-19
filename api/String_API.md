class String API

# Constructors

String();  
String(const String& rhs) noexcept;  
String(String&& rhs) noexcept;  
String(const std::string_view text) noexcept;  
String(const char\* lit) noexcept;  
explicit String(std::string&& text) noexcept;

# Operator Overloads

### Assignment Operator =

String& operator = (String&& rhs);  
String& operator = (const String& rhs);  
String& operator = (std::string_view rtext);  
String& operator = (char symbol);

### Equivalence Operator ==

bool operator == (String& rhs) const noexcept;  
bool operator == (std::string_view rtext) const noexcept;  
bool operator == (char symbol) const noexcept;

### Non-Equivalence Operator !=

bool operator != (String& rhs) const noexcept;  
bool operator != (std::string_view rtext) const noexcept;  
bool operator != (char symbol) const noexcept;

### Indexing Operator []

char& operator[](size_t index);  
char operator[](size_t index) const;

### Concatenation Operator +

String operator+(const String& rhs) const noexcept;  
String operator+(const std::string_view rtext) const noexcept;  
String operator+(const char symbol) const noexcept;

### Append Operator (Mutating Concat) +=

String& operator +=(String& rhs) noexcept;  
String& operator +=(std::string_view rtext) noexcept;  
String& operator +=(char symbol) noexcept;

### Replication and Mutating Replication Operators _, _=

String operator*(const size_t n) const noexcept;  
String& operator *=(const size_t n);

<br>

# Static Methods

static constexpr int Asc(char target);

<br>

# Conversion Methods

operator std::string_view() const noexcept;  
std::string_view View() const noexcept;  
std::string Std() const noexcept;
constexpr int Asc(size_t index) const;

<br>

# Basic Search Methods (Non-Regex)

bool constexpr Includes(char target) const;
bool constexpr StartsWith(std::string_view prefix) const;  
bool constexpr EndsWith(std::string_view suffix) const;  
char At(size_t index) const noexcept;  
int Find(char target) const noexcept;  
int FindLast(char target) const noexcept;

<br>

# Portioning Methods

String Segment(size_t start, size_t end, bool blankIfOverflow = false) const noexcept;  
String Substring(size_t start, size_t length, bool blankIfOverflow = false) const noexcept;  
String Prefix(size_t length, bool blankIfOverflow = false) const noexcept;  
String Suffix(size_t length, bool blankIfOverflow = false) const noexcept;

# Synthesis Methods

### Concatenate

inline String Concat(const String& rhs) const noexcept;  
inline String Concat(std::string_view rtext) const noexcept;  
inline String Concat(char symbol) const noexcept;

### Append

inline String& Append(const String& rhs) noexcept;  
inline String& Append(std::string_view rtext) noexcept;  
inline String& Append(char symbol) noexcept;

### Prepend

inline void Prepend(const String& rhs) noexcept;  
inline void Prepend(std::string_view rtext) noexcept;  
inline void Prepend(char symbol) noexcept;

### Duplicate

String New() const noexcept;
inline String Clone() const noexcept;
void Repeat(size_t n);

<br>

# Formatting Methods

### Misc

inline void Reverse() noexcept;

### Casing

void Snake() noexcept;  
void Pascal() noexcept;  
void ApplyCase() noexcept;

### Trimming

void Trim() noexcept;  
void TrimStart() noexcept;  
void TrimEnd() noexcept;

### Padding

void PadStart(size_t n, char pad = ' ');  
void PadEnd(size_t n, char pad = ' ');

<br>

# Regex Methods

For the Future: Match, Search, Replace

<br>

# STL Compatibility Methods

### Iterators

std::string::iterator begin();  
std::string::iterator end();

### Const Iterators

const std::string::const_iterator begin() const;  
const std::string::const_iterator end() const;
