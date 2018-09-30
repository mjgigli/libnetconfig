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
#ifndef NET_IP_IPV4ADDRESS_HPP_
#define NET_IP_IPV4ADDRESS_HPP_

#include <stdint.h>

#include <string>

#include "net/ip/ipaddress.hpp"

namespace net {
namespace ip {

class Ipv4Address : public IpAddress {
 public:
    Ipv4Address();
    Ipv4Address(const Ipv4Address& addr);
    Ipv4Address(Ipv4Address&& addr);
    explicit Ipv4Address(uint32_t addr);
    explicit Ipv4Address(const std::string& addr);

    virtual ~Ipv4Address();

    Ipv4Address& operator=(const Ipv4Address& addr);
    Ipv4Address& operator=(Ipv4Address&& addr);
    Ipv4Address operator&(const Ipv4Address& addr) const;
    Ipv4Address operator|(const Ipv4Address& addr) const;
    Ipv4Address& operator++();
    Ipv4Address operator++(int);
    Ipv4Address& operator--();
    Ipv4Address operator--(int);

    uint32_t to_uint32() const;
    Family family() const override;
    std::string to_string() const override;
    bool is_unspecified() const override;
    bool is_broadcast() const override;
    bool is_loopback() const override;
    bool is_multicast() const override;
    bool is_unicast() const override;

    int Compare(const IpAddress& rhs) const override;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_IPV4ADDRESS_HPP_
