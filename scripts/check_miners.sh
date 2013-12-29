#!/bin/bash

for i in {146..197} 199 {50..66}
do
        if ping -W 1 -c 1 192.168.0.$i &> /dev/null
        then
	  echo -ne
        else
          echo 192.168.0.$i is not up
        fi
done

for job in `jobs -p`
do
echo $job
    wait $job
done

