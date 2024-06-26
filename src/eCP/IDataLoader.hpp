#ifndef I_DATA_LOADER_HPP
#define I_DATA_LOADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <hdf5/serial/H5Cpp.h>

namespace ecp {

    using std::vector;
    using std::string;
    using std::unique_ptr;

    class IDataLoader {
        virtual ~IDataLoader() {} // Virtual desctructor
        virtual vector<unique_ptr<float[]>> load_data(const string& filename) = 0;
        virtual vector<unique_ptr<float[]>> load_data_batch(const string& filename, int start, int end) = 0;
        int get_dims() {
            return dims;
        }
    private:
        int dims = 0;    
    }; // class DataLoader


    class HDF5Loader : IDataLoader {
    public:
        HDF5Loader(const string& ds_name) : _ds_name(ds_name) {}

        ~HDF5Loader() = default;

        vector<unique_ptr<float[]>> load_data(const string& filename) override {
            vector<unique_ptr<float[]>> data;

            H5::H5File file(filename, H5F_ACC_RDONLY);
            H5::DataSet dataset = file.openDataSet(_ds_name);
            H5::DataSpace dataspace = dataset.getSpace();
            hsize_t dims_out[2]; // dims_out[0] Total Vectors, dims_out[1] Vector Size

            int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
            if (ndims != 2) {
                dataspace.close();
                dataset.close();
                file.close();
                throw std::invalid_argument("Invalid dataset shape!");
            }
            dims = dims_out[1];

            // Set offset and count for dataset
            hsize_t dataOffset[2] = {0, 0};
            const hsize_t dataCount[2] = {1, dims_out[1]};

            // Define memory space for single vector
            H5::DataSpace memspace(1, dims_out[1]);
            const hsize_t memCount[1] = {dims_out[1]};
            const hsize_t memOffset[1] = {0}; 
            memspace.selectHyperslab(H5S_SELECT_SET, memCount, memOffset);

            // Resize data to hold point vectors
            data.resize(dims_out[0]);

            // Read point vectors into data
            for (hsize_t i = 0; i < dims_out[0]; ++i) {
                dataOffset[0] = i;
                dataspace.selectHyperslab(H5S_SELECT_SET, dataCount, dataOffset);
                data[i] = std::make_unique<float[]>(dims_out[1]);
                dataset.read(data[i].get(), H5::PredType::NATIVE_FLOAT, memspace, dataspace);
            }

            memspace.close();
            dataspace.close();
            dataset.close();
            file.close();

            return std::move(data);
        } // HDF5Loader::load_data

        vector<unique_ptr<float[]>> load_data_batch(const std::string& filename, int start, int end) override {
            vector<unique_ptr<float[]>> data;

            H5::H5File file(filename, H5F_ACC_RDONLY);
            H5::DataSet dataset = file.openDataSet(_ds_name);
            H5::DataSpace dataspace = dataset.getSpace();
            hsize_t dims_out[2]; //dims_out[0] Total Vectors, dims_out[1] Vector Size

            int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
            if (ndims != 2) {
                dataspace.close();
                dataset.close();
                file.close();
                throw std::invalid_argument("Invalid dataset shape!");
            }
            dims = dims_out[1];

            // Check start and end are within dataset bounds
            if (start < 0 || end >= dims_out[0] || start > end) {
                dataspace.close();
                dataset.close();
                file.close();
                throw std::invalid_argument("Invalid dataset shape!");
            }

            // Set range, offset, and count for the dataset
            hsize_t range = end - start + 1;
            const hsize_t dataOffset[2] = {static_cast<hsize_t>(start), 0};
            const hsize_t dataCount[2] = {1, dims_out[1]};

            // Define memory space for single vector
            H5::DataSpace memspace(1, dims_out[1]);
            const hsize_t memCount[1] = {dims_out[1]};
            const hsize_t memOffset[1] = {0}; 
            memspace.selectHyperslab(H5S_SELECT_SET, memCount, memOffset);
 
            // Resize data to hold all point vectors
            data.resize(range);

            // Read point vectors into data
            for (size_t i = 0; i < range; ++i) {
                dataOffset[0] = i;
                dataspace.selectHyperslab(H5S_SELECT_SET, dataCount, dataOffset);
                data[i] = std::make_unique<float[]>(dims_out[1]);
                dataset.read(data[i].get(), H5::PredType::NATIVE_FLOAT, memspace, dataspace);
            }

            memspace.close();
            dataspace.close();
            dataset.close();
            file.close();
            return data;
        } // HDF5Loader::load_data_batch

    private:
        string _ds_name;
    }; // class HDF5Loader
} // namespace eCP

#endif // I_DATA_LOADER_HPP