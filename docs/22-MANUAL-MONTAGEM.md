# Manual de montagem e soldagem — StageMod v0

Guia passo a passo para montar **Medusa** (Pro Micro + ZS-040 + fonte), **4 módulos** (8× WS2812B cada) e **tubo 4 m**.  

Este manual usa ligação **direta** de fios (5 V, GND, DATA) — **sem resistor nem capacitor** no texto de montagem.

| Referência | Documento |
|------------|-----------|
| Pinagem XLR | [16-XLR-CONECTORES.md](16-XLR-CONECTORES.md) |
| ZS-040 | [19-ZS-040.md](19-ZS-040.md) |
| Firmware | [firmware/promicro-4mod/](../firmware/promicro-4mod/) |
| O que já temos | [20-INVENTARIO-HARDWARE.md](20-INVENTARIO-HARDWARE.md) |

---

## 1. Ferramentas

| Ferramenta | Uso |
|------------|-----|
| Ferro de solda **25–60 W**, ponta fina | Conectores, fios, pads |
| Estanho com fluxo | Ligações |
| Alicate de corte / decapador AWG 18–22 | Cabos |
| Multímetro | Continuidade, 5 V, polaridade |
| Chave fenda / furadeira | Painel (C14, XLR, USB) |
| Estilete, fita, etiquetas | Identificar cabos `MOD`, `TUBO`, `DATA` |

EPI: óculos, local ventilado. Para a parte **127/220 V**, tomada **desligada** e caixa **aberta** só até testar o DC.

---

## 2. Convenções de fio e XLR

### Cores sugeridas

| Cor | Sinal |
|-----|--------|
| Vermelho | **+5 V** |
| Preto | **GND** |
| Verde ou branco | **DATA** |

### XLR 3 pinos (todos os cabos do projeto)

| Pino | Sinal |
|------|--------|
| **1** | GND (ligar **shell** do conector ao GND) |
| **2** | +5 V |
| **3** | DATA |

Etiqueta nos cabos: **`5V PIXEL — NÃO É ÁUDIO`**.

### Pro Micro (pinos úteis)

| Pro Micro | Função |
|-----------|--------|
| **VCC** | +5 V |
| **GND** | Terra |
| **D6** | DATA → cadeia dos **módulos** |
| **D5** | DATA → **tubo** |
| **D0 (RX)** | ← TX do ZS-040 |
| **D1 (TX)** | → RX do ZS-040 |
| **USB** | Programação + MIDI com cabo |

---

## 3. Ordem geral de montagem

```
1. Upload firmware no Pro Micro (USB no PC)
2. Configurar ZS-040 (AT, parear BT)
3. Montar 1 módulo spot → testar com Medusa em bancada (fonte 5 V, sem caixa)
4. Montar módulos 2–4 em cadeia
5. Montar Medusa (DC: Pro Micro, ZS-040, XLR, barramento 5 V)
6. Montar Medusa (AC: C14 + fusível + fonte SMPS)
7. Ligar tubo no XLR TUBO
8. Teste completo MIDI + boot
```

---

## 4. Módulo spot (repetir ×4, etiquetar MOD 1…4)

Cada módulo físico tem **8 LEDs WS2812B** em **série**. No MIDI, um módulo = **um** bloco de 8 LEDs com a **mesma cor**.

### 4.1 Conectores

| Lado | Conector painel |
|------|-----------------|
| **IN** | XLR **fêmea** |
| **OUT** | XLR **macho** |

### 4.2 Esquema interno (soldagem)

```
  XLR IN (F)                         8× WS2812B em cadeia          XLR OUT (M)
  Pin 1 GND ────────┬── GND dos LEDs ─────────────────────────── Pin 1 GND
  Pin 2 5V  ────────┬── 5V dos LEDs ─────────────────────────── Pin 2 5V
  Pin 3 DATA ───────┼──► DIN (LED 1) … LED 8 DOUT ────────────── Pin 3 DATA
```

