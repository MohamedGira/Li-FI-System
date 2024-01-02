# Li-FI-System
Embedded systems project that utilizes the use of LiFi to send data among different platforms

## General Notes
Make sure you have tivaware installed and that its files are accessable to the project

## Interfacing

### PORTB
* PB2: IR sender
* PB3: Start Button (PUR)
* PB4:Stop Button (PUR)
    * `TODO: on stopping, disable inturrpts instead of using extern 'started'`
#### Ultrasonic:
* PB6: echo
* PB7: trigger
    * `Timer0: used with ultrasonic as edge capturer`

### PORTE
* PE1: Hall Switch sensor (digital)
* PE2: LDR sensor (analog)
* PE3: Fume sensor (analog)
* PE4: Bluetooth TX
* PE5: Bluetooth RX

#### Notes
* Bluetooth uses `UART5` port
* Timer1 is used by `dalay utils`
* Timer2 is used along with analog sensors (trigger every sec)

### PORTF
* `SW0` and `SW4`: mute button (one of them is corrupted)
* we use portF led to indicate start/stop
