Zoul RE-MOTE
============

The Zoul RE-MOTE example is based on the Zoul RE-MOTE devices from Zolertia.
This product setup includes button and leds instances and can be used as
an example device together with the Sparrow example.

Run: git submodule update --init

At apps/tinydtls/platform-specific/platform.h add:
#ifdef CONTIKI_TARGET_ZOUL include "platform-specific/config-cc2538dk.h"
#endif

Compile with:
make MAKE_WITH_DTLS=1 MAKE_WITH_IPSO=1
