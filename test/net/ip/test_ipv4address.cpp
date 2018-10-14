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

#include <string>

#include "net/ip/ipv4.hpp"

TEST(Ipv4AddressConstructorTest, Default) {
    net::ip::Ipv4Address addr;
    EXPECT_EQ(addr.to_uint32(), 0);
}

TEST(Ipv4AddressConstructorTest, Uint32) {
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(addr.to_uint32(), 0x01020304);
}

TEST(Ipv4AddressConstructorTest, String) {
    net::ip::Ipv4Address addr("1.2.3.4");
    EXPECT_EQ(addr.to_string(), "1.2.3.4");
}

TEST(Ipv4AddressConstructorTest, Copy) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2(addr1);
    EXPECT_EQ(addr1.to_string(), "1.2.3.4");
    EXPECT_EQ(addr2.to_string(), "1.2.3.4");
}

TEST(Ipv4AddressConstructorTest, Move) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2(std::move(addr1));;
    EXPECT_EQ(addr2.to_string(), "1.2.3.4");
    EXPECT_EQ(addr1.to_string(), "0.0.0.0");
}

TEST(Ipv4AddressFamilyTest, Ipv4Family) {
    net::ip::Ipv4Address addr;
    EXPECT_EQ(addr.family(), net::ip::Family::IPV4);
}

TEST(Ipv4AddressConvertTest, ToString) {
    net::ip::Ipv4Address addr1(0x01020304);
    EXPECT_EQ(addr1.to_string(), "1.2.3.4");

    net::ip::Ipv4Address addr2(0xffffffff);
    EXPECT_EQ(addr2.to_string(), "255.255.255.255");
}

TEST(Ipv4AddressConvertTest, ToUint32) {
    net::ip::Ipv4Address addr("1.2.3.4");
    EXPECT_EQ(addr.to_uint32(), 0x01020304);
}

TEST(Ipv4AddressConvertTest, Address) {
    net::ip::Ipv4Address addr("1.2.3.4");
    net::ip::Address a = addr.address();
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(a.v4[i], i+1);
    }
}

TEST(Ipv4AddressOperatorTest, CopyAssignment) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2;
    addr2 = addr1;
    EXPECT_EQ(addr2.to_string(), "1.2.3.4");
    EXPECT_EQ(addr1.to_string(), "1.2.3.4");
}

TEST(Ipv4AddressOperatorTest, MoveAssignment) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2;
    addr2 = std::move(addr1);
    EXPECT_EQ(addr2.to_string(), "1.2.3.4");
    EXPECT_EQ(addr1.to_string(), "0.0.0.0");
}

TEST(Ipv4AddressOperatorTest, Comparison) {
    net::ip::Ipv4Address addr1("1.2.3.3");
    net::ip::Ipv4Address addr2("1.2.3.4");
    net::ip::Ipv4Address addr3("1.2.3.4");
    net::ip::Ipv4Address addr4("1.2.3.5");

    EXPECT_LT(addr1.Compare(addr2), 0);
    EXPECT_EQ(addr2.Compare(addr3), 0);
    EXPECT_GT(addr2.Compare(addr1), 0);

    EXPECT_TRUE(addr1 < addr2);
    EXPECT_FALSE(addr2 < addr1);
    EXPECT_TRUE(addr1 <= addr2);
    EXPECT_TRUE(addr2 <= addr3);
    EXPECT_FALSE(addr2 <= addr1);

    EXPECT_TRUE(addr2 > addr1);
    EXPECT_FALSE(addr1 > addr2);
    EXPECT_TRUE(addr2 >= addr1);
    EXPECT_TRUE(addr3 >= addr2);
    EXPECT_FALSE(addr1 >= addr2);

    EXPECT_TRUE(addr2 == addr3);
    EXPECT_FALSE(addr1 == addr2);
}

TEST(Ipv4AddressOperatorTest, BitwiseAnd) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2("255.255.0.0");
    net::ip::Ipv4Address addr3 = addr1 & addr2;
    EXPECT_EQ(addr3.to_uint32(), 0x01020000);
}

