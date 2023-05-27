FROM mcr.microsoft.com/devcontainers/base:jammy

RUN apt-get update && apt-get -y install git  


# Install C/C++ build tools
RUN apt-get -y install build-essential gdb cmake git


# Install wget
RUN apt-get -y install wget

# Set the default shell to bash instead of sh
ENV SHELL /bin/bash