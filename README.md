# RFID-Based Bike Theft Detection System

An embedded security system designed to prevent unauthorized access to a bike using an **RFID card**. The system uses an **LPC21xx microcontroller** to read an RFID card through the **EM-18 RFID reader**. If the scanned RFID ID matches the authorized card, the engine is enabled. If an unauthorized card is detected, the engine remains stopped and an alert SMS is sent to the owner using a **SIM800C GSM module**.

## Features

* RFID-based authentication
* Authorized card detection
* Unauthorized card detection
* Engine/motor control
* 16×2 LCD status display
* GSM SMS alert for unauthorized access
* Separate UART communication for RFID and GSM
* LPC21xx ARM7 microcontroller-based implementation

## System Overview

```text
             +------------------+
             |    RFID Card     |
             +--------+---------+
                      |
                      v
             +------------------+
             |   EM-18 RFID     |
             |     Reader       |
             +--------+---------+
                      |
                      | UART0
                      v
             +------------------+
             |    LPC21xx       |
             |  Microcontroller |
             +---+----------+---+
                 |          |
             LCD |          | UART1
                 |          |
                 v          v
        +-------------+  +-------------+
        |   16x2 LCD  |  |   SIM800C   |
        |   Display   |  | GSM Module  |
        +-------------+  +------+------+
                                |
                                v
                         +-------------+
                         | Alert SMS   |
                         | to Owner    |
                         +-------------+

                 LPC21xx
                    |
                    v
              Motor / Engine
```

## Working Principle

1. The system starts and displays the project name on the LCD.
2. The user scans an RFID card using the EM-18 RFID reader.
3. The LPC21xx microcontroller receives the RFID ID through **UART0**.
4. The received RFID ID is compared with the authorized RFID ID stored in the program.
5. If the RFID ID matches:

   * LCD displays **Access Granted**.
   * LCD displays **Engine Started**.
   * The motor/engine control output is activated.
6. If the RFID ID does not match:

   * The engine remains stopped.
   * LCD displays **Invalid Card** and **Access Denied**.
   * The SIM800C GSM module sends an alert SMS to the owner.

## Hardware Requirements

* LPC21xx ARM7 Microcontroller
* EM-18 RFID Reader
* RFID Card/Tag
* SIM800C GSM Module
* 16×2 LCD Display
* Motor or Engine Control Circuit
* Motor Driver / Relay Circuit
* Power Supply
* Connecting Wires

## Software Requirements

* Keil µVision
* ARM7/LPC21xx 
* Embedded C
* Flash Magic or suitable programmer
* Serial Terminal (optional, for debugging)

## Project Structure

```text
RFID-Bike-Theft-Detection/
│
├── main.c
├── uart0.h
├── uart1.h
├── lcd.h
├── delay.h
└── README.md
```

### File Description

| File        | Description                                                           |
| ----------- | --------------------------------------------------------------------- |
| `main.c`    | Main program, RFID authentication, motor control, and GSM alert logic |
| `uart0.h`   | UART0 initialization and communication with the RFID reader           |
| `uart1.h`   | UART1 initialization and communication with the GSM module            |
| `lcd.h`     | 16×2 LCD initialization and display functions                         |
| `delay.h`   | Millisecond and second delay functions                                |
| `README.md` | Project documentation                                                 |

## UART Communication

The project uses two UART interfaces:

### UART0

Used for communication between:

```text
EM-18 RFID Reader <----> LPC21xx
```

The RFID reader sends the RFID card ID to the microcontroller through UART0.

### UART1

Used for communication between:

```text
LPC21xx <----> SIM800C GSM Module
```

UART1 is used to send AT commands to the GSM module and send an SMS alert when an unauthorized RFID card is detected.

## RFID Authentication

The authorized RFID ID is stored in the program:

```c
unsigned char key[]="26001EC83ECE";
```

The RFID reader receives 12 characters, which are stored in a buffer and compared using `strcmp()`.

```c
id = scan();

if(strcmp((char*)key,(char*)id)==0)
{
    // Authorized card
}
else
{
    // Unauthorized card
}
```

> **Note:** Replace the RFID ID in `main.c` with the RFID card ID that you want to authorize.

## GSM Alert

When an unauthorized RFID card is detected, the system communicates with the GSM module using AT commands:

```text
AT
AT+CMGF=1
AT+CMGS="PHONE_NUMBER"
```

The system then sends an alert message to the owner.

Example alert:

```text
someone take your bike ALEART
```

You can modify the SMS text in `main.c` according to your requirement.

## LCD Display Messages

The LCD displays different messages based on the system status:

### Startup

```text
theft detection
```

### Waiting for RFID

```text
scan the key
```

### Authorized Card

```text
Acess Granted
Engine Started
```

### Unauthorized Card

```text
Invalid card
Acess Deneid
```

### GSM Alert

```text
Aleart message
```

## Pin Configuration

The project uses the following LPC21xx GPIO configuration:

| Component          | LPC21xx Pin   |
| ------------------ | ------------- |
| LCD Data D0-D7     | P0.10 - P0.17 |
| LCD RS             | P0.18         |
| LCD Enable         | P0.19         |
| Motor Control 1    | P1.21         |
| Motor Control 2    | P1.22         |
| RFID Communication | UART0         |
| GSM Communication  | UART1         |

## Security Flow

```text
           Start
             |
             v
       Initialize LCD
       Initialize UART0
       Initialize UART1
             |
             v
        Scan RFID Card
             |
             v
       Read RFID ID
             |
             v
      Compare RFID ID
        /          \
       /            \
   Match           No Match
     |                |
     v                v
Access Granted    Access Denied
     |                |
     v                v
Engine Started    Engine Stopped
                      |
                      v
                 Send SMS Alert
```

## Future Improvements

* Store multiple authorized RFID IDs.
* Store RFID IDs in EEPROM instead of hard-coding them.
* Add a buzzer for unauthorized access.
* Add GPS location tracking.
* Send the bike's location along with the alert SMS.
* Add a vibration sensor for theft detection.
* Add GSM-based remote engine control.
* Add password-based RFID registration.
* Improve GSM communication by waiting for the `>` prompt before sending SMS.
* Add timeout handling for RFID and GSM communication.

## Important Notes

* Ensure that the UART baud rate configuration matches the actual **PCLK frequency** of the LPC21xx microcontroller.
* The GSM module requires an appropriate power supply capable of handling its current requirements.
* Use a proper relay or motor driver circuit when controlling a real bike engine or motor.
* Do not connect a motor directly to the LPC21xx GPIO pins.
* The phone number and authorized RFID ID should be changed before deploying the project.

## Applications

* Bike anti-theft systems
* RFID-based vehicle access control
* Smart vehicle security
* Industrial access control
* RFID authentication systems
* Embedded security projects
