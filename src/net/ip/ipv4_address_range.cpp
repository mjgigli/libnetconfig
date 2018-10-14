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

#include "net/ip/ipv4_address_range.hpp"

namespace net {
namespace ip {

Ipv4AddressRange::Ipv4AddressRange(const Ipv4Address& first,
                                   const Ipv4Address& last) :
    first_(first),
    last_(last)
{}

Ipv4AddressRange::Ipv4AddressRange(uint32_t first,
                                   uint32_t last) :
    first_(Ipv4Address(first)),
    last_(Ipv4Address(last))
{}

const Ipv4Address& Ipv4AddressRange::first() const {
    return first_;
}

const Ipv4Address& Ipv4AddressRange::last() const {
    return last_;
}

Ipv4AddressRange::iterator Ipv4AddressRange::begin() const {
    return Ipv4AddressRange::iterator(first_.to_uint32());
}

Ipv4AddressRange::iterator Ipv4AddressRange::end() const {
    return Ipv4AddressRange::iterator(last_.to_uint32() + 1);
}

}   // namespace ip
}   // namespace net
