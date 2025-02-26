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

#ifndef CRYPTO3_ALGEBRA_CURVES_PALLAS_PARAMS_HPP
#define CRYPTO3_ALGEBRA_CURVES_PALLAS_PARAMS_HPP

#include <nil/crypto3/algebra/curves/forms.hpp>
#include <nil/crypto3/algebra/curves/detail/pallas/types.hpp>



namespace nil {
    namespace crypto3 {
        namespace algebra {
            namespace curves {
                namespace detail {

                    /**
                     * @brief https://zips.z.cash/protocol/protocol.pdf#pallasandvesta
                     */
                    template<>
                    struct pallas_params<forms::short_weierstrass> {
                        using base_field_type = typename pallas_types::base_field_type;
                        using scalar_field_type = typename pallas_types::scalar_field_type;
                        /* Short Weierstrass curve: y^2 = x^3 + a*x +b */
                        constexpr static typename pallas_types::base_field_type::value_type a = 0u;
                        constexpr static typename pallas_types::base_field_type::value_type b = 5u;
                    };

                    template<>
                    struct pallas_g1_params<forms::short_weierstrass>
                        : public pallas_params<forms::short_weierstrass> {
                        using field_type = typename pallas_types::g1_field_type;

                        template<typename Coordinates>
                        using group_type = pallas_types::g1_type<forms::short_weierstrass, Coordinates>;

#ifdef STANDARD_EC_INF_POINTS_ENABLED
                        constexpr static std::array<typename field_type::value_type,2> zero_fill = {
                            field_type::value_type::zero(), field_type::value_type::one()};
#else
                        constexpr static std::array<typename field_type::value_type,2> zero_fill = {
                            field_type::value_type::zero(), field_type::value_type::zero()};
#endif

                        // Generator: (-1, 2)
                        constexpr static std::array<typename field_type::value_type, 2> one_fill = {
                            field_type::modulus - 1,
                            typename field_type::value_type(2u)};
                    };

                    constexpr typename pallas_types::base_field_type::value_type pallas_params<forms::short_weierstrass>::a;
                    constexpr typename pallas_types::base_field_type::value_type pallas_params<forms::short_weierstrass>::b;

                    constexpr std::array<typename pallas_g1_params<forms::short_weierstrass>::field_type::value_type, 2>
                        pallas_g1_params<forms::short_weierstrass>::zero_fill;
                    constexpr std::array<typename pallas_g1_params<forms::short_weierstrass>::field_type::value_type, 2>
                        pallas_g1_params<forms::short_weierstrass>::one_fill;

                }    // namespace detail
            }        // namespace curves
        }            // namespace algebra
    }                // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_ALGEBRA_CURVES_PALLAS_PARAMS_HPP
