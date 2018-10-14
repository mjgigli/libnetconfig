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
#ifndef NET_IP_IPV4NETWORK_HPP_
#define NET_IP_IPV4NETWORK_HPP_

#include <stdint.h>

#include <string>

#include "net/ip/ipv4address.hpp"
#include "net/ip/prefix.hpp"
#include "net/ip/ipv4_address_range.hpp"

namespace net {
namespace ip {

class Ipv4Network {
 public:
     Ipv4Network();
     Ipv4Network(uint32_t addr, int prefix_length);
     Ipv4Network(const Ipv4Address& addr, const Prefix& prefix);

     Ipv4Network(const Ipv4Network& network) = default;
     Ipv4Network(Ipv4Network&& network) = default;
     ~Ipv4Network() = default;
     Ipv4Network& operator=(const Ipv4Network& rhs) = default;
     Ipv4Network& operator=(Ipv4Network&& rhs) = default;

    bool operator==(const Ipv4Network& rhs) const;
    bool operator!=(const Ipv4Network& rhs) const;

     Ipv4Address address() const;
     Prefix prefix() const;
     Ipv4Address netmask() const;
     Ipv4Address network() const;
     Ipv4Address broadcast() const;
     Ipv4AddressRange hosts() const;

 private:
    Ipv4Address addr_;
    Prefix prefix_;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_IPV4NETWORK_HPP_
