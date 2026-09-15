# Eletrônica — driver, MOSFET e referência ao vídeo

## O que o vídeo faz (e o que mudar para palco)

Referência: [YouTube — ESP + MOSFET + LED uma cor](https://www.youtube.com/watch?v=HSeckw3VLy8)

Esquema conceitual do vídeo:

```
ESP GPIO ──[R_gate 100Ω]──┤G
                          │  N-ch MOSFET
LED (+) ── V+ (5V do ESP ou externo)
LED (-) ──┤D
          │
         ┤S ── GND comum
```

**O que funciona igual no nosso projeto:**

- ESP **não** alimenta o LED; só **comanda o gate** do MOSFET.
- MOSFET na **parte baixa** (low-side switch): catodo do LED no drain, fonte no GND.
- PWM no GPIO para dimmer.

**O que precisa mudar para watts de palco:**

| Aspecto | Vídeo (LED pequeno) | StageMod |
|---------|---------------------|----------|
| Fonte LED | 3,3–5 V, poucos mA | **24 V barramento**, 350 mA–1 A/canal |
| MOSFET | Qualquer logic-level | **IRLB8721** ou AO3400 (verificar @ 3,3 V) |
| Limitação de corrente | Resistor ou LED interno | **Driver CC** ou resistor dimensionado |
| GND | Comum ESP + LED | **Estrela na fonte**; ESP isolado do calor do LED |

## Esquema recomendado por canal (Spot-S, 3 W)

### Opção A — Eficiente (produção)

```
24V ──► [Módulo buck CC 350mA, ex. PT4115] ──► LED (+)
                              ▲
                         EN/PWM ◄── GPIO ESP (via level OK se 3,3V)
LED (-) ──► GND

MOSFET opcional no caminho EN se driver não aceitar PWM direto.
```

Módulos PT4115 prontos (~US$ 0,30): ajustar potenciômetro para 350 mA uma vez por canal.

### Opção B — Protótipo rápido (linear, mais calor)

```
24V ──► LED (+) ânodo
LED (-) catodo ──► Drain MOSFET ──► Source ──► GND
                  Gate ◄── GPIO + 100Ω + pull-down 10k
```

**Resistor de limitação** (se não usar buck):

| Canal | Vf típico | R @ 350 mA de (12V)* | Potência resistor |
|-------|-----------|------------------------|-------------------|
| R | 2,2 V | (12−2,2)/0,35 ≈ 28 Ω | ~3,4 W → usar 5 W |
| G | 3,2 V | ≈ 25 Ω | ~3 W |
| B | 3,2 V | ≈ 25 Ω | ~3 W |

\* Usar **12 V local** no módulo (buck 24→12 V) reduz dissipação no resistor vs 24 V direto.

Para protótipo: **1× LM2596 24→12 V por módulo** + resistores + MOSFETs é aceitável; para 12 módulos, migrar para Opção A.

## MOSFET — escolha

| Ref | Vds | Id | Rds(on) @ Vgs=4.5V | Pacote | Uso |
|-----|-----|-----|---------------------|--------|-----|
| **IRLB8721** | 30 V | 62 A | 8 mΩ | TO-220 | Canais 3–10 W, fácil heatsink |
| AO3400A | 30 V | 5.7 A | 50 mΩ | SOT-23 | 3 W, PCB compacta |
| IRLZ44N | 55 V | 47 A | 22 mΩ | TO-220 | OK; preferir IRLB8721 |

**Evitar:** IRFZ44N (não logic-level pleno em 3,3 V).

### Gate driver mínimo

```
GPIO ── 100 Ω ── Gate
                 │
                10 kΩ pull-down para GND
```

PWM frequency: **1–25 kHz** (acima de audibilidade; ESP LEDC suporta).

## Parte digital por módulo

| Bloco | Componente | Função |
|-------|------------|--------|
| MCU | ESP32-C3-MINI-1 ou devkit | PWM + UART |
| RS-485 | **MAX485** ou SP3485 | Half-duplex, DE/RE ligados |
| Regulador | AMS1117-3.3 ou buck 24→5 V | Alimentar ESP (não usar 3,3 V do USB em satélite) |
| Proteção | Polyfuse 1 A, TVS 24 V | Entrada V+ |
| Endereço | DIP-3 ou resistor solder | ID do módulo |

### Ligação RS-485 (daisy-chain)

```
Barramento A ──┬── A (MAX485) ──┬── OUT A
Barramento B ──┴── B (MAX485) ──┴── OUT B
DE + RE do MAX485 ── GPIO (modo recepção default; TX enable só ao responder)
```

Terminação **120 Ω** entre A e B **somente no último módulo** da linha (jumper).

## PCB — blocos funcionais

```
┌──────────────────────────────────────────────────┐
│ [IN 4pin]  polyfuse  TVS  buck 5V  ESP32-C3    │
│            MAX485                                 │
│ [OUT 4pin]                                        │
│                                                   │
│  buck 12V ou 3× PT4115                            │
│  3× (MOSFET + LED connector)                      │
│  heatsink área                                    │
└──────────────────────────────────────────────────┘
```

## Lista de GPIO sugerida (ESP32-C3)

| GPIO | Função |
|------|--------|
| 0–2 | DIP address (com pull-up interno) |
| 4 | PWM Red |
| 5 | PWM Green |
| 6 | PWM Blue |
| 7 | PWM White (opcional) |
| 8 | UART TX → RS-485 DI |
| 9 | UART RX ← RS-485 RO |
| 10 | RS-485 DE/RE |

(Ajustar conforme pinout da placa devkit.)

## Segurança elétrica

- **Fusível** em cada módulo e na entrada da fonte.
- **Nunca** hot-plug com carga máxima sem desligar fonte.
- LEDs de alta potência: **queimadura** — carcaça isolada ou grade.
- Cabo de alimentação dimensionado para corrente total do ramo.

## Ferramentas para protótipo

- Multímetro + amperímetro (verificar 350 mA por canal).
- Osciloscópio opcional (forma de PWM).
- Fonte ajustável 0–30 V limitada em corrente para primeiro teste sem ESP.
