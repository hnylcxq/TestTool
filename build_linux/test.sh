

surface -s 128 128 

lf dump_0000.bin 0
mode -c 0 -o 1 -src 1280 720 -dst 1280 720



plane -c 0 -p 0 -s 0 -sw 128 128 -dw 256 256  -km 4 -kp 0 8 -kv 0x80bff 0




surface -s 256 256
lf dump_0001.bin  1
plane -c 0 -p 1 -s 1 -sw 256 256 -dw 400 400 -km 4 -kp 4 4 -kv 0x80bff 0 


check 0