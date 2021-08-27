# clabs

[![Build Status](https://app.travis-ci.com/wolfired/clabs.svg?branch=master)](https://app.travis-ci.com/wolfired/clabs)
[![Main](https://github.com/wolfired/clabs/actions/workflows/main.yml/badge.svg)](https://github.com/wolfired/clabs/actions/workflows/main.yml)
[![codecov](https://codecov.io/gh/wolfired/clabs/branch/master/graph/badge.svg?token=S4GES4NLKW)](https://codecov.io/gh/wolfired/clabs)

a c lab repo

# usage

```bash

# clone
git clone --recurse-submodules git@github.com:wolfired/clabs.git && \
git -C ./doxygen-awesome-css checkout v1.5.0

# build
rm -rf ./build && \
cmake -B ./build && \
cmake --build ./build

# install
rm -rf ./build && \
cmake -DCMAKE_INSTALL_PREFIX=/home/bed -B ./build && \
cmake --build ./build && \
cmake --install ./build

# gen doc
doxygen

# run web server
python -m http.server -b 0.0.0.0 -d ./html 8000

```
