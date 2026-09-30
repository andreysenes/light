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

## Ordem de montagem (siga nesta sequência)

```
1. FONTE     — SMPS 5 V, barramento, C14 (AC por último na caixa)
2. PRO MICRO — Medusa: placa, ZS-040, XLR no painel, D5/D6
3. CABOS     — 4× módulo spot + tentáculos XLR + tubo
4. TESTE     — continuidade e 5 V (ainda sem firmware)
5. FIRMWARE  — upload, ZS-040, boot e MIDI
```

Detalhes em cada seção abaixo. **Ferramentas** e **convenções** vêm antes da Parte 1.

---

## Ferramentas

| Ferramenta | Uso |
|------------|-----|
| Ferro de solda **25–60 W**, ponta fina | Conectores, fios, pads |
| Estanho com fluxo | Ligações |
| Alicate de corte / decapador AWG 18–22 | Cabos |
| Multímetro | Continuidade, 5 V, polaridade |
| Chave fenda / furadeira | Painel (C14, XLR, USB) |
| Estilete, fita, etiquetas | Identificar cabos `MOD`, `TUBO`, `DATA` |

EPI: óculos, local ventilado. Para **127/220 V**, tomada **desligada** e caixa **aberta** só até validar o DC.

---

## Convenções de fio e XLR

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

## Parte 1 — Fonte

Objetivo: **5 V estáveis** no barramento da Medusa, com segurança na entrada AC.

### 1.1 Mecânica da caixa

1. Furar painel: **C14**, **USB micro**, XLR **MOD**, XLR **TUBO** (e **INJ** se usar).
2. Parafusar **fonte SMPS 5 V 10 A** na caixa (espaçadores; não encostar lâmina metálica viva no fundo sem isolamento).

### 1.2 Barramento DC (primeiro em bancada, se quiser)

Pode testar a fonte **fora da caixa** com bornes antes de soldar na Medusa:

1. Saída **+V / −V** da SMPS → fio **AWG 18** vermelho (+) e preto (GND) até um ponto de distribuição.
2. **Não** ligar LEDs nem Pro Micro ainda — só medir **5,0–5,2 V** entre + e GND.

### 1.3 Entrada AC (C14)

**Somente** com caixa desenergizada e fios AC isolados.

1. **C14** → fonte SMPS:
   - **⏚** C14 → **FG** da fonte
   - **N** → **N**
   - **L** → **fusível 2 A** → **L** da fonte
2. Multímetro: **sem curto** entre L e N, entre L e ⏚.
3. Etiquetar **127/220 V** na caixa.

**Primeira energização na rede:** sem cabos XLR nos módulos; medir de novo **5 V** no barramento. Fechar a tampa só depois de validar o DC.

### 1.4 Derivações do barramento (ainda sem dados)

Do mesmo **+5 V / GND**, preparar fios para (soldar na Parte 2):

- **Pino 2** e **pino 1** dos XLR **MOD**, **TUBO** (e **INJ**)
- **VCC** / **GND** do Pro Micro e do ZS-040
- **Shell** de cada XLR → **GND**

---

## Parte 2 — Pro Micro (Medusa)

Objetivo: placa e Bluetooth na caixa, **alimentados pelo barramento**, saídas de dados nos XLR. **Ainda não** fazer upload do firmware.

> No StageMod v0 a “placa” é o **Pro Micro** (ATmega32U4, 5 V) — não o Raspberry Pi Pico. O firmware do repositório é só para Pro Micro.

### 2.1 Ligar a fonte no Pro Micro

Use a **mesma** fonte **5 V** da Parte 1 (barramento vermelho = +, preto = GND).

```
Fonte 5 V (+) ────────► pad VCC  (ou pin "VCC" / "5V" na borda)
Fonte 5 V (−) ────────► pad GND  (qualquer GND na borda)
```

