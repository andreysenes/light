# StageMod — Iluminação de palco modular com ESP32 + MIDI

Sistema de módulos de luz acopláveis para palco/estúdio: **um único ESP32 como cabeça**, cabo proprietário **energia + dados**, módulos simples com **2× 10 W** por unidade (padrão warm white + vermelho), configuráveis no futuro para outras combinações de cores.

## Arquitetura em uma frase

```
DAW ──MIDI USB──► [Cabeça ESP32] ── P4 (24V) + RJ45 (dados) ── [Mod1]──[Mod2]──[Mod3]──...
```

Cada módulo é **só luz** (drivers + decoder). Não há ESP nos módulos.

## Documentação

| Documento | Conteúdo |
|-----------|----------|
| [Visão geral](docs/00-VISAO-GERAL.md) | Objetivos e decisões atuais |
| [Arquitetura](docs/01-ARQUITETURA-MODULAR.md) | Cabeça única, barramento, splits |
| [LEDs](docs/02-LEDS-E-OPTICA.md) | 10 W mono, WW + vermelho |
| [Eletrônica](docs/03-ELETRONICA.md) | Drivers, MOSFET, decoder ATtiny |
| [Alimentação](docs/04-ALIMENTACAO.md) | 24 V, injeção, fusíveis |
| [MIDI / DAW](docs/05-MIDI-DAW.md) | Mapeamento e protocolo |
| [BOM](docs/06-BOM.md) | Lista de materiais |
| [Topologia](docs/07-TOPOLOGIA-CABEAMENTO.md) | Daisy-chain e splits |
| [Roadmap](docs/08-ROADMAP.md) | Próximos passos |
| [**Cablagem**](docs/09-CABLAGEM.md) | **P4 energia + RJ45 dados (Cat5e)** |
| [**Módulo Dual**](docs/10-MODULO-DUAL.md) | **2× 10 W, hardware universal** |
| [**Config módulos**](docs/11-CONFIGURACAO-MODULOS.md) | **WW+R, WW×2, R+amber, …** |
| [**Lente 20 mm**](docs/12-LENTE-20MM.md) | **1 lente por LED, feixe 90°** |
| [Resumo rápido](docs/DECISAO-RESUMO.md) | Decisões em 2 minutos |

## Decisões atuais

| Tópico | Decisão |
|--------|---------|
| Controle | **1× ESP32-S3** na Cabeça (MIDI USB → RS-485) |
| Módulo | **2 canais × 10 W** — padrão **warm white + vermelho** |
| Óptica | **Lente PMMA 20 mm** (90°) — **1 por LED** |
| MCU no módulo | **ATtiny** decoder (não ESP) |
| Cabos | **P4** (24 V) + **RJ45/Cat5e** (RS-485) — [especificação](docs/09-CABLAGEM.md) |
| Proteção P4 | **P-MOS anti-reverso** em cada entrada de energia |
| Config futura | Mesma PCB; trocar LED + `modules.json` na Cabeça |
| Fonte | 24 V central, dimensionada pelo número de módulos |

## Topologia

```
[Fonte 24V]──►[Cabeça ESP32]═══╡ Mod 1 ╞═══╡ Mod 2 ╞═══╡ Mod 3 ╞═══╡ Mod 4 ╞═══
                                    │                    │
                                    ╞══ Mod 5    Mod 6 ╞═╡
                                    ╞══ Mod 7    Mod 8 ╞═╡
                                    └── Mod 9 ── Mod 10 ── ...
```

Cada salto = **2 cabos baratos**: P4 (energia) + patch rede (dados).

## Próximo passo

1. Montar **Cabeça** (ESP32 + MAX485 + MIDI USB).
2. Montar **1 módulo Dual** (2× 10 W WW+R).
3. Fazer **1 par de cabos** patch: P4 + Cat5e 0,5 m.
4. Validar protocolo e dissipação térmica.

Ver [docs/08-ROADMAP.md](docs/08-ROADMAP.md).
