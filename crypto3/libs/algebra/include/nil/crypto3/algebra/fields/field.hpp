//---------------------------------------------------------------------------//
// Copyright (c) 2020-2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020-2021 Nikita Kaskov <nbering@nil.foundation>
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

#pragma once

#include <nil/crypto3/multiprecision/big_uint.hpp>
#include <nil/crypto3/multiprecision/literals.hpp>

namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace fields {

                /**
                 * Arithmetic in the finite field F[p], for prime p of fixed length.
                 *
                 * This class implements Fp-arithmetic, for a large prime p, using a fixed number
                 * of words. It is optimized for tight memory consumption, so the modulus p is
                 * passed as a template parameter, to avoid per-element overheads.
                 */
                template<std::size_t ModulusBits>
                struct field {

                    constexpr static const std::size_t modulus_bits = ModulusBits;
                    constexpr static const std::size_t number_bits = ModulusBits;

                    typedef nil::crypto3::multiprecision::big_uint<modulus_bits> integral_type;
                };

            }    // namespace fields
        }        // namespace algebra
    }            // namespace crypto3
}    // namespace nil
