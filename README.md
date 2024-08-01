# Botris-cpp-template
Template for setting up ixwebsocket and cmake for easily making your botris bot!

# dependencies
    - OpenSSL (libssl-dev on debian!)
 
# Downloading and Building
### Cloning
```git clone <url> --recurse-submodules```

If you forgot to install the submodule (IXWebSocket), do this in the git repo root dir:
```git submodule update --init --recursive```

### Building

```
mkdir build
cd build
cmake ..
make -j4
```
And you're done!
