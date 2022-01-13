#!/usr/bin/env python3.10
# -*- coding: utf-8 -*-

import sys
from time import sleep
import psutil
import serial.tools.list_ports


def conn_arduino():
    arduino_port = None
    ports = serial.tools.list_ports.comports()

    for port in sorted(ports):
        active_port = serial.Serial(port.device, timeout=1)

        print('Connecting to ' + active_port.name + '...')

        try:
            sleep(2)

            active_port.write(b'HLEO\n')
            msg = active_port.readline().decode().rstrip()

            if msg == 'HBLN':
                print('\"Arduino\" found!')
                arduino_port = active_port
                break
        except Exception as e:
            print('Connection to \"Arduino\" failed:')
            print(e)
            sys.exit(1)
        except KeyboardInterrupt:
            active_port.write(b'BYEL\n')
            active_port.close()
            print('\nBye!')
            sys.exit(0)

    return arduino_port


def send_data(active_port):
    try:
        sleep(3)

        msg = active_port.readline().decode().rstrip()

        if msg == 'REDY':
            print('\"Arduino\" ready! Start sending data')

            while True:
                cpu_perc = psutil.cpu_percent()
                cpu_load_avg_prec = [x / psutil.cpu_count() * 100 for x in psutil.getloadavg()]

                ram_perc = psutil.virtual_memory().percent
                ram_used = psutil.virtual_memory().used
                ram_ttl = psutil.virtual_memory().total

                swap_perc = psutil.swap_memory().percent
                swap_used = psutil.swap_memory().used
                swap_ttl = psutil.swap_memory().total

                active_port.write(('DATA|' + str(cpu_perc) + '|' + str(ram_perc) + '|' + str(ram_used) + '|'
                                   + str(ram_ttl) + '|' + str(swap_perc) + '|' + str(swap_used) + '|' + str(swap_ttl)
                                   + '|' + "{:.1f}".format(cpu_load_avg_prec[0]) + '|'
                                   + "{:.1f}".format(cpu_load_avg_prec[1]) + '|'
                                   + "{:.1f}".format(cpu_load_avg_prec[2]) + '\n').encode())

                sleep(1)
        else:
            print('\"Arduino\" is not ready.')
    except Exception as e:
        print('Sending data to \"Arduino\" failed:')
        print(e)
        sys.exit(1)
    except KeyboardInterrupt:
        active_port.write(b'BYEL\n')
        active_port.close()
        print('\nBye!')
        sys.exit(0)


if __name__ == '__main__':
    print('Comp Info\n')

    print('Searching port \"Arduino\"...')
    while True:
        arduino = conn_arduino()

        if arduino is not None:
            break
        else:
            print('\"Arduino\" not found!')
            print('Continuing to search \"Arduino\"\n')

    if arduino is not None:
        send_data(arduino)
