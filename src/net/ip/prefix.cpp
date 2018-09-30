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

#include "net/ip/prefix.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>

namespace net {
namespace ip {

template <int size>
static void set_bits(std::bitset<size> *bitset, int n) {
    for (int i = 0; i < n; i++) {
        bitset->set(i);
    }
}

Prefix::Prefix(int length) {
    set_bits<SIZE>(&prefix_, length);
}

bool Prefix::operator==(const Prefix& rhs) const {
    return prefix_ == rhs.prefix_;
}

bool Prefix::operator!=(const Prefix& rhs) const {
    return !(*this == rhs);
}

int Prefix::length() const {
    return prefix_.count();
}

std::string Prefix::to_string_ipv4() const {
    struct in_addr ia = {htonl(to_uint32())};
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ia, buf, INET_ADDRSTRLEN);
    return std::string(buf);
}

uint32_t Prefix::to_uint32() const {
    uint32_t tmp = 0;
    std::size_t count;
    if (prefix_.count() >= 32) {
        tmp = 0xffffffff;
        count = 32;
    } else {
        tmp = static_cast<uint32_t>(prefix_.to_ulong());
        count = prefix_.count();
    }

    // Reverse the bits, since subnet masks always set bits starting from the
    // left, but std::bitset sets bits from the right.
    return static_cast<uint32_t>(tmp << (32 - count));
}

}   // namespace ip
}   // namespace net
