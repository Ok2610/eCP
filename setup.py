import os
from pathlib import Path
from setuptools import Extension, setup

os.environ['CC'] = 'g++'

# Paths from environment variables
inlcude_paths = [
    str(Path(os.environ['PYTHON_INCLUDE'])),
    str(Path(os.environ['HDF5_INCLUDE'])), 
    str(Path(os.environ['OPENCV_INCLUDE'])) 
]
library_paths = [
    str(Path(os.environ['PYTHON_LIBS'])),
    str(Path(os.environ['HDF5_LIBS'])),
    str(Path(os.environ['OPENCV_LIBS']))
]

# Libraries
libraries = ['python3.10', 'hdf5_serial', 'hdf5_serial_hl']



compile_args = ['-O3', '-Wall', '-std=c++20']

sources = [
    str(Path('src/eCP/PyInterface.cpp')),
    str(Path('src/eCP/ECPCluster.cpp')),
    str(Path('src/eCP/Tree.cpp')),
    str(Path('src/eCP/I_DataLoader.hpp')),
    str(Path('src/eCP/CLIPDescriptor.cpp')),
    str(Path('src/eCP/Neighborhood.cpp')),
    str(Path('src/eCP/QueryOptimisationPolicies.cpp')),
]

ecp = Extension(
    'ecp',
    sources=sources,
    include_dirs=inlcude_paths,
    library_dirs=library_paths,
    libraries=libraries,
    extra_compile_args=compile_args,
    language='c++'
)


setup(
    ext_modules=[ecp]
)