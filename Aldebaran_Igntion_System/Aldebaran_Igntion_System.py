from machine import Pin, UART

Relay_pin = Pin(27, Pin.OUT)

uart = UART(0, 9600)

cmd = ''
CommandStarted = False

while True:
    if uart.any():
        command = uart.readline()
        if CommandStarted == False and command == b'.':
            CommandStarted = True
            continue
        if CommandStarted == True and command == b'.':
            CommandStarted = False
            if command == 'launch':
                Relay_pin.value(1);
            if command == 'reset':
                Relay_pin.value(0);
            cmd = ''
        if CommandStarted:
            cmd += command.decode()