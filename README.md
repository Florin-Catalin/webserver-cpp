# WAPICPP

### Motivation
cpp has the same features of the other languages but it compiles to machine code making it faster ( when started up or when executing ) 
### Setup
----------------------------
#### Docker 
creates an image containing all the tools installed correctly and use it for both development and production

#### Atom 
as text editor support bash

#### Deploying the container to Heroku
- install Heroku cli 64 (Docker does not support 32 bits )
```bash
heroku --version
```
  1. "Containerize" the app
  1. Heroku login.
  1. Create a Heroku app.
  1. Push the container and release it
  1. Test in the browser

- first need to persist the volume to the docker image ( volumes are ephemeral things and not part of the docker image )
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

#### Creating a Volume 
- work on host machine, build&run on the container 
- volume is directory shared by the host machine and one or more docker containers  
- -v create a volume option
- \<host directory> the directory on the host machine 
- \<container directory> the directory on the docker container 
- \<image> the name of the image to run 
  
```
docker run -v <host>:<container> -ti <image> bash
```
---------------
My user is KJ so it will be 
- the flag -ti puts docker in terminal interactive mode 
- cppbox:lates is the local version of the cppbox image 
- bash puts it in the container's bash shell
```
docker run -v C:/Users/KJ/Desktop/cppweb:/usr/src/cppweb -ti cppbox:latest bash
```

To check if volume was created correctly, create a file on the host machine version of the box
```
cd /usr/src/cppweb
touch MY_FILE.txt
```
-----------------------
#### Building Crow
- header only, crow_all.h
```
mkdir build
cd build
cmake ..
```

- each docker container is by default isolated, none of its' ports are open, so accessing localhost:18080 won't work

#### Opening a port
- -p opens a port-the number to the left of the colon is the host machine's port number; the number to the right is the container's port number
- -e creates an environment variable
```
docker run -v <host>:<container> -p <host port>:<container port> -e PORT=8081 <image> <app to run>
```
---------------
In my case is 
```
docker run -v C:\Users\KJ\Desktop\cppweb:/usr/src/cppweb -p 8080:8080 -e PORT=8080 cppbox:latest /usr/src/cppweb/hello_crow/build/hello_crow
```
- /usr/src/cppweb/hello_crow/build/hello_crow is the absolute path to the executable 
![Preview](https://github.com/Florin-Catalin/WAPICPP/blob/master/readme/preview1.PNG)


#### TROUBLESHOOTING 
Problems I encounter

-----------------------------
- running the dockerfile will give a WARNING 'delaying package configuration, since apt-utils is not installed'
- bug that won't stop the installation
```
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
```

- Security warning appearing when building a Docker image from Windows against a non-Windows Docker host
- Warning was added, because the Windows filesystem does not have an option to mark a file as 'executable'
- The files will be 'executable' by default 
-----------------------------------

- when running 'make' command to build crow might give 
```
undefined reference to `boost::system::system_category()
```
One solution is to add 'add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)' to CMakeLists.txt 
or define "BOOST_ERROR_CODE_HEADER_ONLY"

--------------------------
- when running 'make' command gives 'pthread_create - not found ' which is a well-known CMake bug
--------------------------
- receive 'Text file busy' when trying to run 'make' command in 'build' directory when trying to modify an executable while it is executing 

