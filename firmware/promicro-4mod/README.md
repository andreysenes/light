# Protótipo v0 — Pro Micro + 4× WS2812B

Primeiro hardware do StageMod usando o que você já tem: **1 Pro Micro** e **4 LEDs WS2812B** (um por módulo).

## O que este firmware faz

- **MIDI USB** nativo do Pro Micro (ATmega32U4)
- **4 módulos** = 4 pixels numa cadeia WS2812B (data em série)
- Notas **C3–F3** (60–63) ligam/desligam cada módulo com velocity = brilho
- **PC 0** = blackout · **PC 1** = wash quente · **PC 2** = vermelho
- **CC 7** = master dimmer

## Ligação elétrica

### Visão geral

```
[Fonte 5V] ──┬── VCC Pro Micro
             ├── VCC Mód 1 ── VCC Mód 2 ── VCC Mód 3 ── VCC Mód 4
             └── GND comum (Pro Micro + todos os módulos)

Pro Micro D6 ──► [470Ω] ──► DIN Mód1 ── DOUT ──► DIN Mód2 ── ... ──► Mód4
```

### Por módulo (chicote simples)

| Fio | IN | No módulo | OUT |
|-----|-----|-----------|-----|
| Vermelho | 5V | → LED VCC | 5V pass-through |
| Preto | GND | → LED GND | GND pass-through |
| Branco/verde | DATA | → LED DIN | LED DOUT → próximo |

Cada módulo é só **1 WS2812B** + 3 fios de pass-through (energia) + data série.

### Pro Micro (5V, 16MHz)

| Pro Micro | Liga em |
|-----------|---------|
| **VCC** | 5V da fonte (ou USB só para programar — **não** alimentar 4 LEDs só no USB) |
| **GND** | GND comum |
| **D6** (ou `LED_PIN` no .ino) | Resistor 470Ω → DIN do módulo 1 |
| **RAW** | Opcional: 5V da fonte se não usar VCC |

### Boas práticas WS2812B

- Resistor **330–470 Ω** entre Pro Micro e primeiro DIN
- Capacitor **100–1000 µF** entre 5V e GND **no primeiro módulo**
- Fonte **5V / mín. 1 A** (4 LEDs × ~60 mA ≈ 240 mA no pior caso; use 1–2 A)
- Cabo de dados curto no protótipo (< 30 cm entre módulos)

## Arduino IDE — instalação

1. Placa: **Arduino Leonardo** ou **SparkFun Pro Micro** (5V, 16MHz)
2. Bibliotecas:
   - `MIDI Library` (FortySevenEffects)
   - `FastLED`
3. Abrir `promicro-4mod.ino` → Upload
4. No DAW: habilitar dispositivo MIDI USB do Pro Micro

### Pro Micro — pinagem comum

| Função | Pin |
|--------|-----|
| LED data (padrão) | **6** |
| Alternativa | 5, 7, 8, 9… (alterar `LED_PIN`) |

## Mapa MIDI

| Entrada | Ação |
|---------|------|
| Nota **60** (C3) | Módulo 1 — matiz fixo, velocity = brilho |
| Nota **61** (D3) | Módulo 2 |
| Nota **62** (E3) | Módulo 3 |
| Nota **63** (F3) | Módulo 4 |
| **CC 7** | Master dimmer (todos) |
| **PC 0** | Blackout |
| **PC 1** | Preset wash quente |
| **PC 2** | Preset vermelho |

## Teste sem DAW

Após upload, o boot pisca os 4 módulos em branco em sequência. Se não piscar:

1. Verificar ordem GRB no `COLOR_ORDER` (alguns clones usam RGB)
2. Trocar `LED_PIN`
3. Medir 5V no LED

## Próximo passo (firmware)

- [ ] CC 21/22/23 para RGB livre por módulo
- [ ] Migrar Cabeça para ESP32-S3 + RS-485 (doc principal do repo)
- [ ] Trocar WS2812B por LEDs 10W quando hardware estiver pronto

## Relação com o projeto completo

Este protótipo valida **MIDI → luz modular** antes do rig 24V / P4 / ATtiny. A lógica de `modules.json` e endereços do StageMod completo evolui deste mapeamento nota→módulo.
