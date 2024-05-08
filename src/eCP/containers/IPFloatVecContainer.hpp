#include "../IContainer.h"
#include "../descriptors/FloatVecDescriptor.hpp"

namespace ecp {
    class IPFloatVecContainer : public IContainer<float, IDescriptor<vector<float>>> {
        IPFloatVecContainer() {
            _default_value = std::numeric_limits<float>::min();
            _b = 1;
            set_k(10);
        }

        IPFloatVecContainer(int k) {
            _default_value = std::numeric_limits<float>::min();
            _b = 1;
            set_k(k);
        }

        IPFloatVecContainer(FloatVecDescriptor& qpoint, int k, int b) {
            _query_point = qpoint;
            _b = b;
            set_k(k);
        }

        inline boolean halting_check(float distance) override {
            return distance > _halting_distance;
        }

        void sort_neighbors() override {
            sort_neighbors_internal(true);
        }

        float distance_with_halt(FloatVecDescriptor& point) override {
            float dist = 0.0;
            for (int i = 0; i < point.descriptor.size(); ++i) {
                dist += point.descriptor[i] * _query_point[i];
                if (dist < _halting_threshold) {
                    dist = _default_value;
                    return dist;
                }
            }
            return dist;
        };

        float distance_with_halt_unrolled(FloatVecDescriptor& point) override {
            float dist = 0.0;
            int i = 0;
            while (i < point.descriptor.size()) {
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                dist += point.descriptor[i] * _query_point.descriptor[i++];
                if (dist < _halting_threshold) {
                    dist = _default_value;
                    return dist;
                }
            }
            return dist;
        };

        float distance_full_unrolled(FloatVecDescriptor& point) override {
            float dist = 0;
            int i = 0;
            while (i < point.descriptor.size()) {
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
                dist += point.descriptor[i] * _query_point[i++];
            }
            return dist;
        };
    }
}