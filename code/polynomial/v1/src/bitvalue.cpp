#include <iostream>

#include "bitvalue.h"

std::string fmtValue(BitValue v)
{
    using namespace std;
    bool flag = false;
    int t = 0;
    string s = "", s0 = "";
    for (int i = v.len; i >= 0; i--)
    {
        t = int(v.value >> i & 1);
        if (t == 1)
        {
            if (i > 0)
                s = "x^" + to_string(i);
            else if (i == 0)
                s = "1";

            if (flag)
            {
                s = " + " + s;
            }
            else
                flag = true;
            s0 += s;
        }
    }
    return s0;
}

void printPolynomail(BitValue v)
{
    using namespace std;
    bool flag = false;
    int t = 0;
    string s = "";
    for (int i = v.len; i >= 0; i--)
    {
        t = int(v.value >> i & 1);
        if (t == 1)
        {
            if (i > 0)
                s = "x^" + to_string(i);
            else if (i == 0)
                s = "1";

            if (flag)
            {
                s = " + " + s;
            }
            else
                flag = true;
            cout << s;
        }
    }
    cout << endl;
}

void test0()
{
    using namespace std;
    // BitValue b(0b1100111001010101001111);
    BitValue b(0b110011);
    string sb = fmtValue(b);
    // cout << s0 << endl;
    BitValue d(0b101);
    string sd = fmtValue(d);

    BitValue s = b / d;
    string ss = fmtValue(s);
    BitValue y = b % d;
    string sy = fmtValue(y);

    cout << sb << " / " << sd << endl;
    cout << " == " << ss << "  ...  " << sy << endl;
}

void test1()
{
    using namespace std;
    BitValue b, d(0b10011), s, y;
    uint64_t n = 1;
    for (int i = 0; i < 16; i++)
    {
        b.set_value(n << i);
        s = b / d;
        y = b % d;
        y.binprt();
        cout << "  " << fmtValue(y) << endl;
    }
}

int main(int argc, char **argv)
{
    test1();
    return 0;
}
