# Protótipo v0 — Pro Micro + 4 módulos WS2812B

Fase inicial usando componentes que você já tem, antes do rig 24V / 10W / ESP32.

## Arquitetura deste protótipo

```
DAW ──USB MIDI──► [Pro Micro] ──data──► [Mod1]──►[Mod2]──►[Mod3]──►[Mod4]
                      │
                   Fonte 5V ──┬── alimenta Pro Micro + cadeia VCC/GND dos módulos
```

| Peça | Função |
|------|--------|
| **Pro Micro** | Cabeça + controle (substitui ESP32 nesta fase) |
| **4 módulos** | 1× WS2812B cada, pass-through 5V/GND/DATA |
| **Fonte 5V** | ≥ 1 A (USB do PC **não** basta com 4 LEDs acesos) |

Não há RS-485, P4 nem ATtiny nesta fase — tudo num único fio de dados WS2812B.

## Módulo físico mínimo

```
        IN                    OUT
    5V ──┬── VCC LED ──┬── 5V
   GND ──┴── GND LED ──┴── GND
  DATA ───── DIN    DOUT ─── DATA
```

- **1 LED** por módulo (endereço na cadeia: 0, 1, 2, 3)
- Cabos entre módulos: 3 condutores (5V, GND, DATA) — pode ser fita dupont ou chicote fino

## Limites deste protótipo

| Fator | Limite |
|-------|--------|
| Módulos | **4** (fixo no firmware) |
| Corrente | ~60 mA/LED full white → **~250 mA** total |
| Distância DATA | < 1 m entre módulos (WS2812B sensível) |
| Tensão | **5 V** apenas — não ligar em 24 V |

## vs. projeto final (StageMod)

| | Protótipo v0 | StageMod final |
|---|--------------|----------------|
| Cabeça | Pro Micro | ESP32-S3 |
| LED | WS2812B 5V | 2× 10W mono + lente 20mm |
| Barramento | 1 fio data | P4 + RJ45 RS-485 |
| Alimentação | 5V | 24V |
| Módulo MCU | Nenhum | ATtiny decoder |

## Firmware

`firmware/promicro-4mod/` — ver README lá para upload e mapa MIDI.

## Lista de materiais (o que você precisa)

| Qty | Item |
|-----|------|
| 1 | Pro Micro 5V |
| 4 | WS2812B (breakout ou LED com PCB) |
| 1 | Fonte 5V ≥ 1A |
| 1 | Resistor 470Ω |
| 1 | Capacitor 470µF–1000µF |
| — | Fios, USB para programar |

## Evolução sugerida

1. ✅ 4 módulos WS2812B + MIDI (esta fase)
2. Validar mapa MIDI no seu DAW
3. Montar carcaça mecânica dos 4 módulos
4. Migrar Cabeça para ESP32-S3 (mesmo mapa MIDI)
5. Substituir módulos por Dual 10W conforme `docs/10-MODULO-DUAL.md`
