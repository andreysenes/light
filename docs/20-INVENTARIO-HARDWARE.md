# Inventário — hardware em mãos (Andrey)

Estado do rig **v0** com o que já está comprado/montado.

## Já temos

| Item | Especificação | Firmware / notas |
|------|---------------|------------------|
| **Pro Micro** | 5 V, ATmega32U4 | Cabeça Medusa |
| **ZS-040** | BLE → Serial1 | [19-ZS-040.md](19-ZS-040.md) |
| **Fonte** | **5 V 10 A** | Dentro da Medusa + **C14** |
| **Módulos spot** | **4×** WS2812B, **8 LEDs** cada | **32 pixels** na cadeia D6 — MIDI ainda **4 módulos** lógicos (CC 1–14) |
| **Tubo** | **4 m** × **50 LED/m** = **200 LEDs** | D5, WS2811 — `NUM_TUBE_LEDS 200` |

### Cadeia de pixels (pin D6)

```
Medusa D6 ──► [Mod1: LED 0–7] ──► [Mod2: 8–15] ──► [Mod3: 16–23] ──► [Mod4: 24–31]
```

Cada módulo físico: **8 LEDs** em série internos; **DOUT** do módulo → **DIN** do próximo. No firmware, **um** CC RGB acende **os 8 LEDs** do módulo com a mesma cor.

### Tubo (pin D5)

| Campo | Valor |
|-------|--------|
| Comprimento | 4 m |
| Densidade | 50 LED/m |
| Total | **200** addressable |
| Chip | WS2811 (D15-Woven Magic) |

## Ainda falta

Lista de compras completa: **[21-LISTA-COMPRAS-RESTANTE.md](21-LISTA-COMPRAS-RESTANTE.md)**.

Resumo: caixa Medusa + **C14** + fusível + XLR (Medusa e módulos) + cabos + USB painel.  
**Montagem/soldagem:** [22-MANUAL-MONTAGEM.md](22-MANUAL-MONTAGEM.md).

## Corrente (referência)

| Carga | Nominal / pico |
|-------|----------------|
| 32 LEDs módulos (branco full) | ~**2 A** |
| Tubo 200 LED (manual 3,1 W/m) | ~**2,5 A** nominal |
| Pro Micro + ZS-040 | ~**0,15 A** |
| **Fonte 10 A** | Folga para efeitos e pico no tubo |

Injeção **5 V** no **meio** do tubo 4 m continua recomendada.

## Checklist primeiro power-on

1. [ ] `LEDS_PER_MODULE 8` e `NUM_TUBE_LEDS 200` no `.ino` (já padrão no repo)
2. [ ] Ligação 5V/GND/DATA conforme [22-MANUAL-MONTAGEM.md](22-MANUAL-MONTAGEM.md)
3. [ ] Ordem cadeia: Mod1 (C3) → Mod2 → Mod3 → Mod4 (F3)
4. [ ] Boot: cada módulo pisca **8 LEDs** juntos R/G/B/W; depois teste tubo
5. [ ] ZS-040 @ 115200 ou USB para MIDI

## Referências

- [07-CABLAGEM.md](07-CABLAGEM.md)
- [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md)
- [firmware/promicro-4mod/](../firmware/promicro-4mod/)
