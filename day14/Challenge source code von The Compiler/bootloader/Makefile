loader.img: loader.asm qrdata.asm gifdata.asm hiddendata.asm
	nasm -f bin -o loader.img loader.asm

loader-c: loader.c qrdata.h
	gcc -o loader-c loader.c -Wall -Wextra -Os -g

dump-c: loader-c
	objdump --disassemble=main -Mintel -S --visualize-jumps=extended-color loader-c
	objdump -t loader-c | grep -E '(qr_code|main)$$'

gifdata.asm: gif/gifdata.py
	cd gif && .venv/bin/python3 gifdata.py > ../gifdata.asm

qrdata.asm: encode.py
	python3 encode.py --bits "HV20{54n74'5-m461c-b00t-l04d3r}" > qrdata.asm

hiddendata.asm: encode.py
	python3 encode.py --bits --hidden "HV20{h1dd3n-1n-pl41n-516h7}" "HV20{54n74'5-m461c-b00t-l04d3r}" > hiddendata.asm

qrdata.h: encode.py
	python3 encode.py -c --bits > qrdata.h

boot: loader.img
	qemu-system-x86_64 -drive file=loader.img,format=raw

ls: loader.img
	ls -lh loader.img

dump: loader.img
	objdump -D -b binary -mi386 -Maddr16,data16 loader.img

file: loader.img
	file loader.img

.PHONY: boot ls dump dump-c file
