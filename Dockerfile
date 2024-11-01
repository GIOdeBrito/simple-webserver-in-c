# Use GCC official image
FROM gcc:4.9

COPY ./server ./usr/src/simple-server/server
COPY ./public ./usr/src/simple-server/public

WORKDIR ./usr/src/simple-server/server

# Create objects folder used by the makefile
RUN mkdir objects

RUN make

CMD ["./server.g2"]