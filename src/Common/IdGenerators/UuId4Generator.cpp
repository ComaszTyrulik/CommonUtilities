#include "Common/IdGenerators/UuId4Generator.h"
#include "Common/Utils/Hasher.h"

#include <uuid.h>
#include <random>

namespace CT_COMMON_NAMESPACE
{
    Id UuId4Generator::Generate() const
    {
        std::random_device randomDevice;
        auto seed = std::array<int, std::mt19937::state_size>{};

        std::generate(std::begin(seed), std::end(seed), std::ref(randomDevice));
        std::seed_seq seedSequence(std::begin(seed), std::end(seed));
        std::mt19937 generatorEngine(seedSequence);
        uuids::uuid_random_generator uuidGenerator{generatorEngine};

        const auto id = uuidGenerator();
        return Hasher::Hash(id.as_bytes());
    }
} // namespace CT_COMMON_NAMESPACE
