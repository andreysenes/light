# Visão geral — StageMod v0

## Objetivo

Sistema de **4 módulos de luz** para palco/ensaio, controlados por **MIDI** a partir de uma DAW, usando componentes acessíveis:

- **Pro Micro** como cabeça única
- **WS2812B** (RGB completo) em cada módulo
- **Fonte 5V** simples

## O que é v0

| Inclui | Não inclui (v1) |
|--------|-----------------|
| 4 módulos, 1 LED RGB cada | LEDs 10W mono |
| MIDI USB | RS-485 / P4 / RJ45 |
| Pro Micro | ESP32 |
| Cadeia WS2812B (1 fio data) | ATtiny nos módulos |
| Fonte 5V | Fonte 24V |

## Diagrama

```
┌─────────────┐   5V + GND + DATA    ┌──────────────────┐
│ Pro Micro   │ ───────────────────► │ Módulo 1         │
│ MIDI USB    │                      │ 1× WS2812B RGB   │
└─────────────┘                      └────────┬─────────┘
                                              │ DOUT
                                              ▼
                                     Mod2 ──► Mod3 ──► Mod4
```

## Módulo físico

Cada módulo é mínimo:

- **1× WS2812B** (breakout ou LED em star)
- **IN / OUT**: 5V, GND, DATA (pass-through)

Não há MCU no módulo — só o LED e fios.

## Controle de cor

O WS2812B permite **qualquer cor RGB**:

- **CC 1–14** no DAW → R, G, B de cada módulo
- **Notas C3–F3** → acendem módulo com cor definida; velocity = brilho
- **PC 0–6** → presets (blackout, warm, R, G, B, magenta, branco)

Detalhes: [05-MIDI-DAW.md](05-MIDI-DAW.md).

## Limites v0

| Fator | Valor |
|-------|-------|
| Módulos | **4** (fixo no firmware) |
| Corrente total | ~250 mA (4 LEDs full white) |
| Distância DATA | < 1 m entre módulos (ideal) |
| Tensão | **5 V apenas** |

## Evolução para v1

Quando o protótipo MIDI estiver validado, migrar para rig 24V / 10W / ESP32 — ver [v1/README.md](v1/README.md).

## Glossário

| Termo | Significado |
|-------|-------------|
| Cabeça | Pro Micro — único MCU |
| Módulo | 1 WS2812B + pass-through |
| Cadeia WS2812 | LEDs em série no mesmo fio DATA |
| DIN / DOUT | Entrada / saída de dados do LED |
