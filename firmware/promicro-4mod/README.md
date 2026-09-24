# StageMod v0 — Firmware Pro Micro + 4× WS2812B

Firmware oficial da **v0**: **1 Pro Micro** e **4 LEDs WS2812B** (um por módulo), **RGB completo** via MIDI.

Documentação: [docs/](../../docs/) · MIDI: [05-MIDI-DAW.md](../../docs/05-MIDI-DAW.md) · Cablagem: [07-CABLAGEM.md](../../docs/07-CABLAGEM.md) · Cabeça: [17-CABECA-MEDUSA.md](../../docs/17-CABECA-MEDUSA.md)

## O que este firmware faz

- **MIDI USB** nativo do Pro Micro (ATmega32U4)
- **4 módulos** = 4 pixels numa cadeia WS2812B (data em série)
- **RGB completo** em cada módulo — qualquer cor via CC
- **Tubo flexível** (pin D5) — gradiente, chase, rainbow ([14-TUBO-FLEX.md](../../docs/14-TUBO-FLEX.md))
- Notas **C3–F3** acendem o módulo com a cor RGB já definida; **velocity** = brilho
- **PC 0–6** = presets de cor (blackout, warm, R, G, B, magenta, branco)
- **CC 7** = master dimmer

## Ligação elétrica

### Visão geral

```
[Fonte 5V] ──┬── VCC Pro Micro
             ├── VCC Mód 1 ── VCC Mód 2 ── VCC Mód 3 ── VCC Mód 4
             └── GND comum (Pro Micro + todos os módulos)

Pro Micro D6 ──► [470Ω] ──► DIN Mód1 ── ... ──► Mód4
Pro Micro D5 ──► [470Ω] ──► DIN fita WS2812B no tubo flexível
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

## Mapa MIDI — RGB por módulo

Cada módulo tem **3 CCs** (R, G, B). Valor 0–127 no DAW → 0–255 no LED.

| Módulo | Vermelho | Verde | Azul |
|--------|----------|-------|------|
| **1** | CC **1** | CC **2** | CC **3** |
| **2** | CC **4** | CC **5** | CC **6** |
| **3** | CC **9** | CC **10** | CC **11** |
| **4** | CC **12** | CC **13** | CC **14** |

| Entrada | Ação |
|---------|------|
| **CC 1–14** | Define cor RGB do módulo (efeito imediato) |
| Nota **60–63** (C3–F3) | Módulo 1–4 — acende com cor dos CCs; velocity = brilho |
| Nota off | Apaga o módulo |
| **CC 7** | Master dimmer (todos) |
| **PC 0** | Blackout |
| **PC 1** | Warm white (todos) |
| **PC 2** | Vermelho |
| **PC 3** | Verde |
| **PC 4** | Azul |
| **PC 5** | Magenta |
| **PC 6** | Branco |

### Exemplo no DAW

1. Enviar **CC 1 = 127, CC 2 = 0, CC 3 = 0** → módulo 1 fica vermelho.
2. **CC 2 = 127** → amarelo (R+G).
3. Nota **C3** com velocity 100 → módulo 1 com brilho ~80 %.

Qualquer combinação R+G+B = **milhões de cores** — é a vantagem do WS2812B.

## Teste sem DAW

Após upload, o boot pisca os 4 módulos em branco em sequência. Se não piscar:

1. Verificar ordem GRB no `COLOR_ORDER` (alguns clones usam RGB)
2. Trocar `LED_PIN`
3. Medir 5V no LED

## Próximo passo (firmware)

- [x] RGB completo por módulo (CC 1–14)
- [ ] Migrar Cabeça para ESP32-S3 + RS-485 (doc principal do repo)
- [ ] Trocar WS2812B por LEDs 10W quando hardware estiver pronto

## v1 (futuro)

Rig 24V / 10W / ESP32 — [docs/v1/](../../docs/v1/README.md). A v0 valida **MIDI → luz modular** antes dessa migração.
