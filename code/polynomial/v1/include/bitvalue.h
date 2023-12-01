#ifndef __BITVALUE_H
#define __BITVALUE_H

#include <iostream>
#include <cstdio>
#include <string>

class BitValue
{
private:
public:
    uint64_t value;
    uint32_t len;
    BitValue(/* args */);
    BitValue(const uint64_t);
    BitValue(const uint64_t, const uint32_t);
    ~BitValue();

    void set_value(const uint64_t);
    void set_value(const uint64_t, const uint32_t);

    uint32_t get_value_bits_length();
    uint32_t get_value_bits_length(uint64_t);

    BitValue operator/(BitValue &);
    BitValue operator%(BitValue &);

    bool operator>(BitValue &);
    bool operator<(BitValue &);
    bool operator==(BitValue &);
    bool operator>=(BitValue &);

    void print(std::string s, uint64_t value);
    void binprt();
};

uint32_t BitValue::get_value_bits_length()
{
    uint32_t len = 0;
    uint64_t v = value;
    while (v > 0)
    {
        v >>= 1;
        len++;
    }
    return len;
}

uint32_t BitValue::get_value_bits_length(uint64_t value)
{
    uint32_t len = 0;
    while (value > 0)
    {
        value >>= 1;
        len++;
    }
    return len;
}

BitValue BitValue::operator%(BitValue &divisor)
{
    uint64_t quo = 0;
    uint64_t b = this->value;
    uint32_t l = this->len;

    if (*this < divisor)
    {
        quo = 0;
    }
    else if (*this == divisor)
    {
        quo = 1;
    }
    else
    {
        int move = 0;
        int i = 0;
        move = l - divisor.len;
        // print("dividend before:", b);
        // print("divisor:", divisor.value);
        // std::cout << "move: " << move << std::endl;
        while (b >= divisor.value)
        {
            // std::cout << "----" << std::endl;
            // 除
            b ^= divisor.value << move;
            // 更新商
            quo |= 1 << move;
            // 更新长度
            move = this->get_value_bits_length(b) - divisor.len;
            // std::cout << "move: " << move << std::endl;

            // print("quotent after:", quo);
            // print("dividend after:", b);
        }
    }

    return BitValue(b);
}

BitValue BitValue::operator/(BitValue &divisor)
{
    uint64_t quo = 0;
    uint64_t b = this->value;
    uint32_t l = this->len;

    if (*this < divisor)
    {
        quo = 0;
    }
    else if (*this == divisor)
    {
        quo = 1;
    }
    else
    {
        int move = 0;
        int i = 0;
        move = l - divisor.len;
        // print("dividend before:", b);
        // print("divisor:", divisor.value);
        // std::cout << "move: " << move << std::endl;
        while (b >= divisor.value)
        {
            // std::cout << "----" << std::endl;
            // 除
            b ^= divisor.value << move;
            // 更新商
            quo |= 1 << move;
            // 更新长度
            move = this->get_value_bits_length(b) - divisor.len;
            // std::cout << "move: " << move << std::endl;

            // print("quotent after:", quo);
            // print("dividend after:", b);
        }
    }

    return BitValue(quo);
}

bool BitValue::operator>(BitValue &r)
{
    if (value > r.value)
        return true;
    else
        return false;
}

bool BitValue::operator>=(BitValue &r)
{
    if (*this > r || *this == r)
        return true;
    else
        return false;
}

bool BitValue::operator<(BitValue &r)
{
    if (value < r.value)
        return true;
    else
        return false;
}

bool BitValue::operator==(BitValue &r)
{
    if (value == r.value)
        return true;
    else
        return false;
}

BitValue::BitValue(/* args */)
{
    value = 0;
    len = 0;
}

BitValue::BitValue(const uint64_t v)
{
    value = v;
    len = get_value_bits_length();
}

BitValue::BitValue(const uint64_t v, const uint32_t l)
{
    value = v;
    len = l;
}

void BitValue::set_value(const uint64_t v)
{
    value = v;
    len = get_value_bits_length();
}

void BitValue::set_value(const uint64_t v, const uint32_t l)
{
    value = v;
    len = l;
}

BitValue::~BitValue()
{
}

void BitValue::print(std::string s, const uint64_t value)
{
    BitValue v(value);
    // printf("0x%X\n", value);
    std::cout << s << "0b";
    for (int i = v.len; i >= 0; i--)
        printf("%d", int(v.value >> i & 1));
    printf(" (%d)\n", v.len);
}

void BitValue::binprt()
{
    // std::bitset<64> y(value);
    std::bitset<16> y(value);
    std::cout << y;
}
#endif