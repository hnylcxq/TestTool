

surface -s 128 128
mode -c 0 -o 1 -src 1280 720 -dst 1280 720
plane -c 0 -s 0 -sw 128 128 -dw 256 256  -km 4 -kp 0 8 -kv 0x80bff 0
lf dump_0000.bin 0x1000000
