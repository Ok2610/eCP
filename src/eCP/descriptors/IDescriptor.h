
namespace ecp {
    template<class T>
    class IDescriptor {
    public:
        int n_features;
        T descriptor;

        virtual T get_descriptor() = 0;
    }
}

template class ecp::IDescriptor<float*>; // Embeddings
template class ecp::IDescriptor<vector<float>>; // Embeddings
template class ecp::IDescriptor<vector<int>>; // SIFT
template class ecp::IDescriptor<vector<pair<int,float>>>; // R64 / Sparse