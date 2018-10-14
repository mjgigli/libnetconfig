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
#ifndef NET_IP_IPV4_ADDRESS_RANGE_ITERATOR_HPP_
#define NET_IP_IPV4_ADDRESS_RANGE_ITERATOR_HPP_

#include <iterator>

#include "net/ip/ipv4address.hpp"

namespace net {
namespace ip {

class Ipv4AddressRangeIterator {
 public:
    // Iterator traits
    using value_type = Ipv4Address;
    using difference_type = std::ptrdiff_t;
    using pointer = Ipv4Address*;
    using reference = Ipv4Address;
    using iterator_category = std::input_iterator_tag;

    Ipv4AddressRangeIterator();
    explicit Ipv4AddressRangeIterator(uint64_t start);

    Ipv4AddressRangeIterator(const Ipv4AddressRangeIterator& it) = default;
    Ipv4AddressRangeIterator(Ipv4AddressRangeIterator&& it) = default;
    ~Ipv4AddressRangeIterator() = default;
    Ipv4AddressRangeIterator& operator=(
            const Ipv4AddressRangeIterator& it) = default;
    Ipv4AddressRangeIterator& operator=(
            Ipv4AddressRangeIterator&& it) = default;

    reference operator*() const;
    Ipv4AddressRangeIterator& operator++();
    Ipv4AddressRangeIterator operator++(int);
    bool operator==(const Ipv4AddressRangeIterator& rhs) const;
    bool operator!=(const Ipv4AddressRangeIterator& rhs) const;

 private:
    uint64_t curr_;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_IPV4_ADDRESS_RANGE_ITERATOR_HPP_
