#ifndef FLOAT_VEC_DESCRIPTOR_HPP
#define FLOAT_VEC_DESCRIPTOR_HPP

#include "../IDescriptor.h"

namespace ecp {
    class FloatVecDescriptor : public IDescriptor<vector<float>> {
        FloatVecDescriptor() {
            n_features = 0;
            descriptor = vector<float>();
        }

        FloatVecDescriptor(vector<float> desc, int n_feat) {
            n_features = n_feat;
            descriptor = desc;
        }

        ~FloatVecDescriptor() {}

        vector<float> get_descriptor() override {
            return descriptor;
        }
    }
}

#endif // FLOAT_VEC_DESCRIPTOR_HPP