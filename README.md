# ch32fun_isler
Industry Standard Low Energy Radio (iSLER) RX/TX for ch32fun

### install:
Checkout [ch32fun](https://github.com/cnlohr/ch32fun) on the same level as this repository, and just run `make`.
If you have your copy of `ch32fun` somewhere else you probably already know what to do; change the `include`
in the `Makefile` to point to that.

### supported MCUs:
This code aims to support all WCH RF enabled microcontrollers, and is currently tested and working on ch570, ch582 and ch592,
and development aims for additional support for ch573 and ch32v208 (but this can be extended to other chips).
Current focus is on getting 1M rx/tx working on all, and when that is finished 2M and Coded Phy S2 and S8 will be added
where supported.

| Chip       | RX | TX | 1M | 2M | S2 | S8 |
|------------|----|----|----|----|----|----|
| ch570/2    | √  | √  | √  | x  | x  | x  |
| ch571/3*   | ~  | x  | ~  | x  | x  | x  |
| ch582/3    | √  | √  | √  | x  | x  | x  |
| ch584/5    | x  | x  | x  | x  | x  | x  |
| ch591/2    | √  | √  | √  | x  | x  | x  |
| ch23v208   | √  | √  | √  | x  | x  | x  |

* ch571/3 is a completely different creature in many respects, and iSLER support is very challenging. Current state is that
the core init seems ok, but TX does not work and RX seems to receive but since DMA has to be handled manually here
I don't know where to pull the frame data from. It's possible the TX issues are also from the DMA part, but the LLE_IRQHandler
is also sus.