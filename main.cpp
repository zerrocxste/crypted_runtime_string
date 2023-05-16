#include <iostream>

#ifdef _MSC_VER
#define FINLINE __forceinline
#else
#define FINLINE __attribute__((always_inline))
#endif

constexpr auto KEY = 32;
template <typename Ch, std::size_t Sz>
class CXStr
{
public:
	Ch buf[Sz / sizeof(Ch)];
public:
	FINLINE constexpr CXStr(const Ch str[])
	{
		for (std::size_t i = 0; i < (Sz / sizeof(Ch)); i++)
		{
			buf[i] = str[i] ^ KEY;
			buf[i] += (i & 1) ? 1 : -1;
		}
	}

	FINLINE Ch* get() const
	{
		volatile auto ret = (Ch*)this->buf;
		for (std::size_t i = 0; i < (Sz / sizeof(Ch)); i++)
		{
			ret[i] += (i & 1) ? -1 : 1;
			ret[i] ^= KEY;
		}
		return ret;
	}
};

#define cxstr(str) []() { auto v = *str; constexpr CXStr<decltype(v), sizeof(str)> cr(str); return cr; }().get()

int main(int argc, char* argv[], char* envp[])
{
	printf("%s\n", cxstr("134567890 AYE"));
	printf("%ws\n", cxstr(L"134567890 AYE"));
}