| Passo | Ação |
|-------|------|
| 1 | Fonte **desligada** na tomada (ou SMPS sem AC). |
| 2 | Multímetro na saída da fonte: **vermelho** no **+V**, **preto** no **−V** → deve marcar **+5 V** (não invertido). |
| 3 | Soldar ou parafusar fio **AWG 22–18** do **+ barramento** no **VCC** do Pro Micro. |
| 4 | Fio do **GND barramento** no **GND** do Pro Micro (mesmo plano de terra da fonte). |
| 5 | **Não** alimentar o Pro Micro pelo pino **RAW** com 5 V — **RAW** é entrada para o regulador interno (7–12 V em muitas clones). Com SMPS 5 V use só **VCC**. |
| 6 | Ligar a fonte: a placa não acende LEDs sozinha ainda; opcional: LED de power da clone aceso. Medir **5 V** entre VCC e GND nos pads. |
| 7 | **USB:** pode ficar desconectado nesta etapa. Depois, para programar, USB + fonte 5 V no **VCC** é o uso normal na Medusa (clone com diodo entre USB e VCC). |

**O que não fazer**

- Não passar a **corrente dos LEDs** pelo Pro Micro — só **sinal** em D5/D6; **5 V dos módulos/tubo** vão direto do barramento aos XLR (pino 2).
- Não ligar **+5 V** em **GND** (confira cores antes de energizar).

### 2.2 Fixar placa na caixa

1. Fixar **Pro Micro** com espaçadores (USB acessível pelo painel).
2. Repetir o par **VCC / GND** ao barramento se ainda não soldou na etapa 2.1.

### 2.3 ZS-040

| De | Para |
|----|------|
| ZS-040 **TX** | Pro Micro **D0 (RX)** |
| ZS-040 **RX** | Pro Micro **D1 (TX)** — adaptação 3,3 V se necessário: [19-ZS-040.md](19-ZS-040.md) |
| **GND** | GND comum |
| **VCC** | +5 V (se o módulo aceitar 5 V) |

A configuração **AT+BAUD4** (115200) fica na **Parte 5 — Firmware**.

### 2.4 XLR na Medusa (ligados ao Pro Micro)

Na caixa da Medusa você monta **2× XLR fêmea painel** (receptáculo): um etiquetado **MOD**, outro **TUBO**. O cabo de palco usa **plug macho** na ponta que encaixa na Medusa.

**Não é áudio** — pinagem de pixel (5 V / GND / DATA). Detalhes: [16-XLR-CONECTORES.md](16-XLR-CONECTORES.md).

#### O que vai em cada pino (os dois XLR iguais na alimentação)

| Pino XLR | Sinal | De onde vem na Medusa |
|----------|--------|------------------------|
| **1** | **GND** | Barramento **GND** (preto AWG 18) + **shell** do conector |
| **2** | **+5 V** | Barramento **+5 V** (vermelho AWG 18) — **direto da fonte**, não pelo Pro Micro |
| **3** | **DATA** | Só **um** fio AWG 22 por XLR — ver tabela abaixo |

| XLR painel | Pino 3 (DATA) no Pro Micro |
|------------|----------------------------|
| **MOD** | **D6** |
| **TUBO** | **D5** |

Ligação **direta** D5/D6 → pino 3 (sem resistor no manual v0).

#### Vista do conector (lado solda, padrão Neutrik / clone)

Olhando a **parte traseira** do XLR fêmea painel (onde solda), pinos em triângulo:

```
        pino 1 (GND)
           ●
    pino 2 ●   ● pino 3 (DATA)
      (+5V)
```

Confirme no **seu** conector com o datasheet — alguns clones marcam 1/2/3 no plástico.

#### Passo a passo — um XLR (repetir para MOD e TUBO)

| # | Ação |
|---|------|
| 1 | Furo no painel conforme o conector (geralmente **~24 mm** + 2 furos M3 ou presilha). Parafusar o XLR **antes** de soldar os fios longos. |
| 2 | **Shell / corpo metálico** → fio preto ao **GND** do barramento (ou aba de terra do conector). |
| 3 | **Pino 1** → mesmo **GND** (pode juntar shell + pino 1 num único ponto na caixa). |
| 4 | **Pino 2** → **+5 V** do barramento (fio vermelho AWG 18). |
| 5 | **Pino 3** → fio verde/branco AWG 22 até o pad **D6** (MOD) ou **D5** (TUBO) do Pro Micro. |
| 6 | **GND comum:** um fio preto AWG 22 do **GND** do Pro Micro ao mesmo ponto GND dos XLR (terra único na caixa). |
| 7 | Etiqueta no painel: `MOD D6` e `TUBO D5` + `5V PIXEL`. |

#### Esquema interno da Medusa