Passos:

1. Soldar **trilha 5 V** e **trilha GND** (fio ou PCB) passando pelo módulo.
2. Ligar **5V** e **GND** de **cada** LED às trilhas (respeitar polaridade do breakout).
3. **DIN** do 1º LED no **pino 3** do XLR **IN**.
4. Encadear **DOUT → DIN** entre os 8 LEDs (ordem da seta no PCB da fita, se houver).
5. **DOUT** do 8º LED no **pino 3** do XLR **OUT**.
6. Ligar **pinos 1 e 2** do IN aos **pinos 1 e 2** do OUT (pass-through).
7. Soldar **shell** dos XLR ao **GND**.

### 4.3 Ordem na cadeia do palco

| Etiqueta | Pixels no firmware | Nota MIDI |
|----------|-------------------|-----------|
| **MOD 1** | 0–7 | C3 |
| **MOD 2** | 8–15 | D3 |
| **MOD 3** | 16–23 | E3 |
| **MOD 4** | 24–31 | F3 |

**DATA** nunca em paralelo: só **IN → OUT → IN** entre módulos.

---

## 5. Medusa — baixa tensão (sem ligar na rede ainda)

### 5.1 Fixação mecânica

1. Furar painel: **C14**, **USB micro**, XLR **MOD**, XLR **TUBO** (e **INJ** se usar).
2. Parafusar conectores; fixar **fonte SMPS** e **Pro Micro** com espaçadores (não encostar fundo metálico sem isolamento).

### 5.2 Barramento 5 V / GND

1. Da saída **+V / −V** da fonte SMPS, levar fio **AWG 18** vermelho e preto para um ponto de distribuição na caixa.
2. Derivar **+5 V** e **GND** para:
   - **VCC** e **GND** do Pro Micro
   - **VCC** e **GND** do ZS-040 (5 V no breakout, se aplicável)
   - **Pino 2** e **pino 1** de cada XLR (MOD, TUBO, INJ)
3. Unir todos os **shells** XLR ao **GND**.

### 5.3 Pro Micro ↔ ZS-040

| De | Para |
|----|------|
| ZS-040 **TX** | Pro Micro **D0 (RX)** |
| ZS-040 **RX** | Pro Micro **D1 (TX)** — se o módulo for 3,3 V lógica, usar adaptação de nível conforme [19-ZS-040.md](19-ZS-040.md) |
| **GND** comum | |

Configurar **AT+BAUD4** (115200) no ZS-040 antes de fechar a caixa.

### 5.4 Pro Micro → XLR

| Pro Micro | XLR painel | Pino |
|-----------|------------|------|
| **D6** | **MOD** | **3** (DATA) |
| **D5** | **TUBO** | **3** (DATA) |
| **GND** | MOD, TUBO | **1** |
| *(barramento)* | MOD, TUBO | **2** (+5 V) |

Soldar fios **curtos** (AWG 22) entre pads do Pro Micro e terminais traseiros dos XLR.

### 5.5 Teste em bancada (só 5 V DC)

**Não** plugar C13 na parede ainda — alimentar a fonte SMPS só se já tiver **AC** montado **e** tiver conferido isolamento; para primeiro teste, pode usar a mesma fonte 5 V 10 A com bornes em bancada.

1. Upload `promicro-4mod.ino` (USB).
2. Ligar **só MOD 1** no XLR MOD.
3. Boot: os **8 LEDs** do módulo 1 devem piscar R, G, B, W em sequência.

---

## 6. Medusa — entrada AC (C14)

**Somente** com caixa desenergizada e fios AC isolados.

1. **C14** → fonte SMPS:
   - **⏚** C14 → **FG** da fonte
   - **N** → **N**
   - **L** → **fusível 2 A** → **L** da fonte
