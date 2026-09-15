# MIDI e DAW — v0

Firmware: `firmware/promicro-4mod/promicro-4mod.ino`

## Fluxo

```
DAW ──USB MIDI──► Pro Micro ──► FastLED ──► 4× WS2812B RGB
```

## Mapa MIDI — RGB por módulo

Cada módulo: **3 Control Changes** (R, G, B). Valor DAW 0–127 → LED 0–255.

| Módulo | Vermelho | Verde | Azul |
|--------|----------|-------|------|
| **1** | CC **1** | CC **2** | CC **3** |
| **2** | CC **4** | CC **5** | CC **6** |
| **3** | CC **9** | CC **10** | CC **11** |
| **4** | CC **12** | CC **13** | CC **14** |

| CC | Função |
|----|--------|
| **7** | Master dimmer (todos os módulos) |

## Notas (gatilho + brilho)

| Nota | Módulo | Comportamento |
|------|--------|---------------|
| **60** (C3) | 1 | Acende com RGB dos CC 1–3; **velocity** = brilho |
| **61** (D3) | 2 | CC 4–6 |
| **62** (E3) | 3 | CC 9–11 |
| **63** (F3) | 4 | CC 12–14 |
| Note off | — | Apaga o módulo |

## Program Change (presets)

| PC | Preset | Cor (todos os módulos) |
|----|--------|------------------------|
| **0** | Blackout | Apagado |
| **1** | Warm white | RGB(255, 180, 80) |
| **2** | Vermelho | RGB(255, 0, 0) |
| **3** | Verde | RGB(0, 255, 0) |
| **4** | Azul | RGB(0, 0, 255) |
| **5** | Magenta | RGB(255, 0, 255) |
| **6** | Branco | RGB(255, 255, 255) |

## Canal MIDI

```cpp
#define MIDI_CHANNEL 1   // alterar; 0 = omni
```

## Configuração no DAW

### Reaper

1. Preferences → MIDI → habilitar dispositivo USB do Pro Micro
2. Track com saída MIDI → Pro Micro
3. Envelope ou knobs nos CC 1–14

### Ableton Live

1. Preferences → Link/MIDI → Track On no Pro Micro
2. MIDI mapping nos knobs para CC 1–14

## Exemplo de uso

1. `CC1=127, CC2=0, CC3=0` → módulo 1 vermelho
2. `CC2=127` → amarelo
3. `CC1=127, CC3=127` → magenta
4. Nota C3 velocity 100 → módulo 1 com ~80% do brilho

## Latência

| Trecho | Tempo típico |
|--------|--------------|
| USB MIDI | 1–3 ms |
| FastLED update | < 1 ms |

## v1 (futuro)

MIDI na Cabeça ESP32 + RS-485 para módulos 10W — mapa em evolução; ver [v1/README.md](v1/README.md).
