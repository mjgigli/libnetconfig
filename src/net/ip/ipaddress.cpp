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

#include "net/ip/ipaddress.hpp"

#include <cstring>

namespace net {
namespace ip {

IpAddress::IpAddress() :
    addr_()
{}

IpAddress::IpAddress(const IpAddress& addr) :
    addr_(addr.addr_)
{}

IpAddress::IpAddress(IpAddress&& addr) :
    addr_(addr.addr_) {
    addr.addr_ = {0};
}

IpAddress::~IpAddress()
{}

IpAddress& IpAddress::operator=(const IpAddress& addr) {
    addr_ = addr.addr_;
    return *this;
}

IpAddress& IpAddress::operator=(IpAddress&& addr) {
    if (this != &addr) {
        addr_ = addr.addr_;
        addr.addr_ = {0};
    }
    return *this;
}

bool IpAddress::operator==(const IpAddress& addr) const {
    return std::memcmp(&addr.addr_, &addr_, sizeof(addr_)) == 0;
}

bool IpAddress::operator!=(const IpAddress& addr) const {
    return !(*this == addr);
}

bool IpAddress::operator<(const IpAddress& addr) const {
    return Compare(addr) < 0;
}

bool IpAddress::operator<=(const IpAddress& addr) const {
    return Compare(addr) <= 0;
}

bool IpAddress::operator>(const IpAddress& addr) const {
    return Compare(addr) > 0;
}

bool IpAddress::operator>=(const IpAddress& addr) const {
    return Compare(addr) >= 0;
}

const Address& IpAddress::address() const {
    return addr_;
}

}   // namespace ip
}   // namespace net
