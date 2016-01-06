Example Summary
----------------
Sample application to transmit and receive data via USB CDC.

Peripherals Exercised
---------------------
Board_LED0      Transmit indicator LED
Board_LED1      Receive indicator LED
Board_USBDEVICE Used for serial communication*

*  Please ensure that the board is connected to your host via a USB cable.
   Depending on your board, this may require a second USB connection.

Please refer to the Getting Started Guide's Board section to get details
regarding the location of the buttons, LEDs, USB connections and any
additional settings (e.g. jumpers) for your specific board.

Example Usage
-------------
First run the example. Board_LED0 turns ON to indicate TI-RTOS driver
initialization is complete.

When the application is running, open a serial session (e.g. HyperTerminal,
puTTY, etc.) to the appropriate COM port. Note: the COM port can be determined
via Device Manager in Windows or via ls /dev/tty* in Linux.

Once the connection is made, the board transmits the following text every
two seconds:

    "TI-RTOS controls USB.\r\n"

The Board_LED0 is toggled when a transmission occurs.

Board_LED1 toggles once character(s)* are received. Typed characters are printed
to the SysMin internal buffer. These can be viewed by stopped the target and
looking at SysMin in ROV.

*  The MSP430 collects 31 characters before returning. The Tiva and Concerto
   family devices collect a single character before returning.

** Note characters typed into the serial session are not echoed back, so you
   will not see them (unless you enable echo on the host).

USB drivers can be found at the following locations:
    Tiva USB Drivers:
    Windows USB drivers are located in the products directory:
    <tirtos_install_dir>\products\<TivaWare_install_dir>\windows_drivers

    MSP430 USB Drivers:
    Windows USB drivers are located within the CCS project's USB_config/
    directory.

    Concerto Family USB Drivers:
    Windows USB drivers are located in the products directory:
    <tirtos_install_dir>\products\<MWare_install_dir>\windows_drivers

Application Design Details
--------------------------
This application uses two tasks:

  'transmit' performs the following actions:
      Determine if the device is connected to a USB host.

      If connected, periodically sends an array of characters to the USB host.

  'receive' performs the following actions:
      Determine if the device is connected to a USB host.

      If connected, it prints, via System_printf, any received data and the
      number of bytes. SysMin is used for this example, so the output goes into
      its internal buffer.

For GNU and IAR users, please read the following website for details about semi-hosting
http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting.
