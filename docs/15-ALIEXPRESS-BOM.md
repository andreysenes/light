# Guia de compras — AliExpress (StageMod v0)

Lista para montar o protótipo: **Pro Micro + 4 módulos WS2812B + tubo flexível + fonte 5V** + caixa [**Medusa**](17-CABECA-MEDUSA.md).

Links de busca (cole no AliExpress se o link não abrir):

| # | Peça | Busca no AliExpress |
|---|------|---------------------|
| 1 | Pro Micro | `Pro Micro ATmega32U4 5V 16MHz` |
| 2 | WS2812B módulo (×4) | `WS2812B breakout board 5V DIN DOUT` |
| 3 | Tubo neon flex | `WS2812B neon tube 5V silicone` (já é fita addressable dentro do silicone) |
| 4 | Fonte 5V 10A | `5V 10A power supply SMPS switching` |
| 5 | Resistor 470Ω | `470 ohm resistor 1/4W 100pcs` |
| 6 | Capacitor 1000µF | `1000uf 16V electrolytic capacitor` |
| 7 | Fio silicone | `silicone wire 22AWG red black green` |
| 8 | XLR fêmea painel ×3 (Medusa MOD/TUBO/INJ) | `XLR female 3 pin panel mount` |
| 9 | XLR macho painel ×4 (módulos OUT) + fêmea IN | `XLR male 3 pin panel mount` |
| 10 | Caixa ABS + bornes | `ABS project box` + `terminal block 2 pin` |
| 11 | JST 3 pin (opcional) | `JST SM 3 pin connector cable` |

---

## 1. Pro Micro (cabeça) — obrigatório

### O que buscar

```
Pro Micro ATmega32U4 5V 16MHz bootloader
```

### Filtros no anúncio

| Campo | Valor correto |
|-------|----------------|
| Chip | **ATmega32U4** (não ATmega328P = Pro Mini errado) |
| Voltagem | **5V** / 16MHz |
| USB | Micro-USB ou USB-C (tanto faz) |
| Bootloader | Com bootloader Arduino / Caterina |

### Evitar

- **Pro Mini** — não tem USB nativo, não serve para MIDI USB fácil
- **3.3V / 8MHz** — incompatível com WS2812B em 5V
- Placa sem foto do chip legível

### Preço referência

| Qty | ~US$ |
|-----|------|
| 1 | 3–6 |
| 2 (reserva) | 6–10 |

### Lojas com boa reputação (buscar pelo nome)

- Estardyn Official Store
- Worldchips
- HiLetgo (também vende no Ali)

### Arduino IDE

Placa: **Arduino Leonardo** ou **SparkFun Pro Micro**

---

## 2. WS2812B — 4 módulos spot

### Opção A — Breakout com PCB (recomendado)

```
WS2812B breakout 5V addressable LED module DIN DOUT
```

Ou:

```
10pcs WS2812B mini PCB board 5V 5050
```

| Verificar na foto | |
|-------------------|---|
| 4 pinos | **5V, GND, DIN, DOUT** |
| Chip | WS2812B (não só WS2812 antigo) |
| Tensão | **5V** |

Pacote **10 peças** costuma sair ~US$ 1–3 — sobram para reserva.

### Opção B — Fita e cortar 4 pedaços

```
WS2812B LED strip 5V 60LED/m IP30 1 meter
```

- Cortar **4 LEDs** com tesoura nas linhas de corte
- Soldar fios em 5V / GND / DIN / DOUT de cada pedaço
- Alternativa barata se não quiser breakout com PCB

### Evitar

- WS2811 só (protocolo diferente no firmware)
- **12V** strip
- LED “RGB” comum **sem** chip integrado (não é addressable)

### Preço referência

| Item | ~US$ |
|------|------|
| 10× breakout | 1–4 |
| 1 m fita 60LED/m | 2–5 |

---

## 3. Tubo flexível neon (gradiente / chase)

O tubo neon **já inclui** a fita addressable dentro do silicone — **não precisa comprar fita separada**.

### O que buscar — tubo pronto

```
WS2812B neon LED tube 5V silicone IP67
```

