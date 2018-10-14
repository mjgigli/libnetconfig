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

#include "net/ip/ipv4network.hpp"

namespace net {
namespace ip {

Ipv4Network::Ipv4Network() :
    addr_(0),
    prefix_(0)
{}

Ipv4Network::Ipv4Network(uint32_t addr, int prefix_length) :
    addr_(addr),
    prefix_(prefix_length)
{}

Ipv4Network::Ipv4Network(const Ipv4Address& addr, const Prefix& prefix) :
    addr_(addr),
    prefix_(prefix)
{}

bool Ipv4Network::operator==(const Ipv4Network& rhs) const {
    return network() == rhs.network() && prefix() == rhs.prefix();
}

bool Ipv4Network::operator!=(const Ipv4Network& rhs) const {
    return !(*this == rhs);
}

Ipv4Address Ipv4Network::address() const {
    return addr_;
}

Prefix Ipv4Network::prefix() const {
    return prefix_;
}

Ipv4Address Ipv4Network::netmask() const {
    return Ipv4Address(prefix_.to_uint32());
}

Ipv4Address Ipv4Network::network() const {
    return Ipv4Address(addr_ & netmask());
}

Ipv4Address Ipv4Network::broadcast() const {
    return network() | Ipv4Address(~(prefix_.to_uint32()));
}

Ipv4AddressRange Ipv4Network::hosts() const {
    if (prefix_.length() == 31) {
        // Include network/broadcast address with prefix = 31
        return Ipv4AddressRange(network(), broadcast());
    } else if (prefix_.length() == 32) {
        // Only 1 possible IP address
        return Ipv4AddressRange(addr_, addr_);
    } else {
        // Valid hosts start after network address, end before broadcast
        // address
        return Ipv4AddressRange(network().to_uint32() + 1,
                                broadcast().to_uint32() - 1);
    }
}

}   // namespace ip
}   // namespace net
