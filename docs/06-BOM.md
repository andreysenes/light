# BOM — Lista de materiais (arquitetura v2)

Preços aproximados USD (AliExpress/LCSC). Brasil: FilipeFlop, Usinainfo.

## Kit protótipo — Cabeça + 1 módulo + cabos

| Qty | Item | Ref | ~US$ | Notas |
|-----|------|-----|------|-------|
| 1 | ESP32-S3 DevKit USB | | 6 | **Único ESP** |
| 2 | MAX485 / SP3485 | | 1,00 | Cabeça + módulo |
| 1 | ATtiny1614-SS | | 0,60 | Decoder módulo |
| 2 | LED 10 W warm white star | 3000 K | 1,60 | Canal A |
| 1 | LED 10 W red star | 620 nm | 0,80 | Canal B |
| 2 | Módulo buck CC 900 mA | PT4115/XL6001 | 2,00 | |
| 2 | IRLB8721 | TO-220 | 1,00 | Opcional |
| 1 | DIP-3 | | 0,15 | Endereço |
| 1 | Buck 24→5 V | Mini560 | 0,80 | Cabeça |
| 2 | Polyfuse 2 A | | 0,20 | |
| 1 | TVS SMBJ24A | | 0,15 | |
| 4 | Jack P4 fêmea painel | 5,5×2,1 mm | 0,40 | 2× módulo IN/OUT |
| 2 | Plug P4 macho | | 0,20 | Cabos energia |
| 2 | Jack RJ45 fêmea painel | | 0,40 | 2× módulo IN/OUT |
| 1 | Cabo 2× AWG18 0,5 m + P4 | | 0,50 | Patch energia |
| 1 | Patch Cat5e 0,5 m | | 0,40 | Patch dados |
| 2 | Lente PMMA 20 mm 90° | | 0,60 | |
| 2 | Holder lente 20 mm | | 0,40 | |
| 1 | Fonte 24 V 5 A com P4 | | 12 | |
| 1 | Heatsink Al 80 mm | | 4,00 | |
| 1 | Caixa ABS Cabeça | | 3,00 | |
| — | Misc | | 4 | |
| | **Total protótipo** | | **~41** | |

## Cabeça (Head Unit)

| Qty | Item | ~US$ |
|-----|------|------|
| 1 | ESP32-S3 DevKit | 6 |
| 1 | MAX485 | 0,50 |
| 1 | Buck 24→5 V | 0,80 |
| 1 | RJ45 fêmea | 0,20 |
| 1 | P4 fêmea (da fonte) | 0,10 |
| 1 | Caixa | 3,00 |
| | **Total** | **~11** |

## Módulo Dual — por unidade

| Qty | Item | ~US$ |
|-----|------|------|
| 1 | ATtiny1614 | 0,60 |
| 1 | MAX485 | 0,50 |
| 2 | Buck CC 900 mA | 2,00 |
| 2 | IRLB8721 (opcional) | 1,00 |
| 1 | LED 10 W WW | 0,80 |
| 1 | LED 10 W red | 0,80 |
| 2 | Lente 20 mm 90° + holder | 1,00 |
| 2 | P4 fêmea IN+OUT | 0,20 |
| 2 | RJ45 fêmea IN+OUT | 0,40 |
| 1 | Polyfuse + TVS | 0,25 |
| 1 | DIP-3 | 0,15 |
| 1 | Heatsink / carcaça Al | 4,00 |
| 1 | PCB | 2,00 |
| | **Por módulo** | **~14** |

## Cabos por salto (módulo → módulo)

| Item | ~US$ | Notas |
|------|------|-------|
| Patch P4 AWG18 0,5 m | 0,50 | Macho-macho |
| Patch Cat5e 0,5 m | 0,40 | RJ45 crimpado |
| **Total / salto** | **~0,90** | vs ~US$ 7 com GX16-5 |

## Sistema 8 módulos + Cabeça

| Categoria | ~US$ |
|-----------|------|
| Cabeça | 11 |
| 8× Módulo @ 14 | 112 |
| Fonte 24 V 10 A | 28 |
| Distro + fusíveis | 10 |
| 8× par cabos P4+Cat5e | 7 |
| Reserva 15 % | 25 |
| **Total** | **~193** |

## Estoque conectores (12 módulos)

| Item | Qty | ~US$ |
|------|-----|------|
| P4 fêmea painel | 30 | 3 |
| P4 macho | 20 | 2 |
| RJ45 fêmea painel | 30 | 6 |
| Patch Cat5e 0,5 m | 12 | 5 |
| Cabo AWG18 + P4 DIY | 12 | 6 |
| Lente 90° reserva | 4 | 1 |

## O que mudou vs cabo único GX16

| Removido | Substituído por |
|----------|-----------------|
| GX16-5 | P4 + RJ45 |
| Cabo 5 condutores | AWG18 + Cat5e |
| ~US$ 7/salto | **~US$ 0,90/salto** |

## Checklist antes de lote

- [ ] P4 centro + em todos os cabos
- [ ] RJ45 pin 4-5 pass-through IN→OUT
- [ ] 30 min térmico @ 100 % com lentes 90°
- [ ] RS-485 estável com 3 módulos em cadeia