```
Barramento +5V ─────┬──── pino 2  XLR MOD
                    ├──── pino 2  XLR TUBO
                    ├──── VCC Pro Micro
                    └──── VCC ZS-040 (se 5 V)

Barramento GND ─────┬──── pino 1 + shell  XLR MOD
                    ├──── pino 1 + shell  XLR TUBO
                    ├──── GND Pro Micro
                    └──── GND ZS-040

Pro Micro D6 ────────────── pino 3  XLR MOD   ──cabo──► Mod1 IN
Pro Micro D5 ────────────── pino 3  XLR TUBO  ──cabo──► tubo
```

#### Cabo que sai da Medusa (primeiro tentáculo)

Não confundir com o XLR **dentro** da caixa: o **cabo** é montado à parte (Parte 3.2).

| Condutor no cabo | Cor sugerida | XLR macho na ponta da Medusa |
|------------------|--------------|------------------------------|
| GND | preto + malha | **pino 1** |
| +5 V | vermelho | **pino 2** |
| DATA | verde/branco | **pino 3** |

O plug **macho** do cabo entra no XLR **fêmea** do painel; na outra ponta, outro XLR (geralmente **fêmea** no cabo indo ao MOD 1 **IN** fêmea — use cabo **macho–macho** ou **macho–fêmea** conforme o que fechar a cadeia; o importante é **1=GND, 2=5V, 3=DATA** em todo o sistema).

#### Teste antes do firmware

Com fonte ligada e **sem** sketch no Pro Micro:

- Entre **pino 2 e 1** de cada XLR: **~5 V**
- Entre **pino 3 e 1**: não deve ser curto com +5 V; tensão flutuante é normal

---

## Parte 3 — Cabos

Objetivo: módulos spot prontos e cabos de palco até a Medusa.

### 3.1 Módulo spot (repetir ×4, etiquetar MOD 1…4)

Cada módulo tem **8 LEDs WS2812B** em **série**. No MIDI, um módulo = **um** bloco de 8 LEDs com a **mesma cor**.

**Carcaça 3D (opcional):** [23-MODULO-SPOT-3D.md](23-MODULO-SPOT-3D.md) — [`hardware/spot-module-v0/`](../hardware/spot-module-v0/).

| Lado | Conector |
|------|----------|
| **IN** | XLR **fêmea** |
| **OUT** | XLR **macho** |

```
  XLR IN (F)                         8× WS2812B em cadeia          XLR OUT (M)
  Pin 1 GND ────────┬── GND dos LEDs ─────────────────────────── Pin 1 GND
  Pin 2 5V  ────────┬── 5V dos LEDs ─────────────────────────── Pin 2 5V
  Pin 3 DATA ───────┼──► DIN (LED 1) … LED 8 DOUT ────────────── Pin 3 DATA
```

1. Trilhas **5 V** e **GND** no módulo.
2. **5V** e **GND** de cada LED nas trilhas.
3. **DIN** do 1º LED no **pino 3** do XLR **IN**.
4. **DOUT → DIN** entre os 8 LEDs.
5. **DOUT** do 8º LED no **pino 3** do XLR **OUT**.
6. Pass-through pinos **1** e **2** do IN para o OUT.
7. **Shell** dos XLR no **GND**.

| Etiqueta | Pixels | Nota MIDI |
|----------|--------|-----------|
| **MOD 1** | 0–7 | C3 |
| **MOD 2** | 8–15 | D3 |
| **MOD 3** | 16–23 | E3 |
| **MOD 4** | 24–31 | F3 |

**DATA** em série: **IN → OUT → IN** entre módulos (nunca em paralelo na linha de dados).

### 3.2 Cabos XLR (tentáculos)

Pinagem em todos: **1=GND, 2=5V, 3=DATA**.

| Cabo | De | Para | Comprimento típico |
|------|-----|------|---------------------|
| A | Medusa **MOD** | MOD 1 **IN** | 1–2 m |
| B–D | MOD **OUT** | próximo **IN** | 0,3–1 m |
| E | Medusa **TUBO** | tubo | 3–5 m |

**Tubo 4 m (200 LED):** vermelho = 5 V, fio do **meio** = DATA (WS2811), externo = GND (manual D15); ligar ao XLR 1/2/3.

Opcional: **5 V/GND** no **meio** do tubo para queda de tensão.

### 3.3 Ligação completa (visão geral)

