#include <bitset>
#include <string>
#include <iostream>

template <std::size_t N>
inline
void
rotate(std::bitset<N>& b, unsigned m)
{
b = b << m | b >> (N-m);
}

int main()
{
std::bitset<20> b(std::string("00001111111111111111"));
std::cout << b << '\n';
rotate(b, 4);
std::cout << b << '\n';
}