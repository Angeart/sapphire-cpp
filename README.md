# <img src="./assets/logo.svg" width="50%">

 [![CircleCI](https://circleci.com/gh/Angeart/sapphire-cpp/tree/master.svg?style=shield)](https://circleci.com/gh/Angeart/sapphire-cpp/tree/master)
![GitHub issues](https://img.shields.io/github/issues/Angeart/sapphire-cpp.svg)
[![Waffle.io - Columns and their card count](https://badge.waffle.io/Angeart/sapphire-cpp.svg?columns=all)](https://waffle.io/Angeart/sapphire-cpp)
![GitHub](https://img.shields.io/github/license/Angeart/sapphire-cpp.svg)

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
