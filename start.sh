#!/bin/bash 

imageName="minishell:dev"
if [[ "$(docker images -q $imageName)" == "" ]]
then
    echo "Building $imageName"
    docker build -t $imageName .
fi
docker run --rm -it -m 1g -v "$(pwd):/home/minishell" $imageName
