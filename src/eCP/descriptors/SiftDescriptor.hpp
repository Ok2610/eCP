#include "../IDescriptor.h"

namespace ecp {
    class SiftDescriptor : public IDescriptor<vector<int>> {

        SiftDescriptor(vector<int> desc, int n_feat) {
            n_features = n_feat;
            descriptor = desc;
        }

        ~SiftDescriptor() {
            delete[] _descriptor;
        }

        vector<int> get_descriptor() override {
            return _descriptor;
        }
    }
}