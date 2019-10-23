#include <data/crypto/sha512.hpp>
#include <crypto++/sha.h>

namespace data::sha512 {

    digest hash(const bytes_view data) {
        std::array<byte, size> hash;
        CryptoPP::SHA512{}.CalculateDigest(hash.data(),data.begin(),data.size());
        return uint<size>{hash};
    }

}

