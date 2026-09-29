# ESP-01 — bridge MIDI UDP → serial (opcional)

**Não faz parte da Medusa v0** — a cabeça usa **ZS-040** ([19-ZS-040.md](../../docs/19-ZS-040.md)). Este sketch é alternativa Wi‑Fi para quem não usar Bluetooth.

## Hardware

| ESP-01 | Ligação |
|--------|---------|
| VCC | **3,3 V** (regulador na Medusa) |
| GND | GND comum |
| TX | Pro Micro **RX (D0 / Serial1)** |
| RX | Pro Micro **TX (D1)** via divisor 5V→3,3 V |

**CH_PD** (EN) no ESP-01: ligar a **3,3 V** para manter o chip ativo.

## Upload

1. Adaptador USB **3,3 V** para ESP-01 (GPIO0 → GND no flash).
2. Arduino IDE: placa **Generic ESP8266 Module**, 1 MB flash.
3. Editar `WIFI_SSID` / `WIFI_PASS` no `.ino`.
4. Upload; anotar IP (Serial Monitor após boot ou roteador).

## Protocolo

- **UDP** porta **5004**
- Payload = bytes MIDI (ex. `0xB0 0x01 0x7F` = CC1 no canal 1)
- Sem cabeçalho extra — repasse direto para UART

## PC

Ver script de exemplo em [docs/18-WIRELESS-MIDI.md](../../docs/18-WIRELESS-MIDI.md).

## Pro Micro

`ENABLE_SERIAL_MIDI 1` e `SERIAL_MIDI_BAUD 115200` em `promicro-4mod.ino`.
