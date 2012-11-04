shift-register-test-one-7-seg-diplay
====================================

This is a trivial demo of a 4094 shift register.
It drives a single 7-segment display.

Circuit Construction
--------------------

* Arduino D2 to shift register strobe (STR).
* Arduino D3 to shift register data (D).
* Arduino D4 to shift register clock (CP).

Tie the shift register output enable (OE) high.

Connect the 7-segment display thus: 

* QP0 to segment A.
* QP1 to segment B.
* QP2 to segment C.
* QP3 to segment D.
* QP4 to segment E.
* QP5 to segment F.
* QP6 to segment G.

This demo does not use the decimal point, but QP7 can be used.

