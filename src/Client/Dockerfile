FROM ubuntu:latest
RUN apt update && apt install build-essential
RUN gcc imageproc.c -o  imageproc -lm
COPY . /ImageServer
WORKDIR /ImageServer/
CMD ["./imageproc"]