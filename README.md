# HeadTracker

DIY head-tracker based on this instructions: https://wiki.flightgear.org/User:Massima/Howto:Hatire_head_tracker

To seperate my USB devices I've edited boards.txt from Arduino IDE and copied the complete block for leonardo.name=Arduino Leonardo

Then I've changed the IDs from "leonardo." to "leonardo_headtracker." and the name and usb_product from "Arduino Leonardo" to "Arduino Leonardo (HeadTracker)".

As last step I've changed to VID to 0x2341 and the PID to 0xA002.