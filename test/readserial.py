#!/home/rick/rjsvenv/mqtt/bin/python
import serial
import time
import argparse


def doarguments(args):
    parser = argparse.ArgumentParser(
        description="Read data from serial port",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "-d",
        "--device",
        type=str,
        dest="device",
        default="/dev/ttyS0",
        help="Serial port to connect with",
    )
    parser.add_argument(
        "-b",
        "--baud",
        dest="baud",
        type=int,
        default=9600,
        help="Serial baud rate",
    )
    parser.add_argument(
        "--eol",
        dest="eol",
        type=str,
        default=None,
        help="read to eol: None (ignore), crlf, cr, lf",
    )
    parser.add_argument(
        "-L",
        "--linelength",
        dest="llen",
        type=int,
        default=256,
        help="amount of data for each read()",
    )
    parser.add_argument(
        "-T",
        "--timeout",
        dest="timeout",
        type=float,
        default=None,
        help="timeout for in seconds read: None for blocking, 0 non blocking, t seconds",
    )
    parser.add_argument(
        "-D",
        "--debug",
        dest="debug",
        action="store_true",
        help="enable debug",
    )
    r = parser.parse_args(args)
    return r


def domain(args):
    r = doarguments(args)
    ser = serial.Serial(port=r.device, baudrate=r.baud, timeout=r.timeout)
    time.sleep(5)  # wait for serial to connect
    keepgoing = True
    eolchar = None
    if r.eol == "crlf":
        eolchar = b"\r\n"
    elif r.eol == "cr":
        eolchar = b"\r"
    elif r.eol == "lf":
        eolchar = b"\n"

    while keepgoing:
        try:
            if eolchar is None:
                indata = ser.read(r.llen)
            else:
                indata = ser.read_until(expected=eolchar)
            if (l := len(indata)) > 0:
                print(f"len={l}")
                print(indata)
            elif r.timeout != 0:
                print("Timeout")

        except KeyboardInterrupt:
            keepgoing = False


if __name__ == "__main__":
    import sys

    domain(sys.argv[1:])