Modelo do projeto: **D15-Woven Magic** (WS2811, 50 LED/m) — [detalhes](14-TUBO-FLEX.md#tubo-comprado-4-m--manual-d15-woven-magic).

### Filtros críticos

| Campo | Valor |
|-------|-------|
| Voltagem | **DC 5V** (não 12V) |
| Chip / IC | **WS2811** ou WS2812B (addressable) |
| LEDs/m | Anotar para `NUM_TUBE_LEDS` (ex.: **50** = 200 LEDs em 4 m) |

### Evitar

- Tubo **12V** ou **24V**
- Anúncio só “RGB LED tube” **sem** WS2812 / addressable
- Kit com controlador IR só — você usa o Pro Micro, não precisa do controle remoto (mas o tubo sozinho basta)

### Preço referência

| Item | ~US$ |
|------|------|
| Tubo neon 4 m 5V addressable | 15–40 |

---

## 4. Fonte 5V — obrigatório

### O que buscar

```
5V 10A power supply SMPS switching
```

### Filtros

| Campo | Valor |
|-------|-------|
| Saída | **5V DC** |
| Corrente | **≥ 5A** (tubo 4 m); **10A** recomendado |
| Entrada | **100–240V** (bivolt) |

Só 4 módulos sem tubo: **1A** basta.

### Evitar

- Fonte genérica “5V” sem amperagem na etiqueta
- USB charger de celular fraco (500 mA) para rig completo

### Preço referência

| Amperagem | ~US$ |
|-----------|------|
| 5V 1A | 2–4 |
| 5V 5A | 6–10 |
| 5V 10A | 10–18 |

---

## 5. Componentes passivos — obrigatório

### Resistor 470Ω (linha de data)

```
470 ohm resistor kit 1/4W
```

Mínimo **2 unidades** (D5 tubo + D6 módulos). Kit 100 pcs ~US$ 1.

### Capacitor eletrolítico 1000µF

```
1000uf 16V electrolytic capacitor
```

| Verificar | |
|-----------|---|
| Tensão | **≥ 10V** (16V comum) |
| Qty | 1–2 (um no tubo, um nos módulos) |

~US$ 0.50–2 (kit).

---

## 6. Fios e conectores — recomendado

### Fio silicone 22 AWG

```
silicone wire 22AWG 5 colors
```

| Cor sugerida | Uso |
|--------------|-----|
| Vermelho | 5V |
| Preto | GND |
| Verde/branco | DATA |

### JST 3 pinos (opcional, facilita desmontar módulos)

```
JST SM 3 pin connector male female cable
```

### Mini interruptor (opcional)

```
mini rocker switch 5x8mm 2 pin
```

Na linha 5V da fonte.

---

## Lista de compras mínima

| # | Item | Qty | ~US$ |
|---|------|-----|------|
| 1 | Pro Micro 5V 32U4 | 1–2 | 4 |
| 2 | WS2812B breakout ou 10pcs mini PCB | 4–10 | 2 |
| 3 | Tubo neon **5V** addressable (ex. 4 m D15) | 1 | — (já tem) |
| 4 | Fonte 5V **10A** | 1 | 12 |
| 5 | Resistor 470Ω | 5+ | 1 |
| 6 | Capacitor 1000µF 16V | 2 | 1 |
| 7 | Fio silicone 22AWG | 1 kit | 3 |
| | **Total estimado** (sem tubo/Pro Micro/LEDs) | | **~15–20** |

Envio Brasil: +US$ 0–15 dependendo do vendedor e promo “Choice” / “AliExpress Standard”.

---

## Checklist ao receber

### Pro Micro

- [ ] Chip marcado **ATmega32U4**
- [ ] Liga no USB; Arduino IDE reconhece porta COM
- [ ] Upload de sketch de teste OK

### WS2812B

- [ ] 4 pinos: 5V, GND, DIN, DOUT
- [ ] Acende com teste FastLED em um LED

### Tubo

- [ ] Etiqueta diz **5V** e chip addressable (**WS2811** no D15)
- [ ] Contar LEDs ou medir: atualizar `NUM_TUBE_LEDS` no `.ino`
- [ ] Teste com PC 7 (gradient wave)

### Fonte

- [ ] Multímetro: saída **5,0–5,2 V**
- [ ] Polaridade P4: **centro = +**

---

## Ordem de montagem sugerida

1. Pro Micro + **1** WS2812B (teste pin D6)
2. Adicionar módulos 2–4 em cadeia
3. Ligar tubo no **D5**; ajustar `NUM_TUBE_LEDS`
4. Fonte 5V 10A alimentando tudo (GND comum; injeção 5V no meio do tubo 4 m)

Firmware: [firmware/promicro-4mod/](../firmware/promicro-4mod/)

---

## v1 (futuro — não comprar ainda para v0)

ESP32-S3, fonte 24V, P4, RJ45, LEDs 10W — [v1/README.md](v1/README.md)
