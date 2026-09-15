# BOM — Lista de materiais (arquitetura v2)

Preços aproximados USD (AliExpress/LCSC). Brasil: FilipeFlop, Usinainfo.

## Kit protótipo — Cabeça + 1 módulo + 1 cabo

| Qty | Item | Ref | ~US$ | Notas |
|-----|------|-----|------|-------|
| 1 | ESP32-S3 DevKit USB | | 6 | **Único ESP do sistema** |
| 2 | MAX485 / SP3485 | | 1,00 | Cabeça + módulo |
| 1 | ATtiny1614-SS | | 0,60 | Decoder módulo |
| 2 | LED 10 W warm white star | 3000 K | 1,60 | Soquete A padrão |
| 1 | LED 10 W red star | 620 nm | 0,80 | Soquete B padrão |
| 2 | Módulo buck CC 900 mA | PT4115/XL6001 | 2,00 | 1 por canal |
| 2 | IRLB8721 | TO-220 | 1,00 | Se PWM via EN |
| 1 | DIP-3 | | 0,15 | Endereço |
| 1 | Buck 24→5 V | Mini560 | 0,80 | Cabeça |
| 2 | Polyfuse 2 A | | 0,20 | |
| 1 | TVS SMBJ24A | | 0,15 | |
| 4 | GX16-5 conector | macho+fêmea ×2 | 8,00 | 1 cabo + IN/OUT módulo |
| 1 | Cabo 5 condutores 0,5 m | | 3,00 | Cabo StageMod patch |
| 1 | Fonte 24 V 5 A | | 12 | |
| 1 | Heatsink Al 80 mm | | 4,00 | Módulo |
| 1 | Caixa ABS Cabeça | | 3,00 | |
| — | Misc | | 5 | |
| | **Total protótipo** | | **~47** | |

## Cabeça (Head Unit) — unitário

| Qty | Item | ~US$ |
|-----|------|------|
| 1 | ESP32-S3 DevKit | 6 |
| 1 | MAX485 | 0,50 |
| 1 | Buck 24→5 V | 0,80 |
| 1 | GX16-5 OUT | 2,00 |
| 1 | Bornes ou GX16 IN (da fonte) | 2,00 |
| 1 | Caixa | 3,00 |
| | **Total** | **~14** |

## Módulo Dual — por unidade (produção)

| Qty | Item | ~US$ |
|-----|------|------|
| 1 | ATtiny1614 | 0,60 |
| 1 | MAX485 | 0,50 |
| 2 | Buck CC 900 mA | 2,00 |
| 2 | IRLB8721 (opcional) | 1,00 |
| 1 | LED 10 W WW | 0,80 |
| 1 | LED 10 W red | 0,80 |
| 1 | Polyfuse 2 A | 0,10 |
| 1 | TVS SMBJ24A | 0,15 |
| 2 | GX16-5 IN+OUT | 4,00 |
| 1 | DIP-3 | 0,15 |
| 1 | Heatsink / carcaça Al | 4,00 |
| 1 | PCB | 2,00 |
| | **Por módulo** | **~16** |

Sem ESP — **~US$ 1–2 mais barato** que versão anterior com ESP32-C3.

## Cabo StageMod — por unidade

| Tipo | Comprimento | ~US$ |
|------|-------------|------|
| Patch | 0,5 m | 4 |
| Patch | 1 m | 5 |
| Tronco | 2 m AWG16 V+ | 8 |
| Adaptador T | 1× IN, 2× OUT | 12 (DIY PCB) |

Ver [09-CABO-STAGEMOD.md](09-CABO-STAGEMOD.md).

## Sistema 8 módulos + Cabeça

| Categoria | ~US$ |
|-----------|------|
| Cabeça | 14 |
| 8× Módulo Dual @ 16 | 128 |
| Fonte 24 V 10 A | 28 |
| Distro + fusíveis | 12 |
| 9× cabo patch 0,5 m | 36 |
| 1× cabo tronco 2 m | 8 |
| Reserva LEDs/drivers 15 % | 25 |
| **Total** | **~250** |

## Estoque LEDs extras (configurável)

| LED 10 W | Qty sugerida | ~US$ |
|----------|--------------|------|
| Amber | 4 | 3 |
| Green | 4 | 3 |
| Cool white | 2 | 2 |

Para converter módulos WW+R → outras combinações.

## O que saiu da BOM (vs v1)

| Removido | Motivo |
|----------|--------|
| ESP32-C3 por módulo | Cabeça única |
| LED 3 W RGB | Agora 10 W dual |
| Conector 4 pin | Cabo StageMod 5 pin |

## Checklist antes de lote

- [ ] Cabeça + 1 módulo estável 30 min @ 100 % ambos canais
- [ ] Cabo StageMod patch testado com osciloscópio/logic (RS-485)
- [ ] Heatsink < 65 °C
- [ ] `modules.json` com 3 perfis diferentes testados no DAW
