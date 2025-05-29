# ch32fun_isler
Industry Standard Low Energy Radio (ISLER) RX/TX for ch32fun

## install:
Checkout [ch32fun](https://github.com/cnlohr/ch32fun) on the same level as this repository, and just run `make`.
If you have your copy of `ch32fun` somewhere else you probably already know what to do; change the `include` include
in the `Makefile` to point to that.

## supported MCUs:
This code aim to support all WCH RF enabled microcontrollers, and is currently tested and working on ch570,
and development aims for support for ch573, ch582, ch592/1 and ch32v208 (but this can be extended to other chips).
