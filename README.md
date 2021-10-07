# arcticOS

A custom operating system written in C for RP2040-based phones.

## Vision

Every modern phone company either sells your data or your attention, and they make you pay huge amounts to let them do it. I aim to change that, by building a phone that is:
- Low-cost
- Fully open-source, in both hardware and software
- As modular as possible, with no stupid software locks to prevent you from extending, repairing, or upgrading your phone
- Completely ad-free
- Easy for anyone with basic knowledge in SMD soldering and 3D printing to replicate

## Features

- ILI9341 display driver
- Keypad driver for EVT1/EVT3
- Font rendering
- Basic menus
- Settings app
- Factory reset
- Low-power sleep mode
  
## Planned features
- Calls and SMS with the EC25X series of modems.
- Calendar
- Contacts
- Calculator
- Notes
- Clock with alarms and reminders
- Easy updates
- User Data Encryption
- Flashlight
- Custom T9 engine

## Roadmap

TBD

## Building

Building arcticOS requires the Raspberry Pi Pico SDK to be located at `~/.pico_sdk` and the Raspberry Pi Pico toolchain binaries to be located at `~/opt/arm/bin`.  
To build, run `build-<DEVICE>.sh`. For custom devices, create a new buildscript and sections in the files in `include/hardware/arcticOS` and `source/hardware`.

## FAQ

#### Will it support WhatsApp?

No.

#### Will it support group messaging?

Group messaging is not currently planned but may be added.

#### What will the final hardware look like?

The final hardware configuration hasn't been fully decided yet, but it should look something like this:
- 2.8" LCD display
- RP2040 CPU
- Quectel EC25X modem (depends on region)
- USB Type C
- Triple-tap keypad + directional stick.

## License

[GNU General Public License Version 3.0](https://choosealicense.com/licenses/gpl-3.0/)

## Special Thanks
- The Raspberry Pi Foundation, for their amazing RP2040 chip (and the outstanding documentation and board design guide)
- Shawn Hyam, for his work on an ILI9341 driver for RP2040-based boards ([available on his GitHub here](https://github.com/shawnhyam/pico/tree/main/ili9341))
