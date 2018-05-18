FROM ubuntu:latest
RUN \
    apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y build-essential && \
    apt-get install -y curl htop vim wget tree dnsutils && \
    apt-get install -y gawk sed peco && \
    apt-get install -y python3-pip python3-dev && \
    cd /usr/local/bin && \
    ln -s /usr/bin/python3 python && \
    pip3 install --upgrade pip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ENV HOME /root
WORKDIR /root
CMD ["bash"]
