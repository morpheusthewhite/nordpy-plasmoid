# NordPy Plasmoid

A Plasma widget to control [NordPy](https://github.com/morpheusthewhite/nordpy); it uses the last server type used within the application to establish the VPN connection.

## Features

- Starts connection with recommended server (according to nordvpn site), using the last chosen server type (through `openvpn`)
- Stops any running nordpy connection
- Shows IP (also country, when available), which is updated when a connection is established

### Screenshot

![Alt text](package/contents/screenshot.png?raw=true "Preview")

## Installation

Before installing this plasmoid make sure to have `polkit` and `nordpy` (at least version 1.3.2) on your system.

Then just run `./build.sh`.