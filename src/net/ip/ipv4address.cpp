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

#include "net/ip/ipv4address.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sstream>
#include <cstring>

namespace net {
namespace ip {

static void uint32_to_bytes(uint8_t *dest, uint32_t src) {
    std::memcpy(dest, &src, 4);
}

static uint32_t bytes_to_uint32(const uint8_t *src) {
    uint32_t dest = 0;
    std::memcpy(&dest, src, 4);
    return dest;
}

Ipv4Address::Ipv4Address()
{}

Ipv4Address::Ipv4Address(const Ipv4Address& addr) :
    IpAddress(addr)
{}

Ipv4Address::Ipv4Address(Ipv4Address&& addr) :
    IpAddress(std::move(addr))
{}

Ipv4Address::Ipv4Address(uint32_t addr) {
    // Convert addr to host byte order, and save to addr array
    uint32_to_bytes(addr_.v4.data(), htonl(addr));
}

Ipv4Address::Ipv4Address(const std::string& addr) {
    // Convert from character string to network address structure, written in
    // network byte order
    struct in_addr ia;
    int ret = inet_pton(AF_INET, addr.c_str(), &ia);
    if (ret != 1) {
        throw std::invalid_argument("Invalid IPv4 address");
    }

    // Save network address in network byte order
    uint32_to_bytes(addr_.v4.data(), ia.s_addr);
}

Ipv4Address::~Ipv4Address()
{}

Ipv4Address& Ipv4Address::operator=(const Ipv4Address& addr) {
    IpAddress::operator=(addr);
    return *this;
}

Ipv4Address& Ipv4Address::operator=(Ipv4Address&& addr) {
    IpAddress::operator=(std::move(addr));
    return *this;
}

Ipv4Address Ipv4Address::operator&(const Ipv4Address& addr) const {
    return Ipv4Address(to_uint32() & addr.to_uint32());
}

Ipv4Address Ipv4Address::operator|(const Ipv4Address& addr) const {
    return Ipv4Address(to_uint32() | addr.to_uint32());
}

Ipv4Address& Ipv4Address::operator++() {
    uint32_to_bytes(addr_.v4.data(), htonl(to_uint32() + 1));
    return *this;
}

Ipv4Address Ipv4Address::operator++(int) {
    Ipv4Address addr(*this);
    uint32_to_bytes(addr_.v4.data(), htonl(to_uint32() + 1));
    return addr;
}

Ipv4Address& Ipv4Address::operator--() {
    uint32_to_bytes(addr_.v4.data(), htonl(to_uint32() - 1));
    return *this;
}

Ipv4Address Ipv4Address::operator--(int) {
    Ipv4Address addr(*this);
    uint32_to_bytes(addr_.v4.data(), htonl(to_uint32() - 1));
    return addr;
}

uint32_t Ipv4Address::to_uint32() const {
    // Convert network byte order address array to host byte order uint32
    uint32_t naddr = bytes_to_uint32(addr_.v4.data());
    return ntohl(naddr);
}

Family Ipv4Address::family() const {
    return Family::IPV4;
}

std::string Ipv4Address::to_string() const {
    struct in_addr ia = {htonl(to_uint32())};
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ia, buf, INET_ADDRSTRLEN);
    return std::string(buf);
}

bool Ipv4Address::is_unspecified() const {
    return to_uint32() == INADDR_ANY;
}

bool Ipv4Address::is_broadcast() const {
    return to_uint32() == INADDR_NONE;
}

bool Ipv4Address::is_loopback() const {
    return (addr_.v4[0] & 0xff) == 0x7f;
}

bool Ipv4Address::is_multicast() const {
    return (addr_.v4[0] & 0xf0) == 0xe0;
}

bool Ipv4Address::is_unicast() const {
    return !is_unspecified() && !is_broadcast() && !is_multicast();
}

int Ipv4Address::Compare(const IpAddress& rhs) const {
    uint32_t raddr = ntohl(bytes_to_uint32(rhs.address().v4.data()));
    if (to_uint32() < raddr) {
        return -1;
    } else if (to_uint32() > raddr) {
        return 1;
    } else {
        return 0;
    }
}

}   // namespace ip
}   // namespace net
