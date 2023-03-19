# micropython_nrf82540

Check out NRF devlopment to match expansion board tests.

1.  `time.time()` and `time.sleep()` missing - see `modutime.rjs.c` for simple work around. 

2.  `machine.UART(0, 9600)` with GPS gets stuck
     `test/driveserial.py` can be used to drive a serial port to test without a GPS module.  Note in my testing, the GPS module caused the UART to quit receiving while the `driveserial.py` tests did not.  It uses the `pyserial` module.
	 
usage: driveserial.py [-h] [-d DEVICE] [-b BAUD] [-L LLEN] [-g GAP] [-B BATCH]
                      [-D] [-E] [-8]

Drive periodic data out serial port

options:
  -h, --help            show this help message and exit
  -d DEVICE, --device DEVICE
                        Serial port to connect with (default: /dev/ttyS0)
  -b BAUD, --baud BAUD  Serial baud rate (default: 9600)
  -L LLEN, --linelength LLEN
                        Length of each line in batch (default: 40)
  -g GAP, --batch_gap GAP
                        seconds between batches (float) (0 is continuous)
                        (default: 1)
  -B BATCH, --batch BATCH
                        number lines in a batch (default: 5)
  -D, --debug           enable debug (default: False)
  -E, --echo            echo output to stdio (default: False)
  -8, --eight           enable 8 bit characters instead of 7 bit (default:
                        False)					

I modified uart.c with:

+ added volatile counters to track interrupt behavior:
   nuaint = count entry to interrupt
   nrxint = count rx-done events
   nerr   = count rx err events
+ add an argument to any() to allow print out of interrupt counts
+ added deinit function
+ latest version trigger rx again after error


experiment.txt- results using uarte, added deinit() function, no retrigger of rx after error (and no error count here)
   hangs, usually after reset - note there are extended periods where interrupts occur (incrementing nuaint) but not rx-done (no change in nrxint)
   also note the odd characters from GPS. I believe this indicates odd state of GPS module.

experiment2.txt - add retrigger of rx after error
   no hangs, errors after resetting ... note odd 8-bit values from GPS
