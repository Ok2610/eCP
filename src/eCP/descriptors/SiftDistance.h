#include "../IDistance.h"

namespace ecp {
    class CLIPDistanceMIPS : public IDistance<float> {
        float get_default_distance() override {
            return std::numeric_limits<float>::min();
        };

        float distance_with_halt() override;

        float distance_with_halt_unrolled() override;

        float distance_full_unrolled() override;
    }
}