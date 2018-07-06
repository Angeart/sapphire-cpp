# <img src="./assets/logo.svg" width="50%">

|||
|---|---|
state | [![CircleCI](https://circleci.com/gh/Angeart/sapphire-cpp/tree/master.svg?style=svg)](https://circleci.com/gh/Angeart/sapphire-cpp/tree/master)

## desc
compiler of sapphire by c++


## development

### require
* cpp standard
    * c++17 (201703) or more
        > recommend g++-8 when you use Mac.
* tools
    * cmake > 3.10
* libraries
    * boost

### build
```bash
mkdir build
cd build
cmake .. -DBOOST_ROOT=<your_boost_root_dir>
```

### test
```bash
make test
```