```
[C13 rede] → C14 → SMPS 5V10A
                    ├─ Pro Micro + ZS-040
                    ├─ XLR MOD ──cabo──► MOD1 ⇄ MOD2 ⇄ MOD3 ⇄ MOD4
                    └─ XLR TUBO ──cabo──► Tubo 4m (200 LED)
```

---

## Parte 4 — Teste (antes do firmware)

Objetivo: confirmar **fiação e alimentação** sem depender do programa ainda.

| # | Procedimento | OK se |
|---|----------------|-------|
| 1 | **Sem** Pro Micro no USB, barramento **sem** cargas pesadas | 5,0–5,2 V no barramento |
| 2 | Continuidade: XLR **pino 1** ↔ shell ↔ GND Medusa | bip no multímetro |
| 3 | Cada tentáculo: pino 2 ↔ pino 1 **não** curto; pino 2 = +5 V com fonte ligada | sem faísca, ~5 V |
| 4 | MOD 1 **só** no XLR MOD (Pro Micro ainda **sem** sketch) | 5 V nos pinos 2/1 do módulo; DATA isolada |
| 5 | Ordem física etiquetada MOD 1→4; tubo separado no XLR TUBO | cabos corretos |

Se algo falhar, corrija solda antes da Parte 5. LEDs **não** devem acender nesta fase (normal).

---

## Parte 5 — Firmware

Objetivo: programar o Pro Micro, Bluetooth e validar o rig completo.

### 5.1 Upload

1. Cabo **USB** no Pro Micro (placa **Leonardo / 5 V 16 MHz** no Arduino IDE).
2. Abrir [firmware/promicro-4mod/promicro-4mod.ino](../firmware/promicro-4mod/promicro-4mod.ino).
3. Conferir `LEDS_PER_MODULE 8`, `NUM_TUBE_LEDS 200`.
4. Upload.

### 5.2 ZS-040

1. Configurar **AT+BAUD4** (115200) — ver [19-ZS-040.md](19-ZS-040.md).
2. Parear com o PC; bridge MIDI→serial na mesma baud — [18-WIRELESS-MIDI.md](18-WIRELESS-MIDI.md).

### 5.3 Testes funcionais

| # | Teste | Esperado |
|---|--------|----------|
| 1 | Boot sem MIDI, **só MOD 1** ligado | 8 LEDs R → G → B → W |
| 2 | Cadeia MOD 1→4 | Cada módulo 8 LEDs na sequência de boot |
| 3 | Tubo no XLR TUBO | Animação curta após os módulos |
| 4 | CC 1–3 | MOD 1 muda cor (8 LEDs juntos) |
| 5 | Notas C3–F3 | Módulos 1–4 com velocity |
| 6 | CC 7 / PC | Dimmer e gradiente no tubo |
| 7 | BT vs USB | Um caminho MIDI por vez na DAW |

Brilho no início: **CC 7** ~30–40%.

```
DAW → Bluetooth → ZS-040 → Serial1
   ou USB → Pro Micro
```

---

## Soldagem — boas práticas

- Aquecer **metal + fio**, depois estanho; evitar bola seca no plástico do XLR.
- Tracionar levemente o fio após soldar no pino XLR.
- Não aquecer o **Pro Micro** mais de **3–4 s** por pad.
- WS2812B: não inverter **DIN/DOUT** na cadeia dos 8 LEDs.
- Foto da traseira dos XLR (pinos 1/2/3) em cada módulo.

---

## Problemas comuns

| Sintoma | Verificar |
|---------|-----------|
| Módulo apagado | 5 V no pino 2; ordem MOD 1→4; DIN no 1º LED |
| Só 1º LED acende | DOUT→DIN entre os 8 LEDs |
| Cores erradas no tubo | `TUBE_COLOR_ORDER` no `.ino` |
| MIDI BT não chega | Baud 115200; COM do bridge; canal 1 |
| Tubo fraco no fim | Injeção 5 V/GND no meio dos 4 m |
| Pro Micro não aparece USB | Cabo dados; placa Leonardo 5V 16MHz |

---

## Checklist antes do show

- [ ] Etiquetas MOD 1–4 e cabos MOD/TUBO
- [ ] Firmware `LEDS_PER_MODULE 8`, `NUM_TUBE_LEDS 200`
- [ ] ZS-040 pareado; cabo USB reserva
- [ ] C14, fusível e XLR apertados
- [ ] Cabo C13 com terra da instalação
