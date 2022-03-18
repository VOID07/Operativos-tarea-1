#!/bin/sh
cd .. && pwd 
make
cd daemon && pwd
gcc -o daemon daemon.c
sudo cp imageserver.service /lib/systemd/system
sudo systemctl daemon-reload
sudo systemctl start imageserver.service
sudo systemctl enable imageserver.service
sudo systemctl status imageserver.service