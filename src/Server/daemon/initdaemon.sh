#!/bin/sh
../make clean && make
rm daemon
gcc -o daemon daemon.c
sudo cp imageserver.service /lib/systemd/system
sudo systemctl daemon-reload
sudo systemctl start imageserver.service
sudo systemctl enable imageserver.service
sudo systemctl status imageserver.service