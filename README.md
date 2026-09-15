# StageMod — Iluminação de palco modular com ESP32 + MIDI

Sistema de módulos de luz acopláveis para palco/estúdio, controlados por DAW via MIDI (USB ou Wi‑Fi), com alimentação centralizada em 24 V e LEDs de alta potência por canal (R, G, B).

## O que é este repositório

Nesta fase o foco é **esboço de arquitetura e escolha de peças** — não firmware final nem PCB fabricada. A documentação em `docs/` cobre:

| Documento | Conteúdo |
|-----------|----------|
| [Visão geral](docs/00-VISAO-GERAL.md) | Objetivos, decisões principais, glossário |
| [Arquitetura modular](docs/01-ARQUITETURA-MODULAR.md) | Master, satélites, barramento RS-485 |
| [LEDs e óptica](docs/02-LEDS-E-OPTICA.md) | 3× mono vs RGB integrado, branco, potência |
| [Eletrônica](docs/03-ELETRONICA.md) | MOSFET, drivers CC, referência ao vídeo |
| [Alimentação](docs/04-ALIMENTACAO.md) | 24 V, injeção, fusíveis, PSU |
| [MIDI / DAW](docs/05-MIDI-DAW.md) | Mapeamento, protocolo, software |
| [BOM](docs/06-BOM.md) | Lista de materiais com alternativas |
| [Topologia](docs/07-TOPOLOGIA-CABEAMENTO.md) | Daisy-chain, split em T, cabos |
| [Roadmap](docs/08-ROADMAP.md) | Próximos passos até protótipo |

## Decisão rápida (resumo)

| Tópico | Recomendação inicial |
|--------|----------------------|
| LED | **3× LED 3 W mono** (R, G, B) em star PCB — mais barato e flexível que RGB 10 W |
| Branco | Mistura RGB + canal **WW 3 W** opcional no módulo “spot” |
| Driver | **MOSFET logic-level** (IRLB8721) + limitação de corrente (PT4115 ou resistor calculado) |
| MCU | **1× ESP32-S3** (master MIDI) + **ESP32-C3** por módulo satélite |
| Barramento | **RS-485** (4 fios: V+, GND, A, B) — passa por todos os módulos |
| Tensão do barramento | **24 V DC** — menos queda de tensão em correntes longas |
| Alimentação | Fonte chaveada **24 V / 10–20 A** (Mean Well ou similar) + fusível geral |

## Topologia (exemplo)

```
[Fonte 24V]──►[Master + Mód 1]──►[Mód 2]──►[Mód 3]──►[Mód 4]
                    │
                    ├──►[Mód 5]     [Mód 6]
                    ├──►[Mód 7]     [Mód 8]
                    └──►[Mód 9]──►[Mód 10]──►...
```

Cada módulo tem conector **IN** e **OUT** (energia + dados). Splits em T usam cabo de derivação ou PCB com 2× OUT.

## Referência citada

O vídeo [ESP + MOSFET para LED de uma cor](https://www.youtube.com/watch?v=HSeckw3VLy8) mostra o princípio correto (GPIO → MOSFET → LED), mas **não escala** para watts de palco alimentando pelo regulador do ESP. Este projeto usa **fonte externa 24 V** e o mesmo princípio de chaveamento por MOSFET em cada canal.

## Próximo passo sugerido

1. Montar **1 módulo único** (breadboard) com 3× LED 3 W + 3× MOSFET + ESP32.
2. Validar MIDI USB no DAW (Reaper, Ableton, etc.).
3. Só então desenhar PCB e cabo de acoplamento.

Veja [docs/08-ROADMAP.md](docs/08-ROADMAP.md) para o plano completo.
