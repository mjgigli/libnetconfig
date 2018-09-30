/*
 * Copyright (c) 2018 Matt Gigli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include "net/ip/prefix.hpp"


TEST(PrefixConstructorTest, Length) {
    net::ip::Prefix prefix(10);
    EXPECT_EQ(prefix.length(), 10);
}

TEST(PrefixConstructorTest, Copy) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(prefix1);
    EXPECT_EQ(prefix1.to_string_ipv4(), "255.255.0.0");
    EXPECT_EQ(prefix2.to_string_ipv4(), "255.255.0.0");
}

TEST(PrefixConstructorTest, Move) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(std::move(prefix1));
    EXPECT_EQ(prefix1.to_string_ipv4(), "255.255.0.0");
    EXPECT_EQ(prefix2.to_string_ipv4(), "255.255.0.0");
}

TEST(PrefixOperatorTest, CopyAssignment) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(8);
    prefix2 = prefix1;
    EXPECT_EQ(prefix1.to_string_ipv4(), "255.255.0.0");
    EXPECT_EQ(prefix2.to_string_ipv4(), "255.255.0.0");
}

TEST(PrefixOperatorTest, MoveAssignment) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(8);
    prefix2 = std::move(prefix1);
    EXPECT_EQ(prefix1.to_string_ipv4(), "255.255.0.0");
    EXPECT_EQ(prefix2.to_string_ipv4(), "255.255.0.0");
}

TEST(PrefixOperatorTest, Equality) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(16);
    net::ip::Prefix prefix3(17);
    EXPECT_TRUE(prefix1 == prefix2);
    EXPECT_FALSE(prefix1 == prefix3);
}

TEST(PrefixOperatorTest, Inequality) {
    net::ip::Prefix prefix1(16);
    net::ip::Prefix prefix2(17);
    net::ip::Prefix prefix3(16);
    EXPECT_TRUE(prefix1 != prefix2);
    EXPECT_FALSE(prefix1 != prefix3);
}

TEST(PrefixConvertTest, ToString) {
    net::ip::Prefix prefix1(16);
    EXPECT_EQ(prefix1.to_string_ipv4(), "255.255.0.0");

    net::ip::Prefix prefix2(32);
    EXPECT_EQ(prefix2.to_string_ipv4(), "255.255.255.255");

    net::ip::Prefix prefix3(128);
    EXPECT_EQ(prefix3.to_string_ipv4(), "255.255.255.255");

    net::ip::Prefix prefix4(15);
    EXPECT_EQ(prefix4.to_string_ipv4(), "255.254.0.0");
}

TEST(PrefixConvertTest, ToUint32) {
    uint32_t mask = 0;
    for (int i = 0; i <= 128; i++) {
        net::ip::Prefix prefix(i);
        if (i > 31) {
            mask = 0xffffffff;
        } else if (i > 0) {
            mask |= (1 << (32 - i));
        }
        EXPECT_EQ(prefix.to_uint32(), mask) << "i: " << i;
    }
}
