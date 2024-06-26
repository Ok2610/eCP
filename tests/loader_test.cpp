#include "../src/eCP/IDataLoader.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main() {
    string filename = "data/test_embeddings_10x8f.h5";
    ecp::HDF5Loader hdf5Loader = ecp::HDF5Loader("embeddings");
    vector<vector<float>> hdf5Data = hdf5Loader.load_data(filename);
    for (const auto& vec : hdf5Data) {
        for (const auto& value : vec) {
            cout << value << " ";
        }
        cout << endl;
    }

    cout << "Only load items 100 to 110:\n";
    vector<float> batch = hdf5Loader.load_data_batch(filename, 100, 110);
    for (const auto& value : batch) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}