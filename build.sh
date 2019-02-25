mkdir -p ./build
pushd build
cmake .. -DBOOST_ROOT=/opt/boost -GNinja
ninja
popd