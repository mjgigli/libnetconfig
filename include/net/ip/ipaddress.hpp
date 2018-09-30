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
#ifndef NET_IP_IPADDRESS_HPP_
#define NET_IP_IPADDRESS_HPP_

#include <stdint.h>

#include <string>
#include <array>

namespace net {
namespace ip {

union Address {
    // IPv4 address in bytes, in network byte order
    std::array<uint8_t, 4> v4;
    // IPv6 address in bytes, in network byte order
    std::array<uint8_t, 16> v6;
};

enum Family {
    IPV4,
    IPV6
};

class IpAddress {
 public:
    // Common comparison operators for all IpAddress objects
    bool operator==(const IpAddress& addr) const;
    bool operator!=(const IpAddress& addr) const;
    bool operator<(const IpAddress& addr) const;
    bool operator<=(const IpAddress& addr) const;
    bool operator>(const IpAddress& addr) const;
    bool operator>=(const IpAddress& addr) const;

    // Accessor functions
    const Address& address() const;
    virtual Family family() const = 0;
    virtual std::string to_string() const = 0;
    virtual bool is_unspecified() const = 0;
    virtual bool is_broadcast() const = 0;
    virtual bool is_loopback() const = 0;
    virtual bool is_multicast() const = 0;
    virtual bool is_unicast() const = 0;

    // Class member functions
    virtual int Compare(const IpAddress& rhs) const = 0;

 protected:
    IpAddress();
    IpAddress(const IpAddress& addr);
    IpAddress(IpAddress&& addr);

    virtual ~IpAddress();

    IpAddress& operator=(const IpAddress& addr);
    IpAddress& operator=(IpAddress&& addr);

    Address addr_;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_IPADDRESS_HPP_
