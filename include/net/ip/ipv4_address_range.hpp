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
#ifndef NET_IP_IPV4_ADDRESS_RANGE_HPP_
#define NET_IP_IPV4_ADDRESS_RANGE_HPP_

#include <iterator>

#include "net/ip/ipv4_address_range_iterator.hpp"
#include "net/ip/ipv4address.hpp"

namespace net {
namespace ip {

class Ipv4AddressRange {
 public:
    using iterator = Ipv4AddressRangeIterator;

    explicit Ipv4AddressRange(const Ipv4Address& first,
                              const Ipv4Address& last);
    explicit Ipv4AddressRange(uint32_t first,
                              uint32_t last);

    Ipv4AddressRange(const Ipv4AddressRange& range) = default;
    Ipv4AddressRange(Ipv4AddressRange&& range) = default;
    ~Ipv4AddressRange() = default;
    Ipv4AddressRange& operator=(const Ipv4AddressRange& rhs) = default;
    Ipv4AddressRange& operator=(Ipv4AddressRange&& rhs) = default;

    const Ipv4Address& first() const;
    const Ipv4Address& last() const;
    iterator begin() const;
    iterator end() const;

 private:
    Ipv4Address first_;
    Ipv4Address last_;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_IPV4_ADDRESS_RANGE_HPP_
