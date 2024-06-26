#include "IDescriptor.h"

using namespace ecp;

template class ecp::IDescriptor<std::unique_ptr<float[]>>; // Embeddings
template class ecp::IDescriptor<vector<float>>; // Embeddings
template class ecp::IDescriptor<vector<int>>; // SIFT
template class ecp::IDescriptor<vector<pair<int,float>>>; // R64 / Sparse