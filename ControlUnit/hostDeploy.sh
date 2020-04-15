#!/bin/bash
cp -f -a website_files/index.html /var/www/html/edbike/
cp -f -a website_files/myStyle.css /var/www/html/edbike/
cp -f -a website_files/EDBike.js /var/www/html/edbike
cp -f -a website_files/img/. /var/www/html/edbike/img/
cp -f -a website_files/javascript_websockets_host/uWS.js /var/www/html/edbike/
echo "copied /website folder  to /var/www/html/edbike/"
make TARGET=host MODE=release
echo "compiled for HOST"
killall main
echo "main killed"
./bin/host/release/main&
echo "main is running"
