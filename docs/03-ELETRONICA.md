# Eletrônica — Cabeça, módulo e drivers 10 W

## Visão geral

```
┌── Cabeça ──────────────────┐     ┌── Módulo Dual ─────────────┐
│ ESP32-S3                   │     │ ATtiny1614                 │
│  USB MIDI                  │     │  MAX485                    │
│  MAX485 ───────── RS-485 ──┼─────┼── MAX485                   │
│  Buck 5V                   │     │  PWM A ──► Driver CC ──► WW│
└────────────────────────────┘     │  PWM B ──► Driver CC ──► R │
                                   └────────────────────────────┘
         ▲                                      ▲
    Fonte 24 V ─────────── Cabo StageMod ──────┘
```

Referência conceitual MOSFET: [vídeo ESP + MOSFET](https://www.youtube.com/watch?v=HSeckw3VLy8) — aplica-se ao **chaveamento**, não à alimentação do LED pelo ESP.

## Cabeça — esquema

| Bloco | Parte | Notas |
|-------|-------|-------|
| MCU | ESP32-S3-WROOM | USB nativo |
| RS-485 | MAX485 / SP3485 | DE+RE em 1 GPIO |
| Alimentação | Buck 24→5 V | Alimenta ESP; entrada do Cabo StageMod |
| Saída | GX16-5 OUT | Para primeiro módulo |
| Entrada fonte | GX16 ou borne | V+ 24 V da fonte central |

GPIO sugeridos:

| GPIO | Função |
|------|--------|
| USB | MIDI |
| 17 | UART2 TX → DI |
| 16 | UART2 RX ← RO |
| 4 | RS-485 DE/RE |
| 5 | LED status |

## Módulo Dual — esquema

| Bloco | Parte | Notas |
|-------|-------|-------|
| Decoder | ATtiny1614 | UART + 2× PWM LEDC |
| Bus | MAX485 | Pass-through A/B |
| Addr | DIP-3 | Pull-ups internos |
| Driver A, B | Buck CC 900 mA | XL6001 ou PT4115 mod |
| Chaveamento | IRLB8721 no EN | Se driver não PWM nativo |
| Proteção | Polyfuse 2 A, TVS 24 V | Entrada IN |
| LEDs | Star 10 W × 2 | Soquetes A, B |

### ATtiny1614 vs ESP

- UART hardware para RS-485.
- 2 canais PWM ~20 kHz.
- ~US$ 0,60 vs US$ 2,50 ESP32.
- Firmware < 4 KB flash.

## Driver 10 W — canal único

```
24V (barramento) ──► [Buck CC 900mA] ──► LED (+)
                           ▲
                      EN ◄── PWM (ATtiny) ou MOSFET
LED (−) ───────────────────────────────────► GND
```

### Ajuste PT4115 / XL6001 para 900 mA

- PT4115: R_sense ≈ 0,15 Ω para ~900 mA (ver datasheet).
- Verificar com amperímetro em série antes de carga térmica longa.

### MOSFET no enable (alternativa)

```
GPIO ──100Ω──┤G  IRLB8721
             ┤D── EN do módulo buck
             ┤S── GND
```

## MOSFET — quando usar

| Situação | Solução |
|----------|---------|
| Buck aceita PWM em EN | PWM direto do ATtiny |
| Buck só liga/desliga | MOSFET logic-level no EN |
| Driver linear (protótipo) | MOSFET low-side + resistor (não recomendado 10 W) |

**IRLB8721** para 10 W; **AO3400A** só se corrente < 2 A confirmada.

## Pass-through no módulo

```
IN pin1 V+ ── polyfuse 2A ──┬── buck drivers
                            └── OUT pin1 V+
IN pin2 GND ────────────────┬── OUT pin2 GND
IN pin3/4 D+/D− ── MAX485 ─┴── OUT pin3/4
```

Trilha V+: fio AWG18 entre conectores ou trilha ≥ 3 mm na PCB.

## Terminação RS-485

- Resistor **120 Ω** entre D+ e D− no **último** módulo de cada ramo (jumper SMD).
- Cabeça **não** termina (só transceiver).

## Segurança

| Item | Valor |
|------|-------|
| Fusível Cabeça | 15–20 A (entrada fonte) |
| Polyfuse módulo | 2 A |
| TVS entrada | SMBJ24A |
| Temperatura teste | 30 min @ 100 % ambos canais |

## Protótipo em breadboard (ordem)

1. Cabeça: ESP32 envia “hello” serial USB + loopback RS-485.
2. 1 canal: ATtiny + 1 driver + 1 LED 10 W (começar em 50 % PWM).
3. Medir corrente e temperatura.
4. Adicionar segundo canal + cabo StageMod curto.
