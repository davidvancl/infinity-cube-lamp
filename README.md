# infinity-cube-lamp

Firmware for a lamp with an RGB LED strip, running on an ESP8266 (NodeMCU v2). The strip is controlled with an infrared remote, and the firmware updates itself from GitHub Releases.

## Hardware

- ESP8266 NodeMCU v2
- RGB LED strip driven directly by three PWM pins (e.g. through MOSFETs)
- IR receiver
- Classic 24-button IR remote with colored buttons

Wiring (can be changed in [include/config.h](include/config.h)):

| Signal | GPIO |
|---|---|
| Red | 4 |
| Green | 12 |
| Blue | 5 |
| IR receiver | 14 (D5) |

## Controls

| Button | Action |
|---|---|
| ON / OFF | turn the strip on / off (ON restores the last color) |
| VOLUME UP / DOWN | brightness in 10 % steps (10 to 100 %) |
| R, G, B, W | red, green, blue, white |
| other color buttons | shades by row (see `COLOR_BUTTONS`) |

The FLASH, STROBE, FADE and SMOOTH buttons do nothing yet.

## Configuration

Everything is in [include/config.h](include/config.h): pins, PWM frequency, brightness steps, default and boot color and the color table for the buttons. Button codes are in [include/IRController.h](include/IRController.h).

## WiFi

Create `include/secrets.h` (it is in `.gitignore`):

```cpp
#define SECRET_SSID "wifi-name"
#define SECRET_PASS "wifi-password"
```

On the first upload over USB the credentials are saved to EEPROM. Firmware built by GitHub Actions has no `secrets.h` and uses the saved credentials. To change WiFi, edit `secrets.h` and upload the firmware over USB again.

## Build and upload

```
pio run -t upload
pio device monitor
```

On startup the strip glows orange while the device connects to WiFi and checks for updates, then switches to the default color. The firmware also prints its version and the result of the update check to the serial monitor.

## Source layout

- `src/main.cpp` – `setup()` and `loop()` only
- `src/Led.cpp` – PWM output, brightness, color, boot color
- `src/IrRemote.cpp` – IR receiver and button handling

## Firmware update (OTA)

Uses the [esp-ota-updater](https://github.com/davidvancl/esp-ota-updater) library. On startup the device checks the latest release and updates itself if a newer version exists.

Releasing a new version:
1. Increase `custom_version` in `platformio.ini`.
2. Commit and push to `main`.
3. GitHub Actions publish a release. The device updates after its next restart.

Do not push a locally changed version in `platformio.ini` unless you want to publish a release.
