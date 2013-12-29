#!/bin/bash

id=`date +%N`
echo \#define USERAUTH \"`echo -n $id':123' | base64`\" > user_config.h

make

