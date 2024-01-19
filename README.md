# Simple Webserver in C

Ever since I've heard and witnessed, on the interweb, that it was possible to create a webserver with the grandfather of modern programming languages, the C language, I have set my heart to try and make my very own.<br>
Here in this repository you can find my very own attempt. It is not meant to be used in a real life realistic scenario, it is, mostly, just for reasons of study and practice.

## How To Use
It is simple, not many steps to perform, I prefer to work simple and lightweight.

Fork or manually copy the repository to your machine, or another. And attend to the requirements below.

<i>One must first use a Linux operating system, as of current date, it is hard-coded for it to work only on the Linux system.</i>

## Requirements
- A machine running a Linux system
- The GNU C Compiler

## Build and Run 

Locate the folder where one can find the server .C file and build the program with its makefile.

```bash
  make
```

A few errors of unused variables might come, but you can simply ignore it.
Alternatively, one can also build it manually using the GNU C Compiler.

```bash
  gcc server.c request.c -o server.g2
```

Simple. After that, run the object created by the compiler and the server should prensently start and emerge on port 8080.

```bash
  ./server.g2
```

## Testing
To check whether it is working or not, open your web browser on either localhost:8080 or 127.0.0.1:8080<br>
and see if the web page can be properly received and rendered.


## The Author
- [@GIOdeBrito](https://github.com/GIOdeBrito)


## External Resources

 - [A Guide To Using Network Sockets](https://www.gta.ufrj.br/ensino/eel878/sockets/)
 - [C Library](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm)
 - [Introdução ao Makefile](https://embarcados.com.br/introducao-ao-makefile/)
 - [A Simple Makefile Tutorial](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)


