mkdir -p ./build
pushd build
cmake .. -DBOOST_ROOT=/opt/boost -GNinja
ninja -t clean preprocess
ninja preprocess
clang++ -w -std=c++17 ./preprocessed.cpp > /dev/null
popd