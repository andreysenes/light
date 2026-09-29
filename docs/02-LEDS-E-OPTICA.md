# LEDs — WS2812B RGB (v0)

## LED usado

| Item | Especificação |
|------|----------------|
| Tipo | **WS2812B** (ou WS2812B-B breakout) |
| Tensão | **5 V** |
| Cor | **RGB completo** — 8 bits por canal |
| Por módulo físico | **8× WS2812B** (mesma cor via MIDI) |
| Módulos lógicos (MIDI) | **4** |
| Total cadeia D6 | **32 pixels** |
| Tubo D5 | **200** LEDs (4 m × 50/m) |

## Por que WS2812B na v0

| Vantagem | Detalhe |
|----------|---------|
| RGB completo | Milhões de cores — sem misturar LEDs mono |
| 1 fio data | Cadeia simples entre módulos |
| Barato | Comum em estoque DIY |
| Integrado | Driver dentro do LED — sem MOSFET |

## Cor e brilho

| Controle MIDI | Efeito |
|---------------|--------|
| CC 1–14 | R, G, B por módulo (0–255) |
| CC 7 | Master dimmer (FastLED brightness) |
| Velocity (notas) | Escala RGB do módulo |
| PC presets | Cores pré-definidas em todos |

Não é necessário LED warm white separado — **R+G parcial** faz amarelo/laranja; **R+G+B** faz branco.

## Consumo

| Estado | Corrente por LED | 4 LEDs |
|--------|------------------|--------|
| Apagado | ~1 mA | ~4 mA |
| Cor média | ~20–40 mA | ~80–160 mA |
| Branco full | ~60 mA | **~2 A** (32 LEDs) + tubo à parte |

Fonte **5V / 1A** é suficiente com margem.

## Ordem de cores no firmware

```cpp
#define COLOR_ORDER GRB   // padrão WS2812B
```

Se as cores saírem trocadas (vermelho aparece verde), testar `RGB` ou `BGR` no `.ino`.

## Limitações vs. palco grande

| WS2812B v0 | LED 10W v1 (futuro) |
|------------|---------------------|
| ~0,3 W / LED | ~10–20 W / módulo |
| Luz de proximidade / efeito | Wash de palco |
| Sem lente dedicada | Lente 20mm 90° planejada |

Para wash de palco grande, evoluir para [v1](v1/README.md).

## Boot visual

Após upload, firmware pisca cada módulo: **vermelho → verde → azul → branco** — confirma ordem da cadeia e ordem GRB.
