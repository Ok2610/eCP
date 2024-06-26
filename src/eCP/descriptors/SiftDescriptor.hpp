#ifndef SIFT_DESCRIPTOR_HPP
#define SIFT_DESCRIPTOR_HPP

#include "../IDescriptor.h"

namespace ecp {
    class SiftDescriptor : public IDescriptor<vector<int>> {

        SiftDescriptor(vector<int> desc, int n_feat) {
            n_features = n_feat;
            descriptor = desc;
        }

        ~SiftDescriptor() {}

        vector<int> get_descriptor() override {
            return descriptor;
        }
    }
}

#endif // SIFT_DESCRIPTOR_HPP