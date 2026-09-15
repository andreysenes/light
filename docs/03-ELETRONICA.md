# Eletrônica — Cabeça, módulo e drivers 10 W

## Visão geral

```
┌── Cabeça ──────────────────┐     ┌── Módulo Dual ─────────────┐
│ ESP32-S3                   │     │ ATtiny1614                 │
│  USB MIDI                  │     │  MAX485                    │
│  MAX485 ───────── RS-485 ──┼─────┼── MAX485                   │
│  Buck 5V                   │     │  PWM A ──► Driver CC ──► WW│
└────────────────────────────┘     │  PWM B ──► Driver CC ──► R │
                                   └────────────────────────────┘
         ▲                                      ▲
    Fonte 24 V ─────────── P4 + RJ45 ──────────┘
```

Referência conceitual MOSFET: [vídeo ESP + MOSFET](https://www.youtube.com/watch?v=HSeckw3VLy8) — aplica-se ao **chaveamento**, não à alimentação do LED pelo ESP.

## Cabeça — esquema

| Bloco | Parte | Notas |
|-------|-------|-------|
| MCU | ESP32-S3-WROOM | USB nativo |
| RS-485 | MAX485 / SP3485 | DE+RE em 1 GPIO |
| Entrada energia | P4 IN | Fonte 24 V (centro +) |
| **Proteção OUT** | **P-MOS anti-reverso** | **Obrigatório no P4 OUT — única saída do rig** |
| Alimentação | Buck 24→5 V | Alimenta ESP; **após** barramento protegido |
| Saída dados | RJ45 | RS-485 para primeiro módulo |
| Saída energia | **P4 OUT** | 24 V protegido → todos os módulos |

### Cabeça — barramento de energia (única fonte do sistema)

A Cabeça é o **único ponto** que alimenta a cadeia de módulos. A proteção anti-reverso na **saída P4** evita que um cabo invertido ou erro de montagem destrua drivers, LEDs e MCUs em todo o rig.

```
                    ┌── Cabeça ─────────────────────────────────────┐
  Fonte 24V         │                                               │
  P4 ──────────────►│ P4 IN                                         │
  (centro +)        │   │                                           │
                    │   ├──► [P-MOS anti-reverso] ──► V+_BUS         │
                    │   │         │                      │          │
                    │   │         │                      ├── P4 OUT ──┼──► Mód1…MódN
                    │   │         │                      │          │
                    │   └── GND ──┴──────────────────────┴── GND OUT─┼──►
                    │              │                                   │
                    │              ├── polyfuse 10A                      │
                    │              ├── TVS SMBJ24A                       │
                    │              └── buck 24→5 V ──► ESP32            │
                    │                                               RJ45 OUT
                    └───────────────────────────────────────────────────┘
```

| Etapa | Componente | Função |
|-------|------------|--------|
| 1 | **P-MOS** (IRF9540N ou AO4407) | Bloqueia V+ se polaridade invertida no barramento |
| 2 | **Polyfuse 10 A** | Limita curto após proteção |
| 3 | **TVS SMBJ24A** | Surto / transientes |
| 4 | **P4 OUT** | Alimenta toda a cadeia P4 |

> O buck do ESP32 liga em **V+_BUS** (após anti-reverso), não antes — assim o ESP também não recebe tensão invertida.

### Circuito anti-reverso — P4 OUT (detalhe)

```
P4 IN centro (VIN+) ────── S
                      ┌───┴───┐
P4 IN casco  (GND) ───┤  G    │   P-MOS: IRF9540N (TO-220, até ~15 A)
                      └───┬───┘           ou AO4407 (SO-8, até ~8 A rig pequeno)
                          D ──► V+_BUS ──► polyfuse 10A ──► P4 OUT centro
P4 IN casco ─────────────────────────────────────────────► P4 OUT casco
```

| Pino P-MOS | Ligação |
|------------|---------|
| **Source (S)** | P4 IN centro — VIN+ da fonte |
| **Gate (G)** | P4 IN casco (GND) via **10 kΩ** |
| **Drain (D)** | V+_BUS → polyfuse → P4 OUT centro |

| Polaridade | Comportamento |
|------------|---------------|
| **Correta** (centro +24 V) | Vgs ≈ −24 V → MOSFET **liga** (~0,05–0,1 V de queda) |
| **Invertida** | Vgs ≥ 0 → MOSFET **desliga** → corrente **≈ 0** em todo o rig |

Resistor **10 kΩ** Gate → GND (casco P4). Opcional **100 kΩ** Source–Gate para OFF com plug solto.

**Dissipação @ 10 A:** P ≈ I² × Rds(on) ≈ 10² × 0,2 Ω ≈ **2 W** no IRF9540N — usar **heatsink pequeno** ou dissipação no corpo TO-220.

### Proteção no P4 IN (recomendado)

Se a fonte também usa P4, pode inverter na entrada da Cabeça. Opções:

| Abordagem | Notas |
|-----------|-------|
| **Um P-MOS só no IN** | Protege fonte + ESP + OUT com um estágio (IN e OUT em paralelo no V+_BUS após MOS) |
| **Dois P-MOS** (IN + OUT) | IN protege a Cabeça; OUT protege se alguém ligar carga invertida no OUT sem fonte no IN |

**Mínimo do projeto:** P-MOS no caminho entre **fonte e P4 OUT** (um estágio no IN da Cabeça equivale a proteger a saída, pois não há outro caminho de energia).

Para clareza de montagem, documentamos como **anti-reverso no tronco de saída** imediatamente antes do **P4 OUT**.

### Alternativa — diodo Schottky (somente protótipo)

```
VIN+ ──►|── SS54 (5 A) ──► V+_BUS
```

Simples, porém **~0,4 V × 10 A ≈ 4 W** de perda em carga máxima. Usar só em bancada; em produção preferir **P-MOS**.

### Indicador visual (opcional)

| LED | Ligação |
|-----|---------|
| Verde | V+_BUS → resistor 2,2 kΩ → LED → GND |
| — | Aceso = polaridade correta e barramento ativo |

### Teste de aceite (Cabeça)

1. Fonte correta → LED verde ON; P4 OUT mede +24 V; MIDI/RS-485 OK.
2. **Inverter cabo na fonte ou no P4 OUT** → corrente total **≈ 0 A**; sem aquecimento em módulos.
3. Corrigir polaridade → sistema volta sem trocar fusível.

GPIO sugeridos:

| GPIO | Função |
|------|--------|
| USB | MIDI |
| 17 | UART2 TX → DI |
| 16 | UART2 RX ← RO |
| 4 | RS-485 DE/RE |
| 5 | LED status |

## Módulo Dual — esquema

| Bloco | Parte | Notas |
|-------|-------|-------|
| Decoder | ATtiny1614 | UART + 2× PWM LEDC |
| Bus | MAX485 | Pass-through A/B |
| Addr | DIP-3 | Pull-ups internos |
| Driver A, B | Buck CC 900 mA | XL6001 ou PT4115 mod |
| Chaveamento | IRLB8721 no EN | Se driver não PWM nativo |
| Proteção | Polyfuse 2 A, TVS 24 V | Entrada IN |
| LEDs | Star 10 W × 2 | Soquetes A, B |

### ATtiny1614 vs ESP

- UART hardware para RS-485.
- 2 canais PWM ~20 kHz.
- ~US$ 0,60 vs US$ 2,50 ESP32.
- Firmware < 4 KB flash.

## Driver 10 W — canal único

```
24V (barramento) ──► [Buck CC 900mA] ──► LED (+)
                           ▲
                      EN ◄── PWM (ATtiny) ou MOSFET
LED (−) ───────────────────────────────────► GND
```

### Ajuste PT4115 / XL6001 para 900 mA

- PT4115: R_sense ≈ 0,15 Ω para ~900 mA (ver datasheet).
- Verificar com amperímetro em série antes de carga térmica longa.

### MOSFET no enable (alternativa)

```
GPIO ──100Ω──┤G  IRLB8721
             ┤D── EN do módulo buck
             ┤S── GND
```

## MOSFET — quando usar

| Situação | Solução |
|----------|---------|
| Buck aceita PWM em EN | PWM direto do ATtiny |
| Buck só liga/desliga | MOSFET logic-level no EN |
| Driver linear (protótipo) | MOSFET low-side + resistor (não recomendado 10 W) |

**IRLB8721** para 10 W; **AO3400A** só se corrente < 2 A confirmada.

## Módulo — pass-through (sem anti-reverso)

A proteção fica **só na Cabeça**. Módulos fazem pass-through do barramento já protegido + polyfuse local.

```
P4 IN  centro ── V+ ── polyfuse 2A ──┬── buck drivers ── P4 OUT centro
P4 IN  casco  ── GND ────────────────┴── P4 OUT casco
RJ45 IN pin4/5 ── MAX485 ──┬── RJ45 OUT pin4/5 (pass-through)
```

> Cabo P4 invertido **no meio da cadeia** ainda é perigoso — montar cabos com **centro +** certificado e fita vermelha na ponta da fonte. A Cabeça protege o erro na **primeira ligação** (fonte ou P4 OUT).

Trilha V+: fio AWG18 entre conectores ou trilha ≥ 3 mm na PCB.

## Terminação RS-485

- Resistor **120 Ω** entre D+ e D− no **último** módulo de cada ramo (jumper SMD).
- Cabeça **não** termina (só transceiver).

## Segurança

| Item | Valor |
|------|-------|
| Polyfuse Cabeça OUT | 10 A (após anti-reverso) |
| Polyfuse módulo | 2 A |
| **Anti-reverso Cabeça** | **IRF9540N** (TO-220) ou AO4407 |
| TVS Cabeça | SMBJ24A no V+_BUS |
| Heatsink | TO-220 na Cabeça se > 8 A contínuo |
| Temperatura teste | 30 min @ 100 % ambos canais |

## Protótipo em breadboard (ordem)

1. Cabeça: ESP32 envia “hello” serial USB + loopback RS-485.
2. 1 canal: ATtiny + 1 driver + 1 LED 10 W (começar em 50 % PWM).
3. Medir corrente e temperatura.
4. Adicionar segundo canal + cabos P4 e Cat5e curtos.
