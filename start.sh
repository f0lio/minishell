#!/bin/bash 

imageName="minishell:dev"
if [[ "$(docker images -q $imageName)" == "" ]]
then
    echo "Building $imageName"
    docker build -t $imageName .
    docker run --rm -it -v "$(pwd):/home/minishell" $imageName
else
    docker run --rm -it -v "$(pwd):/home/minishell" $imageName
fi
