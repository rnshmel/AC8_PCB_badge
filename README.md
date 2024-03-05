# AvengerCon 8 Electronic Badge Files

Hardware and software design files for the AvengerCon 8 electronic badge. The final version that was fabricated and distributed at the conference is version 1.3

The official name I gave this badge is the "8-8-8 Badge": because this is AC8 and I wanted to incorporate the theme of the number 8. The badge has 8 LEDs (A through H) and 8 push buttons 9B0 through B7). The challenge is to use the 8 buttons to input 8-digit codes and illuminate the individual LEDs. The codes were distributed to the various booths and villages around the conference. This encouraged attendees to explore the conference and interact with all the various groups there in order to collect codes. The first 10 people to solve the badge got a unique conference coin as a small prize.

## Files

The **version1.3** folder contains both the hardware and software files.

### Hardware

 - Gerber PCB files
 - Schematic file
 - Fabrication "pick and place" file
 - Bill of materials (BOM) 
 - Top and bottom copper layer PNGs
 - 3D render

The overall design uses an STM8 microcontroller as the brain of the badge. Power is sourced from batteries and converted using a DC/DC step-up converter to get a steady 3.3 VDC supply. The push buttons are wired directly into the STM8's GPIO pins. I used a shift register to control the LEDs due to insufficient GPIO pins: The LED states are saved in software and shifted in as the codes are solved.

The badge is programed with STMs Single Wire Interface Module (SWIM), which worked really well for this application.

### Software

The **main.c** file in the **src** folder contains the software for the badge. The other files in **inc** and **src** are libraries to interface with with the STM8. The overall architecture uses polling loops instead of interrupts, which is less efficient from a power standpoint but simpler from a coding standpoint. I was under time constraints when building this and needed to get it working quickly.

The push button GPIOs are continuously polled by the CPU. If a button press is detected, it is saved in a FIFO buffer. After every new addition, the buffer is compared to the various challenge codes. If a match is detected, the LED register for that challenge is updated to reflect a "solve". If a code is solved, it is removed from the remaining codes list and not checked again.

There is also a "bank LED function" in the badge (the LEDs are on the brighter side and I wanted a way for attendees to turn them off without losing their progress). inputting the code "all 7's" will toggle the LEDs on or off.

To display the LEDs, I use a few GPIO pins to "bit bash" the data and clock inputs to shift-in the LED register.

### Issues
- Polling instead of interrupts is not power efficient for an embedded device
- The LEDs are always on and source a lot of current. By using an additional pin I could do PWM on the shift register display to reduce the LED illumination duty cycle
-   The software debounce is not correctly implemented, and doesn't detect fast key presses
