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

#include "net/ip/ipv4_address_range_iterator.hpp"

TEST(Ipv4AddressRangeIteratorConstructorTest, Default) {
    net::ip::Ipv4AddressRangeIterator it1;
    net::ip::Ipv4AddressRangeIterator it2(0);
    EXPECT_EQ(it1, it2);
}

TEST(Ipv4AddressRangeIteratorConstructorTest, Copy) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2(it1);
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(*it1, addr);
    EXPECT_EQ(*it2, addr);
}

TEST(Ipv4AddressRangeIteratorConstructorTest, Move) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2(std::move(it1));
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(*it1, addr);
    EXPECT_EQ(*it2, addr);
}

TEST(Ipv4AddressRangeIteratorConstructorTest, Uint32) {
    net::ip::Ipv4AddressRangeIterator it(0x01020304);
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(*it, addr);
}

TEST(Ipv4AddressRangeIteratorOperatorTest, CopyAssignment) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2;
    it2 = it1;
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(*it1, addr);
    EXPECT_EQ(*it2, addr);
}

TEST(Ipv4AddressRangeIteratorOperatorTest, MoveAssignment) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2;
    it2 = std::move(it1);
    net::ip::Ipv4Address addr(0x01020304);
    EXPECT_EQ(*it1, addr);
    EXPECT_EQ(*it2, addr);
}

TEST(Ipv4AddressRangeIteratorOperatorTest, PreIncrement) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4Address addr(0x01020305);
    net::ip::Ipv4AddressRangeIterator it2 = ++it1;
    EXPECT_EQ(*it1, addr);
    EXPECT_EQ(*it2, addr);
}

TEST(Ipv4AddressRangeIteratorOperatorTest, PostIncrement) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4Address addr1(0x01020305);
    net::ip::Ipv4Address addr2(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2 = it1++;
    EXPECT_EQ(*it1, addr1);
    EXPECT_EQ(*it2, addr2);
}

TEST(Ipv4AddressRangeIteratorOperatorTest, Equality) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2(0x01020304);
    EXPECT_EQ(it1, it2);
}


TEST(Ipv4AddressRangeIteratorOperatorTest, Inequality) {
    net::ip::Ipv4AddressRangeIterator it1(0x01020304);
    net::ip::Ipv4AddressRangeIterator it2(0x01020302);
    EXPECT_NE(it1, it2);
}
