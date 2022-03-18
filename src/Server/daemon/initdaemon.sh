#!/bin/sh
cd .. && pwd 
make clean
make
cd daemon && pwd
rm -r writeOnStart
rm -r writeOnStop
gcc -o writeOnStart writeOnStart.c
gcc -o writeOnStop writeOnStop.c
sudo cp imageserver.service /lib/systemd/system
sudo systemctl daemon-reload
sudo systemctl start imageserver.service
sudo systemctl enable imageserver.service
sudo systemctl status imageserver.service