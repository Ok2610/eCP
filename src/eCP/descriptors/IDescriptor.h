#ifndef I_DESCRIPTOR_H
#define I_DESCRIPTOR_H

namespace ecp {
    template<class T>
    class IDescriptor {
    public:
        virtual T get_descriptor() = 0;

    protected:
        int n_features;
        int id;
        T descriptor;
    }

    extern template class ecp::IDescriptor<std::unique_ptr<float[]>>; // Embeddings
    extern template class ecp::IDescriptor<vector<float>>; // Embeddings
    extern template class ecp::IDescriptor<vector<int>>; // SIFT
    extern template class ecp::IDescriptor<vector<pair<int,float>>>; // R64 / Sparse
}

#endif // I_DESCRIPTOR_H