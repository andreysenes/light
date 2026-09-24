# StageMod v0 — Iluminação de palco modular + MIDI

**4 módulos** acopláveis, **1 LED WS2812B RGB** por módulo, controlados por **Pro Micro** via **MIDI USB** a partir de uma DAW.

## Arquitetura v0

```
DAW ──MIDI USB──► [Pro Micro] ──D6──► Mod1 ──► Mod2 ──► Mod3 ──► Mod4
                      │
                   Fonte 5V (≥1A) ── VCC/GND em cadeia nos módulos
```

| Peça | Função |
|------|--------|
| **Pro Micro** | Cabeça única — MIDI → cores RGB |
| **Módulo spot** | 1× WS2812B + pass-through 5V/GND/DATA |
| **Tubo flex** | Fita WS2812B em tubo silicone — gradiente / chase (pin D5) |
| **Fonte 5V** | Pro Micro + spots + tubo (≥ **3A** com tubo) |

Cada WS2812B = **RGB completo** (milhões de cores via MIDI).

## Começar

| Passo | Onde |
|-------|------|
| 1. Ligar hardware | [docs/07-CABLAGEM.md](docs/07-CABLAGEM.md) |
| 2. Upload firmware | [firmware/promicro-4mod/](firmware/promicro-4mod/) |
| 3. Mapear MIDI no DAW | [docs/05-MIDI-DAW.md](docs/05-MIDI-DAW.md) |

## Documentação v0

| Documento | Conteúdo |
|-----------|----------|
| [Visão geral](docs/00-VISAO-GERAL.md) | Objetivos e decisões v0 |
| [Arquitetura](docs/01-ARQUITETURA-MODULAR.md) | Cabeça + 4 módulos em cadeia |
| [LEDs](docs/02-LEDS-E-OPTICA.md) | WS2812B RGB |
| [Eletrônica](docs/03-ELETRONICA.md) | Pro Micro, data, 5V |
| [Alimentação](docs/04-ALIMENTACAO.md) | Fonte 5V, limites |
| [MIDI / DAW](docs/05-MIDI-DAW.md) | CC RGB, notas, presets |
| [BOM](docs/06-BOM.md) | Lista de materiais v0 |
| [Cablagem](docs/07-CABLAGEM.md) | Fios por módulo |
| [XLR](docs/16-XLR-CONECTORES.md) | Pinagem 3 pinos — tubo + módulos |
| [**Cabeça Medusa**](docs/17-CABECA-MEDUSA.md) | Caixa Pro Micro + saídas XLR |
| [**Tubo flex**](docs/14-TUBO-FLEX.md) | Gradiente, chase, MIDI CC 15–19 |
| [**Compras AliExpress**](docs/15-ALIEXPRESS-BOM.md) | **O que buscar e o que evitar** |
| [Roadmap](docs/08-ROADMAP.md) | v0 atual → v1 futuro |
| [Resumo rápido](docs/DECISAO-RESUMO.md) | Decisões em 2 minutos |

## Decisões v0

| Tópico | Decisão |
|--------|---------|
| Cabeça | **1× Pro Micro** (ATmega32U4, MIDI USB) |
| Módulos | **4×** com **1 WS2812B** cada |
| Cor | **RGB completo** por módulo (CC 1–14) |
| Alimentação | **5 V** / ≥ 1 A |
| Dados spot | **D6** — cadeia 4 módulos |
| Tubo flex | **D5** — fita WS2812B (efeitos gradiente) |
| Cabos | 5V + GND + DATA (fios ou **XLR 3 pinos**) |

## MIDI rápido

| Módulo | R | G | B |
|--------|---|---|---|
| 1 | CC 1 | CC 2 | CC 3 |
| 2 | CC 4 | CC 5 | CC 6 |
| 3 | CC 9 | CC 10 | CC 11 |
| 4 | CC 12 | CC 13 | CC 14 |

Notas **C3–F3** = módulos 1–4 (velocity = brilho). **CC 7** = dimmer. **PC 0** = blackout.

## v1 (futuro)

Rig de palco 24V, LEDs 10W, ESP32, P4 + RJ45 — especificação em [docs/v1/](docs/v1/).
