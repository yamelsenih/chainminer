#!/bin/bash

dest=/var/www/miners
cd $dest
rm *.dat ?.conf ??.conf ???.conf *.stat.txt *.putstat.txt

for i in {50..69} {145..199}
do
        if ping -W 1 -c 1 192.168.0.$i &> /dev/null
        then
          scp -o ConnectTimeout=3 -o BatchMode=yes 192.168.0.$i:/run/shm/.stat.log /var/www/miners/$i.stat.txt &
          scp -o ConnectTimeout=3 -o BatchMode=yes 192.168.0.$i:/run/shm/stat.dat /var/www/miners/$i.dat &
          scp -o ConnectTimeout=3 -o BatchMode=yes 192.168.0.$i:/run/shm/.putstat.log /var/www/miners/$i.putstat.txt &
        else
          echo 192.168.0.$i is not up
        fi
done

for job in `jobs -p`
do
echo $job
    wait $job
done

process_miners .dat

