#ifndef MINIGIN_CRYPTO_HPP
#define MINIGIN_CRYPTO_HPP

#include <cstdint>
#include <cstddef>

namespace dae {
    // TMP functions to calculate the sdbm hash of a string
    // Graciously provided by Alex's programming 4 slides
    template<int length>
    struct sdbm_hash_tmp {
        consteval static uint32_t _calculate(const char *const text, uint32_t &value) {
            const uint32_t character = sdbm_hash_tmp<length - 1>::_calculate(text, value);
            value = character + (value << 6) + (value << 16) - value;
            return text[length - 1];
        }

        consteval static uint32_t calculate(const char *const text) {
            uint32_t value = 0;
            const auto character = _calculate(text, value);
            return character + (value << 6) + (value << 16) - value;
        }
    };

    template<>
    struct sdbm_hash_tmp<1> {
        consteval static int _calculate(const char *const text, uint32_t &) { return text[0]; }
    };

    template<std::size_t N>
    consteval uint32_t sdbm_hash(const char (&text)[N]) {
        return sdbm_hash_tmp<N - 1>::calculate(text);
    }
}

#endif //MINIGIN_CRYPTO_HPP
