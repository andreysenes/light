# Eletrônica — v0

## Esquema geral

```
[Fonte 5V] ──┬── VCC Pro Micro
             ├── VCC ──► LED1 ──► LED2 ──► LED3 ──► LED4
             └── GND comum

Pro Micro D6 ──[470Ω]──► DIN LED1 ── DOUT ──► DIN LED2 ── ...
```

## Pro Micro (cabeça)

| Pino | Ligação |
|------|---------|
| **VCC** | 5V (fonte externa recomendada com LEDs ligados) |
| **GND** | GND comum |
| **D6** | Resistor 470Ω → DIN primeiro WS2812B |
| **USB** | Programação + MIDI para DAW |

### Bibliotecas firmware

- **FastLED** — driver WS2812B
- **MIDI Library** (FortySevenEffects) — MIDI USB

## Por módulo

| Conexão | Destino |
|---------|---------|
| 5V IN | VCC do WS2812B + 5V OUT |
| GND IN | GND do WS2812B + GND OUT |
| DATA IN | DIN do WS2812B |
| DATA OUT | DOUT do WS2812B → próximo módulo |

## Componentes passivos

| Item | Onde | Qty |
|------|------|-----|
| Resistor **470Ω** | **Cada módulo:** DATA IN → DIN do WS2812B | **4** |
| Resistor **470Ω** | **Medusa:** D5 e D6 antes dos XLR TUBO/MOD | **2** |
| Capacitor **470µF–1000µF** | **Cada módulo:** 5V/GND no LED | **4** |
| Capacitor **1000µF** | **Medusa:** barramento 5V na fonte | **1** |
| — | Tubo: cap opcional no conector de entrada | 0–1 |

Sem MOSFET nem driver CC na v0.

## Proteção

| Risco | Mitigação v0 |
|-------|----------------|
| USB só alimentando 4 LEDs | Usar **fonte 5V 1A** para VCC dos LEDs |
| Data longa | Cabos < 30 cm entre módulos no protótipo |
| 5V em LED | WS2812B **não** ligar em 24V |

Anti-reverso P4 é especificação **v1** — na v0, observar polaridade 5V/GND manualmente.

## Pinagem alternativa

Alterar em `promicro-4mod.ino`:

```cpp
#define LED_PIN 6   // trocar para 5, 7, 8… se D6 ocupado
```

## Teste sem MIDI

Boot sequence no `setup()` acende cada LED em sequência (R, G, B, W nos 4 módulos). Se um não acender:

1. Verificar ordem na cadeia DIN→DOUT
2. Trocar `COLOR_ORDER`
3. Medir 5V no LED
