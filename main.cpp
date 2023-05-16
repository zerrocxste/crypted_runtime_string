#include <iostream>

constexpr auto KEY = 32;
template <typename Ch, std::size_t Sz>
class CXStr
{
public:
	Ch buf[Sz / sizeof(Ch)];
public:
	__forceinline constexpr CXStr(const Ch str[])
	{
		for (std::size_t i = 0; i < (Sz / sizeof(Ch)); i++)
		{
			buf[i] = str[i] ^ KEY;
			buf[i] += (i & 1) ? 1 : -1;
		}
	}

	__forceinline Ch* get() const
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

#define crstr(str) []() { auto v = *str; constexpr CXStr<decltype(v), sizeof(str)> cr(str); return cr; }().get()

int main(int argc, char* argv[], char* envp[])
{
	printf("%s\n", crstr("134567890 AYE"));
	printf("%ws\n", crstr(L"134567890 AYE"));
}