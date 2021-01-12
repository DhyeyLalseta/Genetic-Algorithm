FROM zouzias/boost
RUN apt-get update
RUN apt-get -y install make gdb
COPY . /ga
WORKDIR /ga