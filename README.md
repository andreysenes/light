# StageMod — Iluminação de palco modular com ESP32 + MIDI

Sistema de módulos de luz acopláveis para palco/estúdio: **um único ESP32 como cabeça**, cabo proprietário **energia + dados**, módulos simples com **2× 10 W** por unidade (padrão warm white + vermelho), configuráveis no futuro para outras combinações de cores.

## Arquitetura em uma frase

```
DAW ──MIDI USB──► [Cabeça ESP32] ═══ Cabo StageMod (24V + RS-485) ═══ [Mod1]──[Mod2]──[Mod3]──...
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
| [**Cabo StageMod**](docs/09-CABO-STAGEMOD.md) | **5 condutores, GX16-5, pinagem** |
| [**Módulo Dual**](docs/10-MODULO-DUAL.md) | **2× 10 W, hardware universal** |
| [**Config módulos**](docs/11-CONFIGURACAO-MODULOS.md) | **WW+R, WW×2, R+amber, …** |
| [Resumo rápido](docs/DECISAO-RESUMO.md) | Decisões em 2 minutos |

## Decisões atuais

| Tópico | Decisão |
|--------|---------|
| Controle | **1× ESP32-S3** na Cabeça (MIDI USB → RS-485) |
| Módulo | **2 canais × 10 W** — padrão **warm white + vermelho** |
| MCU no módulo | **ATtiny** decoder (não ESP) |
| Cabo | **StageMod**: V+ 24 V, GND, D+, D−, shield — [especificação](docs/09-CABO-STAGEMOD.md) |
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

`═══` = Cabo StageMod (energia + dados no mesmo chicote).

## Próximo passo

1. Montar **Cabeça** (ESP32 + MAX485 + MIDI USB).
2. Montar **1 módulo Dual** (2× 10 W WW+R).
3. Fazer **1 cabo StageMod** patch 0,5 m (GX16-5).
4. Validar protocolo e dissipação térmica.

Ver [docs/08-ROADMAP.md](docs/08-ROADMAP.md).
