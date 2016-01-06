Example Summary
----------------
Application that toggles board LEDs using a Pin interrupt.

Peripherals Exercised
---------------------
Board_LED1      Toggled by Board_KEY_RIGHT
Board_LED2      Toggled by Board_KEY_LEFT
Board_LED3      (If defined) toggled by Board_KEY_UP
Board_LED4      (If defined) toggled by Board_KEY_DOWN
Board_KEY_SELECT (If defined) toggles all LEDs

Example Usage
-------------
Run the example.
Board_LED1 is toggled by pushing Board_KEY_RIGHT.
Board_LED2 is toggled by pushing Board_KEY_LEFT.
Board_LED3 is toggled by pushing Board_KEY_UP.
Board_LED4 is toggled by pushing Board_KEY_DOWN.
Board_KEY_SELECT toggles all LEDs
Each key's interrupt is configured for a falling edge of the pulse. A small
delay has been added to provide button de-bounce logic.

Application Design Details
--------------------------
The pinCallbackFxn function is defined in the pinInterrupt.c file. This function
is called in the context of the pin interrupt (Hwi).

For GNU and IAR users, please read the following website for details about semi-hosting
http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting.
