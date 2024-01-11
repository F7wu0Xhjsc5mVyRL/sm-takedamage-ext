FROM i386/ubuntu:14.04

RUN apt update
RUN apt install -y git python3 python3-pip gcc gcc-multilib g++ g++-multilib

RUN git clone https://github.com/alliedmodders/ambuild /opt/ambuild
RUN python3 -m pip install /opt/ambuild

WORKDIR /mnt/project

ENTRYPOINT [ "bash", "build.sh" ]
