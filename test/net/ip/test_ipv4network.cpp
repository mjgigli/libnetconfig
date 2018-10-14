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

#include "net/ip/ipv4.hpp"

TEST(Ipv4NetworkConstructorTest, Default) {
    net::ip::Ipv4Network network;
    EXPECT_EQ(network.address().to_uint32(), 0);
    EXPECT_EQ(network.prefix().length(), 0);
}

TEST(Ipv4NetworkConstructorTest, Integer) {
    net::ip::Ipv4Network network(0x01020304, 16);
    EXPECT_EQ(network.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network.prefix().length(), 16);
}

TEST(Ipv4NetworkConstructorTest, AddressPrefix) {
    net::ip::Ipv4Address addr(0x01020304);
    net::ip::Prefix prefix(16);
    net::ip::Ipv4Network network(addr, prefix);
    EXPECT_EQ(network.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network.prefix().length(), 16);
}

TEST(Ipv4NetworkConstructorTest, Copy) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2(network1);
    EXPECT_EQ(network1.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network1.prefix().length(), 16);
    EXPECT_EQ(network2.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network2.prefix().length(), 16);
}

TEST(Ipv4NetworkConstructorTest, Move) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2(std::move(network1));
    EXPECT_EQ(network1.address().to_uint32(), 0);
    EXPECT_EQ(network1.prefix().length(), 16);
    EXPECT_EQ(network2.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network2.prefix().length(), 16);
}

TEST(Ipv4NetworkOperatorTest, CopyAssignment) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2;
    network2 = network1;
    EXPECT_EQ(network1.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network1.prefix().length(), 16);
    EXPECT_EQ(network2.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network2.prefix().length(), 16);
}

TEST(Ipv4NetworkOperatorTest, MoveAssignment) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2;
    network2 = std::move(network1);
    EXPECT_EQ(network1.address().to_uint32(), 0);
    EXPECT_EQ(network1.prefix().length(), 16);
    EXPECT_EQ(network2.address().to_uint32(), 0x01020304);
    EXPECT_EQ(network2.prefix().length(), 16);
}

TEST(Ipv4NetworkOperatorTest, Equality) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2(0x01020405, 16);
    net::ip::Ipv4Network network3(0x01020304, 17);
    net::ip::Ipv4Network network4(0x01030304, 16);
    EXPECT_TRUE(network1 == network2);
    EXPECT_FALSE(network1 == network3);
    EXPECT_FALSE(network1 == network4);
}

TEST(Ipv4NetworkOperatorTest, Inequality) {
    net::ip::Ipv4Network network1(0x01020304, 16);
    net::ip::Ipv4Network network2(0x01030304, 16);
    net::ip::Ipv4Network network3(0x01030304, 17);
    net::ip::Ipv4Network network4(0x01020506, 16);
    EXPECT_TRUE(network1 != network2);
    EXPECT_TRUE(network1 != network3);
    EXPECT_TRUE(network2 != network3);
    EXPECT_FALSE(network1 != network4);
}

TEST(Ipv4NetworkAccessorsTest, Netmask) {
    uint32_t mask = 0x00000000;
    for (int i = 0; i <= 32; i++) {
        net::ip::Ipv4Network network(0x01020304, i);
        EXPECT_EQ(network.netmask(), net::ip::Ipv4Address(mask));
        mask |= (0x80000000 >> i);
    }
}

TEST(Ipv4NetworkAccessorsTest, NetworkAddress) {
    uint32_t addr = 0x01020304;
    uint32_t mask = 0x00000000;
    for (int i = 0; i <= 32; i++) {
        net::ip::Ipv4Network network(addr, i);
        EXPECT_EQ(network.network(), net::ip::Ipv4Address(addr & mask));
        mask |= (0x80000000 >> i);
    }
}

TEST(Ipv4NetworkAccessorsTest, BroadcastAddress) {
    uint32_t mask = 0xffffffff;
    uint32_t addr = 0x01020304;
    for (int i = 0; i <= 32; i++) {
        net::ip::Ipv4Network network(addr, i);
        EXPECT_EQ(network.broadcast(), net::ip::Ipv4Address(addr | mask));
        mask >>= 1;
    }
}

TEST(Ipv4NetworkAccessorsTest, Hosts) {
    net::ip::Ipv4Address addr(0x01020304);
    for (int i = 0; i <= 32; i++) {
        net::ip::Prefix prefix(i);
        net::ip::Ipv4Network network(addr, prefix);
        net::ip::Ipv4AddressRangeIterator it_begin;
        net::ip::Ipv4AddressRangeIterator it_end;
        if (i == 31) {
            it_begin = net::ip::Ipv4AddressRangeIterator(
                    network.network().to_uint32());
            it_end = net::ip::Ipv4AddressRangeIterator(
                    network.broadcast().to_uint32() + 1);
        } else if (i == 32) {
            it_begin = net::ip::Ipv4AddressRangeIterator(addr.to_uint32());
            it_end = net::ip::Ipv4AddressRangeIterator(addr.to_uint32() + 1);
        } else {
            it_begin = net::ip::Ipv4AddressRangeIterator(
                    network.network().to_uint32() + 1);
            it_end = net::ip::Ipv4AddressRangeIterator(
                    network.broadcast().to_uint32());
        }

        net::ip::Ipv4AddressRange hosts = network.hosts();
        EXPECT_EQ(hosts.begin(), it_begin);
        EXPECT_EQ(hosts.end(), it_end);
    }
}
