#!/bin/bash
for ip in "$@"
do
        if ping -W 1 -c 1 192.168.0.$ip &> /dev/null
        then
          cat ~/.ssh/id_rsa.pub | ssh -o ConnectTimeout=1 root@192.168.0.$ip "cat >> .ssh/authorized_keys"
        else
          echo 192.168.0.$ip is not up
        fi
done

