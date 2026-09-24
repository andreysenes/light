# MIDI sem fio — Medusa + ESP-01 / ZS-040

Alimentação pela **fonte 5V** na Medusa; **comandos** do computador por **Wi‑Fi ou Bluetooth**, sem cabo USB no palco.

## Arquitetura

```
DAW ──► [PC: bridge] ── Wi‑Fi ou BT ──► [ESP-01 ou ZS-040] ── UART ──► Pro Micro ──► LEDs
                                              ▲
                                         3,3 V da Medusa
```

O **Pro Micro** continua gerando os pixels (D5/D6). O módulo sem fio só **repassa bytes MIDI** na serial.

| Camada | Função |
|--------|--------|
| PC | Lê MIDI da DAW e envia **UDP** (ESP) ou usa **porta serial Bluetooth** (ZS-040) |
| ESP-01 / ZS-040 | Rádio + UART |
| Pro Micro | `MIDI_Serial.read()` + mesmo mapa CC/PC/notas |

Firmware Pro Micro: `ENABLE_SERIAL_MIDI` em `promicro-4mod.ino` — [firmware](../firmware/promicro-4mod/).

## Latência — o que esperar

| Caminho | Latência típica | Uso no StageMod |
|---------|-----------------|-----------------|
| **USB** direto no Pro Micro | ~1–3 ms | Melhor para ensaio / gravação |
| **ESP-01 + UDP** (Wi‑Fi, rede dedicada) | ~5–15 ms + jitter | **Recomendado** para show sem cabo |
| **ZS-040 (BLE UART)** | ~15–40 ms | OK para cenas lentas; ruim no beat crítico |

Sem fio **nunca** iguala USB; o objetivo é ficar **abaixo de ~20 ms** percebidos e **estável** (sem bursts).

### Como manter baixa latência (ESP-01)

1. **UDP** no PC → ESP (não TCP, não HTTP).
2. Pacotes **pequenos**: mensagens MIDI completas (3 bytes CC/note), sem filas grandes.
3. Wi‑Fi **2,4 GHz**: PC e ESP na **mesma rede**; evitar repetidor lento; preferir roteador perto da cabeça.
4. No ESP: `WiFi.setSleep(false)`; baud **115200** na UART para o Pro Micro.
5. No PC: script/bridge com prioridade alta; fechar apps que saturam Wi‑Fi.
6. DAW: preferir **CC** para cores; notas com velocity para hits (menos mensagens que automation densa).

### ZS-040 (BLE)

- UART padrão muitas vezes **9600** — subir para **115200** via AT (`AT+BAUD4`) se o módulo permitir.
- No Windows/macOS: porta **COM Bluetooth** + bridge MIDI→serial (ex. loopMIDI + ferramenta que encaminha).
- Latência e jitter do BLE costumam ser **piores** que Wi‑Fi UDP bem configurado.

## Escolha do módulo

| | **ESP-01** (recomendado) | **ZS-040** (BLE) |
|---|---------------------------|------------------|
| Rádio | Wi‑Fi | Bluetooth 4.0 |
| Lógica | 3,3 V | 3,3 V (confirmar no seu lote) |
| Firmware | [esp01-midi-bridge](../firmware/esp01-midi-bridge/) | Transparente UART (AT) |
| PC | UDP → IP do ESP | COM Bluetooth serial |
| Latência | Menor (se UDP) | Maior |

## Ligação na Medusa

### Alimentação

| Módulo | Alimentação |
|--------|-------------|
| Pro Micro | **5V** do barramento Medusa (VCC) |
| ESP-01 / ZS-040 | **3,3 V** via regulador **AMS1117-3.3** (ou similar) a partir do 5V — **não** alimentar ESP em 5V |

Corrente extra: ~80–150 mA (ESP em TX).

### UART (Pro Micro ↔ rádio)

**Serial1** no ATmega32U4 (Leonardo / Pro Micro):

| Pro Micro | ESP-01 / ZS-040 |
|-----------|-----------------|
| **RX (D0)** | TX do módulo (3,3 V) |
| **TX (D1)** | RX do módulo via **divisor** 5V→3,3 V (ex. 1k / 2k) |
| **GND** | GND |

```
Pro Micro TX (5V) ──[1k]──┬── RX ESP
                          │
                         [2k]
                          │
                         GND
```

### Painel Medusa (atualizado)

```
[USB]  ← só programação / fallback MIDI
[MOD] [TUBO] [INJ]  ← XLR LEDs
(Wi‑Fi/BT) antena do ESP/ZS para fora da caixa metálica
```

## PC → ESP-01 (UDP)

1. Grave o sketch [esp01-midi-bridge.ino](../firmware/esp01-midi-bridge/esp01-midi-bridge.ino) no ESP-01 (adaptador USB 3,3 V).
2. Configure `WIFI_SSID`, `WIFI_PASS`, IP fixo ou DHCP.
3. Porta padrão **5004** — cada datagrama = 1 ou mais bytes MIDI brutos.
4. No PC, encaminhe MIDI da DAW para `IP_ESP:5004` (script Python com `mido` + `python-rtmidi`, ou ferramenta equivalente).

Exemplo conceitual (PC):

```python
# Requer: pip install mido python-rtmidi
import socket, mido

UDP = ("192.168.4.1", 5004)  # IP do ESP na sua rede
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def send_raw(msg_bytes):
    sock.sendto(msg_bytes, UDP)

with mido.open_input("Your DAW Virtual MIDI") as port:
    for msg in port:
        send_raw(msg.bytes())
```

Ajuste a porta MIDI de entrada para o virtual port que a DAW usa.

## Pro Micro — configuração

Em `promicro-4mod.ino`:

```cpp
#define ENABLE_USB_MIDI     1   // 0 no show se quiser só sem fio
#define ENABLE_SERIAL_MIDI  1
#define SERIAL_MIDI_BAUD    115200  // igual ao ESP
```

Show só sem fio: `ENABLE_USB_MIDI 0` evita processar USB; mantenha USB só para upload (recompilar entre shows).

## Checklist

- [ ] 3,3 V estável no ESP/ZS (multímetro)
- [ ] Baud **igual** nos dois lados (115200)
- [ ] `MIDI_CHANNEL` igual ao canal da DAW (padrão **1**)
- [ ] Teste com **um CC** (ex. CC1) antes do rig completo
- [ ] Medir latência: metrônomo na DAW + nota no módulo 1 — comparar USB vs sem fio

## Referências

- [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md)
- [05-MIDI-DAW.md](05-MIDI-DAW.md)
- [firmware/esp01-midi-bridge/README.md](../firmware/esp01-midi-bridge/README.md)
