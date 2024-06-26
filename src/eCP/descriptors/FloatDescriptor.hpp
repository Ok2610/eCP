#ifndef FLOAT_DESCRIPTOR_HPP
#define FLOAT_DESCRIPTOR_HPP

#include "../IDescriptor.h"

namespace ecp {
    class FloatDescriptor : public IDescriptor<std::unique_ptr<float[]>> {
        FloatDescriptor(int n_feat) : n_features(n_feat) {
            descriptor = std::make_unique<float[]>(n_feat);
        }

        FloatDescriptor(float* desc, int n_feat) : descriptor(desc), n_features(n_feat) {}

        ~FloatDescriptor() = default;

        vector<float> get_descriptor() override {
            return descriptor.get();
        }
    }
}

#endif // FLOAT_DESCRIPTOR_HPP