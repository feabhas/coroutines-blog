# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends clang-format gcc-10 g++-10 python3


RUN sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 50
RUN sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 50
RUN sudo update-alternatives --set gcc /usr/bin/gcc-10
RUN sudo update-alternatives --set g++ /usr/bin/g++-10
