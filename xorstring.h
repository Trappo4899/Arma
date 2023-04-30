#ifndef XOR_STRING_H
#define XOR_STRING_H

template<typename T, size_t length, size_t key>
class XorString
{
private:

    // we use std::array as we define it with a fixed length so we cant messup and change the size of the string

    std::array<T, length> m_str;

private:

    constexpr T encrypt_single(T character)
    {
        return character ^ key;
    }

    constexpr T decrypt_single(T character)
    {
        return encrypt_single(character);
    }

public:

    template<size_t... seq>
    constexpr XorString(const T(&str)[length], std::index_sequence<seq...>) : m_str{ encrypt_single(str[seq])... } { }

    auto decrypt()
    {
        for (int i = 0; i < length; ++i)
        {
            m_str[i] = decrypt_single(m_str[i]);
        }

        return m_str.data();
    }
};

template<typename T, size_t length>
auto Xor(const T(&s)[length])
{
    return XorString<T, length, __LINE__>(s, std::make_index_sequence<length>()).decrypt();
}

#ifdef _DEBUG
#define XOR( string ) string
#else
#define XOR( string ) Xor(string)
#endif

#endif