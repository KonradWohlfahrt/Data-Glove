![Cover](https://github.com/KonradWohlfahrt/Data-Glove/blob/main/images/Cover.jpg)

# Data Glove
**In this repository you will find the project files for the Data Glove:** A wearable to control your bluetooth devices by hand movement and gestures. It includes the [XIAO nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) microcontroller with five hall sensors and a couple of peripherals. A lipo battery makes this project portable while all the components are  mounted on a bicycle glove. Hall sensors vary the output voltage depending on the strength of the magnetic field. Thus, a change of your finger position can be recognized and interpreted by the microcontroller to, for example, send a command to your phone to increase or decrease the volume. The XIAO is very powerful with rich features and libraries. I have included a few examples for you to try out, but expanding upon them and creating your own applications is simple and fast too!
If you want more information and potentially build one yourself too, you can check out the in-depth [blog](https://www.instructables.com/) on Instructables.
Finally, the printed circuit boards and the XIAO microcontroller were sponsored by [Seeed Studio](https://www.seeedstudio.com/)! They offer a huge variety of microcontrollers, development boards and services for makers! The XIAO series is a small but powerful set of microcontrollers for any project. The size makes it ideal for tiny battery powered iot applications or ble controllers! Thanks to Seeed Studio and without further ado let me quickly give you an overview of the project:

***
# Materials:
| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| custom pcb | 1 | - |
| 10k 0805 | 3 | R1, R2, R4 |
| 33r 0805 | 2 | R5, R6 |
| 1k 0805 | 2 | R7, R8 |
| MMBT2222ALT1 | 2 | Q1, Q2 |
| 5mm LED | 1 | LED1 |
| TSOP38238 | 1 | LED2 |
| tactile button 6x6x6mm | 2 | SW1, SW2 |
| vibration motor 10x2.7mm | 1 | J3 |
| LDR | 1 | R3 |
| 50/100mAh lipo battery | 1 | J1 |
| SK12D07VG5 | 1 | U2 |
| XIAO nRF52840 (Sense) | 1 | U1 |
| ph2.0 3pin 90 degree header | 5 | J5-J9 |
| SS49e hall sensor | 5 | - |
| neodymium magnet 8x3mm | 20 | - |
| M2.5x6mm screw and nut | 3 | - |
| a bicycle glove | 1 | - |
| a few cables | - | - |

***
# Schematic and PCB:
![Schematic](https://github.com/KonradWohlfahrt/Data-Glove/blob/main/images/Schematic_DataGlove.png)
_Schematic_
![PCB](https://github.com/KonradWohlfahrt/Data-Glove/blob/main/images/PCB_DataGlove.jpg)
_The soldered pcb inside of the housing_

***
# Programming and Examples
The following wiki shows you how to setup the Arduino IDE for the XIAO boards, it is straightforward and is done quickly: [Wiki](https://wiki.seeedstudio.com/XIAO_BLE/)
You can directly use the usb c port for programming without any other external device, very handy! Those are the following examples:

- `DataGlovePresentation` -> swap presentation pages by using the buttons or contracting and expanding your hand twice (double press)
- `DataGloveMediaControl` -> control music playback; double press to play/pause, long press to skip, buttons for volume
- `DataGloveFlashlight` -> LED illuminates when forming a fist
- `DataGloveCamerashutter` -> take a photo by double pressing

![Data Glove](https://github.com/KonradWohlfahrt/Data-Glove/blob/main/images/SerialOutput_DataGlove.jpg)
_Testing the hall sensors_
![Data Glove](https://github.com/KonradWohlfahrt/Data-Glove/blob/main/images/DataGlove.jpg)