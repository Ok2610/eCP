
#include "../IContainer.h"

namespace ecp {
    class L2FloatVecContainer : public IContainer<float, FloatVecDescriptor> {
        L2FloatVecContainer() {
            _default_value = std::numeric_limits<float>::max();
            _b = 1;
            set_k(10);
        }

        L2FloatVecContainer(int k) {
            _default_value = std::numeric_limits<float>::max();
            _b = 1;
            set_k(k);
        }

        L2FloatVecContainer(FloatVecDescriptor& qpoint, int k, int b) {
            _query_point = qpoint;
            _b = b;
            set_k(k);
        }

        inline boolean halting_check(float distance) override {
            return distance < _halting_distance;
        }

        void sort_neighbors() override {
            sort_neighbors_internal(false);
        }

        float distance_with_halt() override {
            float dist = 0.0;
            for (int i = 0; i < point.descriptor.size(); ++i) {
                float a = point.descriptor[i] - _query_point.descriptor[i];
                dist += a * a;
                if (dist > _halting_distance) {
                    dist = _default_value;
                    return dist;
                }
            }
            return dist;
        };

        float distance_with_halt_unrolled() override {
            float dist = 0.0;
            int i = 0;
            while (i < point.descriptor.size()) {
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];

                if (dist > _halting_distance) {
                    dist = _default_value;
                    return dist;
                }
            }
            return dist;
        };

        float distance_full_unrolled() override {
            float dist = 0.0;
            int i = 0;
            while (i < point.descriptor.size()) {
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
                dist += point.descriptor[i] - _query_point[i]
                        * point.descriptor[i] - _query_point[i++];
            }
            return dist;
        };

    }
}