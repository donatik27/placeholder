//---------------------------------------------------------------------------//
// Copyright (c) 2020-2021 Mikhail Komarov <nemo@nil.foundation>
// Copyright (c) 2020-2021 Ilias Khairullin <ilias@nil.foundation>
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

#ifndef CRYPTO3_HASH_HASH_TO_CURVE_HPP
#define CRYPTO3_HASH_HASH_TO_CURVE_HPP

#include <nil/crypto3/hash/detail/h2c/h2c_suites.hpp>
#include <nil/crypto3/hash/detail/h2c/h2c_m2c.hpp>
#include <nil/crypto3/hash/detail/h2c/h2c_expand.hpp>

#include <type_traits>
#include <climits>

namespace nil {
    namespace crypto3 {
        namespace hashes {

            template<typename GroupType>
            struct ep_map {
                typedef h2c_suite<GroupType> suite_type;

                typedef typename suite_type::group_value_type group_value_type;
                typedef typename suite_type::field_value_type field_value_type;
                typedef typename suite_type::modular_type modular_type;

                typedef typename suite_type::hash_type hash_type;

                constexpr static std::size_t m = suite_type::m;
                constexpr static std::size_t L = suite_type::L;
                constexpr static std::size_t k = suite_type::k;

                // Sometimes hash is 512 bits, while the group element is 256 or 381 bits.
                // In these cases we take the number module the modulus of the group.
                typedef nil::crypto3::multiprecision::big_uint<L * CHAR_BIT> big_uint_of_hash_size;

                typedef expand_message_xmd<k, hash_type> expand_message_ro;
                // typedef expand_message_xof<k, hash_type> expand_message_nu;

                static_assert(m == 1, "underlying field has wrong extension");

                template<typename InputType, typename DstType,
                            typename = typename std::enable_if<
                                std::is_same<std::uint8_t, typename InputType::value_type>::value &&
                                std::is_same<std::uint8_t, typename DstType::value_type>::value>::type>
                static inline group_value_type hash_to_curve(const InputType &msg, const DstType &dst) {
                    auto u = hash_to_field<2, expand_message_ro>(msg, dst);
                    group_value_type Q0 = map_to_curve<GroupType>::process(u[0]);
                    group_value_type Q1 = map_to_curve<GroupType>::process(u[1]);
                    Q0 += Q1;
                    clear_cofactor(Q0);
                    return Q0;
                }

                // template<typename InputType, typename = typename std::enable_if<std::is_same<
                //                                  std::uint8_t, typename InputType::value_type>::value>::type>
                // static inline group_value_type encode_to_curve(const InputType &msg) {
                //     auto u = hash_to_field<1>(msg);
                //     group_value_type Q = map_to_curve(u[0]);
                //     return clear_cofactor(Q);
                // }

                // private:
                template<std::size_t N, typename expand_message_type, typename InputType, typename DstType,
                            typename = typename std::enable_if<
                                std::is_same<std::uint8_t, typename InputType::value_type>::value &&
                                std::is_same<std::uint8_t, typename DstType::value_type>::value>::type>
                static inline std::array<field_value_type, N> hash_to_field(const InputType &msg,
                                                                            const DstType &dst) {
                    std::array<std::uint8_t, N * m * L> uniform_bytes {0};
                    expand_message_type::process(N * m * L, msg, dst, uniform_bytes);

                    big_uint_of_hash_size e;
                    std::array<modular_type, m> coordinates;
                    std::array<field_value_type, N> result;
                    for (std::size_t i = 0; i < N; i++) {
                        for (std::size_t j = 0; j < m; j++) {
                            auto elm_offset = L * (j + i * m);
                            e.import_bits(uniform_bytes.begin() + elm_offset,
                                          uniform_bytes.begin() + elm_offset + L);

                            // Sometimes hash is 512 bits, while the group element is 256
                            // or 381 bits. In these cases we take the number module the
                            // modulus of the group.
                            coordinates[j] = modular_type(e);
                        }
                        result[i] = field_value_type(coordinates[0]);
                    }

                    return result;
                }

                static inline void clear_cofactor(group_value_type &R) {
                    scalar_mul_inplace(R, suite_type::h_eff);
                }
            };
        }    // namespace hashes
    }    // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_HASH_HASH_TO_CURVE_HPP
