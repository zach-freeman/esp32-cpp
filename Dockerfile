FROM ubuntu:18.04

RUN mkdir -p /home/esp && \
    useradd -d /home/esp esp && \
    chown esp:esp /home/esp && \
    usermod -aG dialout esp

WORKDIR /home/esp

RUN apt-get update && \
    apt-get install -y gcc git curl wget make libncurses-dev flex bison gperf python python-serial vim \
    python-pip && python -m pip install --upgrade pip


USER esp

RUN curl -o esp.tar.gz https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar.gz && \
    tar -xzf esp.tar.gz && \
    rm esp.tar.gz

RUN git clone --recursive --depth 1 https://github.com/espressif/esp-idf.git

ENV PATH="${PATH}:/home/esp/xtensa-esp32-elf/bin" \
    IDF_PATH="/home/esp/esp-idf"

RUN pip install --user -r /home/esp/esp-idf/requirements.txt

CMD bash