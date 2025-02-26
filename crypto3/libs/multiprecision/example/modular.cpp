//---------------------------------------------------------------------------//
// Copyright (c) 2024 Vasiliy Olekhov <vasiliy.olekhov@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//
// This example demonstrates usage of multiprecision modular arithmetic

#include <iostream>
#include <iomanip>

#include <nil/crypto3/multiprecision/integer.hpp>
#include <nil/crypto3/multiprecision/literals.hpp>

int main() {
    /* modulus must be known at compile time */
    constexpr static const nil::crypto3::multiprecision::big_uint<64> p = 0xffffffff00000001_big_uint64;
    using modular_t = nil::crypto3::multiprecision::montgomery_big_mod<p>;

    modular_t x = 1, y = 1, f;
    int N = 100;

    std::cout << N << " Fibonacci numbers (modulo 0x" << std::hex << p << std::dec << ") :" << std::endl;
    std::cout << std::setw(5) << 0 << ": " << x << std::endl;
    std::cout << std::setw(5) << 1 << ": " << y << std::endl;

    for(size_t i = 2; i < N; ++i) {
        f = x + y;
        std::cout << std::setw(5) << i << ": " << f << std::endl;
        x = y;
        y = f;
    }
    return 0;
}
