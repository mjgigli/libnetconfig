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

Ipv4AddressRangeIterator::Ipv4AddressRangeIterator() :
    curr_(0)
{}

Ipv4AddressRangeIterator::Ipv4AddressRangeIterator(uint64_t start) :
    curr_(start)
{}

Ipv4AddressRangeIterator::reference
Ipv4AddressRangeIterator::operator*() const {
    return Ipv4Address(static_cast<uint32_t>(curr_));
}

Ipv4AddressRangeIterator& Ipv4AddressRangeIterator::operator++() {
    ++curr_;
    return *this;
}

Ipv4AddressRangeIterator Ipv4AddressRangeIterator::operator++(int) {
    Ipv4AddressRangeIterator it(*this);
    ++(*this);
    return it;
}

bool Ipv4AddressRangeIterator::operator==(
        const Ipv4AddressRangeIterator& rhs) const {
    return (**this == *rhs);
}

bool Ipv4AddressRangeIterator::operator!=(
        const Ipv4AddressRangeIterator& rhs) const {
    return !(*this == rhs);
}

}   // namespace ip
}   // namespace net
