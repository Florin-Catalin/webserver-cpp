# WAPICPP

### Motivation
cpp has the same features of the other languages but it compiles to machine code making it faster ( when started up or when executing ) 
### Setup
----------------------------
#### Docker 
creates an image containing all the tools installed correctly and use it for both development and production

#### Atom 
as text editor support bash

### Tutorial
```bash
mkdir webcpp
cd cppweb
atom Dockerfile
```
- only use compiler version compatible with the code 
- using latest will give the latest version
```
FROM gcc:7.3.0
```

- update the list of available packages
- -qq flag option used to make the command 'quiet', does not print anything out and assumes 'YES' to all installation prompts
- replace -qq with -y to see outputs
```
RUN apt-get -qq update
```
- install packages that are out-of-date
```
RUN apt-get -qq upgrade 
```
- install cmake cross-platform build-tool to create makefile used to compile and link the code 
```
RUN apt-get -qq install cmake
```

- install boost library because Crow microframework depends on it 
- has many individual library modules
```
RUN apt-get -qq install libboost-all-dev=1.62.0.1
```
- install the essential kit and efficient tcmalloc minimal library
- add some more tools to our image 
```
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
  ln - /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
```
