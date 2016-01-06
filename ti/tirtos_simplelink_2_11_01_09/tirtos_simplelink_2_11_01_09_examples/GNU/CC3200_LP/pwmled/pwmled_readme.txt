Example Summary
----------------
Sample application to control on-board LEDs with the PWM driver.

Peripherals Exercised
---------------------
Board_PWM0      PWM instance used to control Board_LED1 brightness
Board_PWM1      PWM instance used to control Board_LED2 brightness

Please refer to the Getting Started Guide's Board section to get details
regarding the location of the buttons, LEDs, USB connections and any
additional settings (e.g. jumpers) for your specific board.

Example Usage
-------------
The example performs general initialization in main().
The pwmLED task varies the intensity of the on-board LEDs at a rate determined
by the arg0 parameter for the Task instance in the .cfg file.  If Board_PWM0
and Board_PWM1 are different (connected to two LEDs), the LED connected to
Board_PWM0 will fade-in while the LED connected to Board_PWM1 will fade-out
and viceversa.

Application Design Details
--------------------------
This application uses one task:
  'pwmLED' performs the following actions:
      Opens and initializes PWM driver objects.

      Uses the PWM driver changed the intensity of the LEDs.

      The task sleeps for 50 system ticks before changing LED intensity again.

For GNU and IAR users, please read the following website for details about semi-hosting
http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting.
