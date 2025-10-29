#include <cpps/String.h>
#include <iostream>

using namespace cpps;


void Print(std::string_view text) {
	std::cout << text << std::endl;
}
int main()
{
	String a = "Dorian Bell Jr.";
	Print(a);
}