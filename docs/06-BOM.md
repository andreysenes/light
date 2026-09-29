# BOM — v0

Componentes para **4 módulos WS2812B + Pro Micro**.

## Lista principal

| Qty | Item | Ref / busca | ~US$ | Notas |
|-----|------|-------------|------|-------|
| 1 | Pro Micro 5V 16MHz | SparkFun / clone | 4–8 | Cabeça |
| 4 | WS2812B | breakout ou LED star | 0,40 | 1 por módulo |
| 1 | Fonte 5V ≥ 1A | USB charger / bench | 3–10 | Alimenta tudo |
| 6 | Resistor 470Ω | 1/4W | 0,30 | 4× módulos + 2× Medusa (D5/D6) |
| 5 | Capacitor 470µF–1000µF | 6,3V+ | 1,00 | 4× módulos + 1× Medusa |
| — | Fio silicone AWG22–24 | vermelho/preto/verde | 2 | Entre módulos |
| 1 | Cabo USB micro | — | — | Programar |
| | **Total** | | **~10–15** | |

## Opcional

| Item | Uso |
|------|-----|
| PCB perfurada | Fixar LEDs por módulo |
| Conector 3 pinos JST | Desmontagem rápida entre módulos |
| Caixa ABS pequena | Cabeça (Pro Micro) |

## Por módulo (DIY)

| Item | Qty |
|------|-----|
| WS2812B | 1 |
| Resistor **470Ω** | 1 (DATA IN → DIN) |
| Capacitor **470µF–1000µF** | 1 (5V/GND no LED) |
| XLR IN + OUT (opc.) | 1 par |
| 3 fios (5V, GND, DATA) | pass-through + data série |

## O que não precisa na v0

| Item v1 | Motivo |
|---------|--------|
| ESP32 | Pro Micro basta |
| MAX485 / RJ45 | Cadeia WS2812 |
| P4 / 24V | LEDs são 5V |
| MOSFET / driver CC | Integrado no WS2812 |
| Lente 20mm | v1 |
| ATtiny | Sem MCU no módulo |

## Checklist antes de ligar

- [ ] 5V e GND corretos (nunca 24V)
- [ ] **470 Ω** no DATA IN de **cada** módulo (+ Medusa D5/D6)
- [ ] **Cap** 5V/GND em **cada** módulo (+ Medusa)
- [ ] Cadeia DIN→DOUT na ordem 1→2→3→4
- [ ] Boot pisca R,G,B,W nos 4 módulos

## Onde comprar

Guia detalhado com buscas no AliExpress: **[15-ALIEXPRESS-BOM.md](15-ALIEXPRESS-BOM.md)**

## v1 BOM

Rig 24V / 10W — [v1/README.md](v1/README.md).
