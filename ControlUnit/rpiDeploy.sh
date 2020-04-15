#!/bin/bash

make TARGET=rpi MODE=release #make for rpi

ssh root@10.9.8.2 killall main #kill any current main

scp bin/rpi/release/main root@10.9.8.2: #transfor new main executable to rpi root directory

### transfer config files to rpi ###
scp rpi_config_files/connman-hotspot.conf root@10.9.8.2:/etc/connman-hotspot.conf
scp rpi_config_files/enable_hotspot.sh root@10.9.8.2:/etc/init.d
scp EDBikeDataBase.txt root@10.9.8.2:

### transfer website files to rpi ###
scp website_files/index.html root@10.9.8.2:/www/pages
scp website_files/myStyle.css root@10.9.8.2:/www/pages
scp website_files/EDBike.js root@10.9.8.2:/www/pages
scp website_files/javascript_websockets_rpi/uWS.js root@10.9.8.2:/www/pages
scp -r website_files/img/ root@10.9.8.2:/www/

### set date to match that of SSH host ###
ssh root@10.9.8.2 date -s @`( date -u +"%s" )`

### set permissions ###
ssh root@10.9.8.2 chmod 777 /home/root/main
ssh root@10.9.8.2 chmod 777 /etc/init.d/enable_hotspot.sh
ssh root@10.9.8.2 chmod 777 /usr/sbin/connman-hotspot


### make sure boot services are enabled ###
ssh root@10.9.8.2 systemctl enable enable_hotspot.service # starts wifi hotspot on boot
ssh root@10.9.8.2 systemctl start enable_hotspot.service # starts wifi hotspot in case this is first boot

### start main ###
ssh root@10.9.8.2 ./main
