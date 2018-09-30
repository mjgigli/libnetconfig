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
#ifndef NET_IP_PREFIX_HPP_
#define NET_IP_PREFIX_HPP_

#include <bitset>
#include <string>

namespace net {
namespace ip {

class Prefix {
 public:
    Prefix() = default;
    explicit Prefix(int length);

    Prefix(const Prefix& prefix) = default;
    Prefix(Prefix&& prefix) = default;
    ~Prefix() = default;
    Prefix& operator=(const Prefix& prefix) = default;
    Prefix& operator=(Prefix&& prefix) = default;

    bool operator==(const Prefix& rhs) const;
    bool operator!=(const Prefix& rhs) const;

    int length() const;
    std::string to_string_ipv4() const;
    uint32_t to_uint32() const;

 private:
    static const int SIZE = 128;
    std::bitset<SIZE> prefix_;
};

}  // namespace ip
}  // namespace net

#endif  // NET_IP_PREFIX_HPP_
