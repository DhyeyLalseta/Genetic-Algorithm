FROM zouzias/boost
RUN apt-get -y install make
COPY . /ga
WORKDIR /ga