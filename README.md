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

#### Create a dockerfile 
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
- add some more tools to our image like allocating and freeing memory
```
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
  ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
```

#### Running the dockerfile 
```
docker build -t cppbox .
```
```
docker run -ti cppbox:latest bash
```
- checking if install succeded 
```
find /usr -name libboost*.*
```
- for exit the container 
```
exit
```

#### TROUBLESHOOTING 
- running the dockerfile will give a WARNING 'delaying package configuration, since apt-utils is not installed'
- bug that won't stop the installation
```
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
```

- Security warning appearing when building a Docker image from Windows against a non-Windows Docker host
- Warning was added, because the Windows filesystem does not have an option to mark a file as 'executable'
- The files will be 'executable' by default 
