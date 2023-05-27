FROM mcr.microsoft.com/devcontainers/base:jammy

RUN apt-get update && apt-get -y install git  


# Install C/C++ build tools
RUN apt-get -y install build-essential gdb cmake git


# Install wget
RUN apt-get -y install wget

#Get boost lib
RUN wget -c https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz   &&\
    tar -xvf boost_1_82_0.tar.gz

# Set the default shell to bash instead of sh
ENV SHELL /bin/bash