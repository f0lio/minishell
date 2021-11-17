# This image serves as a sandbox for developing/running minishell.
FROM debian:stable
LABEL description="Image for developing minishell project." 
WORKDIR /home/minishell
RUN apt-get update 
RUN apt-get install -y clang
RUN apt-get install -y make
RUN apt-get install -y valgrind
RUN apt-get install -y libreadline-dev
COPY . .
CMD "/bin/bash"
