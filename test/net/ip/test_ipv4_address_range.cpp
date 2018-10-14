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

TEST(Ipv4AddressRangeConstructorTest, AddressArguments) {
    net::ip::Ipv4Address first(0x01020304);
    net::ip::Ipv4Address last(0x0102030a);
    net::ip::Ipv4AddressRange range(first, last);
    EXPECT_EQ(range.first(), first);
    EXPECT_EQ(range.last(), last);
}

TEST(Ipv4AddressRangeConstructorTest, Uint32Arguments) {
    net::ip::Ipv4AddressRange range(0x01020304, 0x0102030a);
    EXPECT_EQ(range.first().to_uint32(), 0x01020304);
    EXPECT_EQ(range.last().to_uint32(), 0x0102030a);
}

TEST(Ipv4AddressRangeConstructorTest, Copy) {
    net::ip::Ipv4AddressRange range1(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRange range2(range1);
    EXPECT_EQ(range1.begin(), range2.begin());
    EXPECT_EQ(range1.end(), range2.end());
}

TEST(Ipv4AddressRangeConstructorTest, Move) {
    net::ip::Ipv4AddressRange range1(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRange range2(std::move(range1));
    net::ip::Ipv4AddressRangeIterator it_empty(0);
    net::ip::Ipv4AddressRangeIterator it_begin(0x01020304);
    net::ip::Ipv4AddressRangeIterator it_end(0x0102030b);
    EXPECT_EQ(range1.begin(), it_empty);
    EXPECT_EQ(range1.end(), ++it_empty);
    EXPECT_EQ(range2.begin(), it_begin);
    EXPECT_EQ(range2.end(), it_end);
}

TEST(Ipv4AddressRangeOperatorTest, CopyAssignment) {
    net::ip::Ipv4AddressRange range1(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRange range2(0x11111111, 0x22222222);
    range2 = range1;
    EXPECT_EQ(range1.begin(), range2.begin());
    EXPECT_EQ(range1.end(), range2.end());
}

TEST(Ipv4AddressRangeOperatorTest, MoveAssignment) {
    net::ip::Ipv4AddressRange range1(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRange range2(0x11111111, 0x22222222);
    range2 = std::move(range1);
    net::ip::Ipv4AddressRangeIterator it_empty(0);
    net::ip::Ipv4AddressRangeIterator it_begin(0x01020304);
    net::ip::Ipv4AddressRangeIterator it_end(0x0102030b);
    EXPECT_EQ(range1.begin(), it_empty);
    EXPECT_EQ(range1.end(), ++it_empty);
    EXPECT_EQ(range2.begin(), it_begin);
    EXPECT_EQ(range2.end(), it_end);
}

TEST(Ipv4AddressRangeAccessorTest, First) {
    net::ip::Ipv4AddressRange range(0x01020304, 0x0102030a);
    net::ip::Ipv4Address first(0x01020304);
    EXPECT_EQ(range.first(), first);
}

TEST(Ipv4AddressRangeAccessorTest, Last) {
    net::ip::Ipv4AddressRange range(0x01020304, 0x0102030a);
    net::ip::Ipv4Address last(0x0102030a);
    EXPECT_EQ(range.last(), last);
}

TEST(Ipv4AddressRangeAccessorTest, Begin) {
    net::ip::Ipv4AddressRange range(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRangeIterator it(0x01020304);
    EXPECT_EQ(range.begin(), it);
}

TEST(Ipv4AddressRangeAccessorTest, End) {
    net::ip::Ipv4AddressRange range(0x01020304, 0x0102030a);
    net::ip::Ipv4AddressRangeIterator it(0x0102030b);
    EXPECT_EQ(range.end(), it);

    net::ip::Ipv4AddressRange range2(0x01020304, 0xffffffff);
    net::ip::Ipv4AddressRangeIterator it2(0x100000000);
    EXPECT_EQ(range2.end(), it2);
}
