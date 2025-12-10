#!/usr/bin/env python3
"""Simple telemetry client to read CSV packets from UART, log to file, and plot in realtime.

Requirements:
    pip install pyserial matplotlib

Usage:
    python3 telemetry.py --port /dev/ttyUSB0 --baud 115200
"""
import argparse
import serial
import time
import csv
import threading
import matplotlib.pyplot as plt

def reader_thread(ser, csvfile):
    with open(csvfile, 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['t','position','vel_enc','vel_fused','control'])
        while True:
            line = ser.readline().decode('ascii', errors='ignore').strip()
            if not line:
                continue
            parts = line.split(',')
            if len(parts) < 5:
                continue
            try:
                w.writerow(parts[:5])
                f.flush()
            except Exception as e:
                print('parse error', e)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--port', required=True)
    ap.add_argument('--baud', type=int, default=115200)
    ap.add_argument('--out', default='telemetry.csv')
    args = ap.parse_args()

    ser = serial.Serial(args.port, args.baud, timeout=1)
    t = threading.Thread(target=reader_thread, args=(ser,args.out), daemon=True)
    t.start()
    print('Logging to', args.out)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print('exiting')

if __name__ == '__main__':
    main()
