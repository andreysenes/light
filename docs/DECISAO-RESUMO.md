# Resumo — StageMod v0

## Em uma frase

**Medusa** (Pro Micro + **ZS-040**) + **4 módulos WS2812B RGB**. MIDI: **Bluetooth** no palco ou **USB** quando a cabeça está perto.

```
DAW ──BT──► [ZS-040]──► [Pro Micro] ──D6──► [Mod1]──► … ──►[Mod4]
     └──USB (opc.)──────►      └── C14 + SMPS 5V 10A na Medusa
```

## Decisões v0

| Tópico | Escolha |
|--------|---------|
| Cabeça | **Pro Micro + ZS-040** na [Medusa](17-CABECA-MEDUSA.md) |
| Módulos | **4×**, 1 WS2812B cada |
| Cor | **RGB completo** (CC 1–14) |
| Alimentação | **5V** / 1A |
| Dados | **1 fio** WS2812 (pin D6) |
| Spot | D6 — 5V + GND + DATA (fios ou XLR IN/OUT em cadeia) |
| Tubo flex | D5 — tubo neon WS2811, XLR único (4×1 m no futuro) |
| Conectores | [XLR 3 pin](16-XLR-CONECTORES.md): 1=GND, 2=+5V, 3=DATA |
| Cabeça física | Medusa — Pro Micro + ZS-040 + XLR; **USB** quando perto do PC |

## MIDI rápido

| Módulo | R | G | B | Nota |
|--------|---|---|---|------|
| 1 | CC1 | CC2 | CC3 | C3 |
| 2 | CC4 | CC5 | CC6 | D3 |
| 3 | CC9 | CC10 | CC11 | E3 |
| 4 | CC12 | CC13 | CC14 | F3 |

- **CC7** = dimmer · **PC0** = blackout · **PC1–6** = presets cor

## Firmware

`firmware/promicro-4mod/promicro-4mod.ino`

## Ligação mínima

- D6 → 470Ω → DIN módulo 1
- 5V/GND em paralelo nos 4 LEDs
- Cap 470µF no 1º módulo

## Limites

- **4 módulos** (firmware)
- **~250 mA** max @ 5V
- Palco pequeno / efeito — não wash 10W

## v1 (depois)

ESP32, 24V, 2×10W, P4+RJ45 — [v1/README.md](v1/README.md)

## Próximo passo

Montar hardware → upload → [08-ROADMAP.md](08-ROADMAP.md)
