#!/home/rick/rjsvenv/mqtt/bin/python
import serial
import time
import argparse


def doarguments(args):
    parser = argparse.ArgumentParser(
        description="Drive periodic data out serial port",
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
        "-L",
        "--linelength",
        dest="llen",
        type=int,
        default=40,
        help="Length of each line in batch",
    )
    parser.add_argument(
        "-g",
        "--batch_gap",
        dest="gap",
        type=float,
        default=1,
        help="seconds between batches (float) (0 is continuous)",
    )
    parser.add_argument(
        "-B",
        "--batch",
        type=int,
        dest="batch",
        default=5,
        help="number lines in a batch",
    )
    parser.add_argument(
        "-D",
        "--debug",
        dest="debug",
        action="store_true",
        help="enable debug",
    )
    parser.add_argument(
        "-E",
        "--echo",
        dest="echo",
        action="store_true",
        help="echo output to stdio",
    )

    parser.add_argument(
        "-8",
        "--eight",
        dest="doeight",
        action="store_true",
        help="enable 8 bit characters instead of 7 bit",
    )
    r = parser.parse_args(args)
    return r


linedata = b"12345,67890,ABCDEF,GHIJK,lmnop,qrstu,VwXyZ"


def dobatch(ser, nline, linedata, *, echo=False, debug=False):
    for _ in range(nline):
        if not (debug or (ser is None)):
            ser.write(linedata)
        if echo or debug:
            print(linedata)
    if echo or debug:
        print("End dobatch")


def getline8(llen):
    b = bytearray()
    for i in range(llen):
        b.append(255 - (i & 255))
    return b


def getline7(llen):
    cl = 0
    ldata = b""
    flen = len(linedata)
    while cl < llen:
        ldata = ldata + linedata[0 : min(flen, llen - cl)]
        cl = len(ldata)
    return ldata + b"\r\n"


def getline(llen, *, eightbit=False):
    return getline8(llen) if eightbit else getline7(llen)


def domain(args):
    r = doarguments(args)
    ser = serial.Serial(r.device, r.baud)
    time.sleep(5)  # wait for serial to connect
    keepgoing = True
    ldata = getline(r.llen, eightbit=r.doeight)
    while keepgoing:
        try:
            dobatch(ser, r.batch, ldata, echo=r.echo, debug=r.debug)
            if r.gap:
                time.sleep(r.gap)
        except KeyboardInterrupt:
            keepgoing = False


if __name__ == "__main__":
    import sys

    domain(sys.argv[1:])
