#include <string>
#include <vector>
#include <iostream>
#include "H5Cpp.h"

namespace eCP {

    using std::vector;
    using std::string;

    class I_DataLoader {
        virtual vector<vector<float>> load_data(const string& filename) = 0;
        virtual vector<vector<float>> load_data_batch(const string& filename, int start, int end) = 0;
    }; // class DataLoader


    class HDF5Loader : I_DataLoader {
    public:
        HDF5Loader(string& ds_name) {
            _ds_name = ds_name;
        }

        ~HDF5Loader() {};

        vector<vector<float>> load_data(const string& filename) override {
            vector<vector<float>> data;
            H5::H5File file(filename, H5F_ACC_RDONLY);
            H5::DataSet dataset = file.openDataSet(_ds_name);
            
            H5::DataSpace dataspace = dataset.getSpace();
            hsize_t dims_out[2]; //dims_out[0] Total Vectors, dims_out[1] Vector Size
            int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
            if (ndims != 2) {
                std::cerr << "Invalid dataset shape!" << std::endl;
                return data;
            }

            // Read the full dataset into a buffer
            std::vector<float> buffer(dims_out[0] * dims_out[1]);
            dataset.read(buffer.data(), H5::PredType::NATIVE_FLOAT);

            // Convert the flat buffer into a vector of vectors
            data.reserve(dims_out[0]);
            for (size_t i = 0; i < dims_out[0]; ++i) {
                data.emplace_back(buffer.begin() + i * dims_out[1], buffer.begin() + (i + 1) * dims_out[1]);
            }

            return data;
        } // HDF5Loader::load_data

        vector<std::vector<float>> load_data_batch(const std::string& filename, int start, int end) override {
            vector<std::vector<float>> data;

            H5::H5File file(filename, H5F_ACC_RDONLY);
            H5::DataSet dataset = file.openDataSet(_ds_name);
            
            H5::DataSpace dataspace = dataset.getSpace();
            hsize_t dims_out[2]; //dims_out[0] Total Vectors, dims_out[1] Vector Size
            int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
            if (ndims != 2) {
                std::cerr << "Invalid dataset shape!" << std::endl;
                return data;
            }

            // Check start and end are within dataset bounds
            if (start < 0 || end >= dims_out[0] || start > end) {
                std::cerr << "Invalid start and end indices." << std::endl;
                return data;
            }

            hsize_t range = end - start + 1;
            hsize_t count[2] = {static_cast<hsize_t>(range), dims_out[1]};
            hsize_t offset[2] = {static_cast<hsize_t>(start), 0};
            dataspace.selectHyperslab(H5S_SELECT_SET, count, offset);

            std::vector<float> buffer(range * dims_out[1]);
            dataset.read(buffer.data(), H5::PredType::NATIVE_FLOAT, dataspace);

            data.reserve(range);
            for (size_t i = 0; i < range; ++i) {
                data.emplace_back(buffer.begin() + i * dims_out[1], buffer.begin() + (i + 1) * dims_out[1]);
            }

            return data;
        } // HDF5Loader::load_data_batch

    private:
        string _ds_name;
    }; // class HDF5Loader
} // namespace eCP