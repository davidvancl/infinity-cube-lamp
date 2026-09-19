# infinity-cube-lamp

Firmware for a lamp with an RGB LED strip, running on an ESP8266 (NodeMCU v2). The strip is controlled with an infrared remote, and the firmware updates itself from GitHub Releases.

## Hardware

- ESP8266 NodeMCU v2
- PWM driver (I2C, address `0x40`), channels 0, 1, 2 = red, green, blue
- IR receiver
- Classic 24-button IR remote with colored buttons

Wiring (can be changed in [include/config.h](include/config.h)):

| Signal | GPIO |
|---|---|
| I2C SDA | 4 |
| I2C SCL | 5 |
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

Everything is in [include/config.h](include/config.h): pins, PWM driver address and frequency, brightness steps, default color and the color table for the buttons. Button codes are in [include/IRController.h](include/IRController.h).

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

On startup the firmware prints its version and the result of the update check.

## Firmware update (OTA)

Uses the [esp-ota-updater](https://github.com/davidvancl/esp-ota-updater) library. On startup the device checks the latest release and updates itself if a newer version exists.

Releasing a new version:
1. Increase `custom_version` in `platformio.ini`.
2. Commit and push to `main`.
3. GitHub Actions publish a release. The device updates after its next restart.

Do not push a locally changed version in `platformio.ini` unless you want to publish a release.
