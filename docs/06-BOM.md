# BOM — v0

Componentes para **4 módulos WS2812B + Pro Micro**.

## Lista principal

| Qty | Item | Ref / busca | ~US$ | Notas |
|-----|------|-------------|------|-------|
| 1 | Pro Micro 5V 16MHz | SparkFun / clone | 4–8 | Cabeça |
| 4 | WS2812B | breakout ou LED star | 0,40 | 1 por módulo |
| 1 | Fonte 5V ≥ 1A | USB charger / bench | 3–10 | Alimenta tudo |
| 1 | Resistor 470Ω | 1/4W | 0,05 | Linha data |
| 1 | Capacitor 470µF–1000µF | 6,3V+ | 0,20 | 1º módulo |
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
| 3 fios (5V, GND, DATA) | IN + OUT |

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
- [ ] Resistor 470Ω no data
- [ ] Capacitor no 1º LED
- [ ] Cadeia DIN→DOUT na ordem 1→2→3→4
- [ ] Boot pisca R,G,B,W nos 4 módulos

## v1 BOM

Rig 24V / 10W — [v1/README.md](v1/README.md).
