# Guia de compras — AliExpress (StageMod v0)

Lista para montar o protótipo: **Pro Micro + 4 módulos WS2812B + tubo flexível + fonte 5V**.

Links de busca (cole no AliExpress se o link não abrir):

| # | Peça | Busca no AliExpress |
|---|------|---------------------|
| 1 | Pro Micro | `Pro Micro ATmega32U4 5V 16MHz` |
| 2 | WS2812B módulo (×4) | `WS2812B breakout board 5V DIN DOUT` |
| 3 | Tubo neon flex | `WS2812B neon tube 5V 1m silicone` |
| 4 | Fita WS2812B (opcional) | `WS2812B LED strip 5V 60LED/m 1m` |
| 5 | Fonte 5V 3A | `5V 3A power supply DC adapter` |
| 6 | Resistor 470Ω | `470 ohm resistor 1/4W 100pcs` |
| 7 | Capacitor 1000µF | `1000uf 16V electrolytic capacitor` |
| 8 | Fio silicone | `silicone wire 22AWG red black green` |
| 9 | JST 3 pin (opcional) | `JST SM 3 pin connector cable` |
| 10 | Borne / terminal (opcional) | `DC barrel 5.5x2.1 female panel mount` |

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
- Mais barato se já vai comprar fita para o tubo

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

### O que buscar — tubo pronto (mais fácil)

```
WS2812B neon LED tube 5V 1m silicone IP67
```

ou

```
BTF-LIGHTING neon tube WS2812B 5V
```

### Filtros críticos

| Campo | Valor |
|-------|-------|
| Voltagem | **DC 5V** (não 12V) |
| Chip / IC | **WS2812B** (ou WS2812) |
| Comprimento | **0,5 m** ou **1 m** para protótipo |
| LEDs/m | **60** ou **30** (anotar para `NUM_TUBE_LEDS`) |

### Calcular `NUM_TUBE_LEDS`

| Comprimento | 60 LED/m | 30 LED/m |
|-------------|----------|----------|
| 0,5 m | **30** | 15 |
| 1 m | **60** | 30 |

### Loja recomendada para tubo/fita

**BTF-LIGHTING Official Store** — muitos anúncios de neon flex 5V WS2812B; leia comentários com foto.

### Opção DIY (mais barato)

1. Comprar fita `WS2812B 5V 60LED/m 1m` (~US$ 3)
2. Comprar `silicone neon tube 10mm LED strip diffuser` (~US$ 2–5)
3. Deslizar a fita dentro do tubo

### Evitar

- Tubo **12V** ou **24V**
- Anúncio só “RGB LED tube” **sem** WS2812 / addressable
- Kit com controlador IR só — você usa o Pro Micro, não precisa do controle remoto (mas o tubo sozinho basta)

### Preço referência

| Item | ~US$ |
|------|------|
| Tubo neon 1 m 5V WS2812B | 8–15 |
| Fita + tubo silicone separados | 5–10 |

---

## 4. Fonte 5V — obrigatório

### O que buscar

```
5V 3A power adapter DC switching supply
```

ou

```
5V 3000mA power supply 5.5x2.1mm
```

### Filtros

| Campo | Valor |
|-------|-------|
| Saída | **5V DC** |
| Corrente | **≥ 3A** (com tubo + 4 módulos) |
| Conector | P4 **5.5×2.1 mm** (comum) |

Só 4 módulos sem tubo: **1A** basta.

### Evitar

- Fonte genérica “5V” sem amperagem na etiqueta
- USB charger de celular fraco (500 mA) para rig completo

### Preço referência

| Amperagem | ~US$ |
|-----------|------|
| 5V 1A | 2–4 |
| 5V 3A | 4–8 |

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
| 3 | Tubo neon WS2812B **5V** 0,5–1 m | 1 | 10 |
| 4 | Fonte 5V **3A** | 1 | 6 |
| 5 | Resistor 470Ω | 5+ | 1 |
| 6 | Capacitor 1000µF 16V | 2 | 1 |
| 7 | Fio silicone 22AWG | 1 kit | 3 |
| | **Total estimado** | | **~25–30** |

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

- [ ] Etiqueta ou anúncio diz **5V** e **WS2812B**
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
4. Fonte 5V 3A alimentando tudo (GND comum)

Firmware: [firmware/promicro-4mod/](../firmware/promicro-4mod/)

---

## v1 (futuro — não comprar ainda para v0)

ESP32-S3, fonte 24V, P4, RJ45, LEDs 10W — [v1/README.md](v1/README.md)