2. Conferir com multímetro: **sem curto** entre L e N, entre L e ⏚.
3. Fechar tampa; etiquetar **127/220 V**.

Primeira energização: sem cabos XLR nos módulos, medir **5,0–5,2 V** no barramento.

---

## 7. Cabos XLR (tentáculos)

Montar ou comprar cabos com a **mesma pinagem** (1=GND, 2=5V, 3=DATA).

| Cabo | De | Para | Comprimento típico |
|------|-----|------|---------------------|
| A | Medusa **MOD** | MOD 1 **IN** | 1–2 m |
| B | MOD 1 **OUT** | MOD 2 **IN** | 0,3–1 m |
| C | MOD 2 **OUT** | MOD 3 **IN** | … |
| D | MOD 3 **OUT** | MOD 4 **IN** | … |
| E | Medusa **TUBO** | XLR do **tubo** | 3–5 m |

**Tubo (4 m, 200 LED):** fio **vermelho** = 5 V, **do meio** = DATA (WS2811), **externo** = GND — conforme manual do tubo D15; ligar ao XLR com a mesma convenção 1/2/3.

Opcional: segundo par 5 V/GND no **meio** do tubo (emenda) para evitar queda de tensão no fim dos 4 m.

---

## 8. Ligação completa

```
[C13 rede] → C14 → SMPS 5V10A
                    ├─ Pro Micro + ZS-040
                    ├─ XLR MOD ──cabo──► MOD1 ⇄ MOD2 ⇄ MOD3 ⇄ MOD4
                    └─ XLR TUBO ──cabo──► Tubo 4m (200 LED)

DAW → Bluetooth → ZS-040 → Serial1
   ou USB → Pro Micro
```

---

## 9. Testes finais

| # | Teste | Esperado |
|---|--------|----------|
| 1 | Boot sem MIDI | 4 módulos: 8 LEDs cada, cores R/G/B/W; depois animação curta no tubo |
| 2 | CC1–3 | MOD 1 muda cor (8 LEDs juntos) |
| 3 | Notas C3–F3 | Módulos 1–4 com velocity |
| 4 | PC 7 | Gradient wave no tubo |
| 5 | BT vs USB | Um caminho MIDI por vez na DAW |

Brilho alto no início: usar **CC 7** (master dimmer) ~30–40%.

---

## 10. Soldagem — boas práticas

- Aquecer **metal + fio**, depois estanho; evitar bola seca em plástico do XLR.
- Tracionar levemente o fio após soldar no pino XLR (teste de fixação).
- Não aquecer o **Pro Micro** por mais de **3–4 s** por pad.
- WS2812B: soldar **5V/GND/DIN/DOUT** no breakout; não inverter **DIN/DOUT** na cadeia dos 8 LEDs.
- Documentar com foto a traseira dos XLR (pino 1/2/3) de cada módulo.

---

## 11. Problemas comuns

| Sintoma | Verificar |
|---------|-----------|
| Módulo apagado | 5 V no pino 2 do XLR; ordem MOD 1→4; DIN no 1º LED |
| Só 1º LED acende | Cadeia interna DOUT→DIN entre os 8 LEDs |
| Cores erradas no tubo | `TUBE_COLOR_ORDER` RGB/GRB no `.ino` |
| MIDI BT não chega | Baud 115200; COM do bridge; canal MIDI 1 |
| Tubo fraco no fim | Injeção 5 V/GND no meio dos 4 m |
| Pro Micro não aparece USB | Cabo dados; placa Leonardo 5V 16MHz |

---

## 12. Checklist antes do show

- [ ] Etiquetas MOD 1–4 e cabos MOD/TUBO
- [ ] Firmware com `LEDS_PER_MODULE 8`, `NUM_TUBE_LEDS 200`
- [ ] ZS-040 pareado; ou cabo USB reserva
- [ ] Parafusos C14 e XLR apertados
- [ ] Cabo C13 com terra da instalação