TEST(Ipv4AddressOperatorTest, BitwiseOr) {
    net::ip::Ipv4Address addr1("1.2.0.0");
    net::ip::Ipv4Address addr2("0.0.3.4");
    net::ip::Ipv4Address addr3 = addr1 | addr2;
    EXPECT_EQ(addr3.to_uint32(), 0x01020304);
}

TEST(Ipv4AddressOperatorTest, PrefixIncrement) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2 = ++addr1;
    EXPECT_EQ(addr1.to_uint32(), 0x01020305);
    EXPECT_EQ(addr2.to_uint32(), 0x01020305);
}

TEST(Ipv4AddressOperatorTest, PostfixIncrement) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2 = addr1++;
    EXPECT_EQ(addr1.to_uint32(), 0x01020305);
    EXPECT_EQ(addr2.to_uint32(), 0x01020304);
}

TEST(Ipv4AddressOperatorTest, PrefixDecrement) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2 = --addr1;
    EXPECT_EQ(addr1.to_uint32(), 0x01020303);
    EXPECT_EQ(addr2.to_uint32(), 0x01020303);
}

TEST(Ipv4AddressOperatorTest, PostfixDecrement) {
    net::ip::Ipv4Address addr1("1.2.3.4");
    net::ip::Ipv4Address addr2 = addr1--;
    EXPECT_EQ(addr1.to_uint32(), 0x01020303);
    EXPECT_EQ(addr2.to_uint32(), 0x01020304);
}

TEST(Ipv4AddressMethodsTest, IsUnspecified) {
    net::ip::Ipv4Address addr1;
    EXPECT_EQ(addr1.is_unspecified(), true);

    net::ip::Ipv4Address addr2("1.2.3.4");
    EXPECT_EQ(addr2.is_unspecified(), false);
}

TEST(Ipv4AddressMethodsTest, IsBroadcast) {
    net::ip::Ipv4Address addr1("255.255.255.255");
    EXPECT_EQ(addr1.is_broadcast(), true);

    net::ip::Ipv4Address addr2("1.2.3.4");
    EXPECT_EQ(addr2.is_broadcast(), false);
}

TEST(Ipv4AddressMethodsTest, IsLoopback) {
    // 127.0.0.0-127.255.255.255
    for (uint32_t i = 0x7f000000; i <= 0x7fffffff; i++) {
        net::ip::Ipv4Address addr(i);
        EXPECT_EQ(addr.is_loopback(), true);
    }

    // Verify just outside the boundary
    net::ip::Ipv4Address addr1(0x7effffff);
    EXPECT_EQ(addr1.is_loopback(), false);
    net::ip::Ipv4Address addr2(0x80000000);
    EXPECT_EQ(addr1.is_loopback(), false);
}

TEST(Ipv4AddressMethodsTest, IsMulticast) {
    // 224.0.0.0-224.255.255.255
    for (uint32_t i = 0xe0000000; i <= 0xe0ffffff; i++) {
        net::ip::Ipv4Address addr(i);
        EXPECT_EQ(addr.is_multicast(), true);
    }

    // Assume in between is OK

    // 239.0.0.0-224.255.255.255
    for (uint32_t i = 0xef000000; i <= 0xefffffff; i++) {
        net::ip::Ipv4Address addr(i);
        EXPECT_EQ(addr.is_multicast(), true);
    }

    // Verify just outside the boundary
    net::ip::Ipv4Address addr1(0xdfffffff);
    EXPECT_EQ(addr1.is_multicast(), false);
    net::ip::Ipv4Address addr2(0xf0000000);
    EXPECT_EQ(addr1.is_multicast(), false);
}

TEST(Ipv4AddressMethodsTest, IsUnicast) {
    // Just based on the top octet
    for (uint64_t i = 0x00000001; i <= 0xff000001; i += 0x01000000) {
        net::ip::Ipv4Address addr(i);
        if (addr.is_unspecified() ||
            addr.is_broadcast() ||
            addr.is_multicast()) {
            EXPECT_EQ(addr.is_unicast(), false);
        } else {
            EXPECT_EQ(addr.is_unicast(), true);
        }
    }
}
