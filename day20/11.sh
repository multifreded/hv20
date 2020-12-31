/bin/sh -c 

cp /tmp/t/bunnies12.jpg bunnies12.jpg && \
steghide embed -e loki97 ofb -z 9 -p "bunnies12.jpg\\" -ef /tmp/t/hidden.png -p "\\SecretPassword" -N -cf "bunnies12.jpg" -ef "/tmp/t/hidden.png" && \
mkdir /home/bread/flimflam && \scp 
xxd -p bunnies12.jpg > flimflam/snoot.hex && \
rm -rf bunnies12.jpg && 
split -l 400 /home/bread/flimflam/snoot.hex /home/bread/flimflam/flom && \
rm -rf /home/bread/flimflam/snoot.hex &&
chmod 0000 /home/bread/flimflam && 
apk del steghide xxd # buildkit
