# Módulo Dual — 2× 10 W, sem ESP

Módulo luminoso **simples**: apenas drivers, decodificador de barramento e dois soquetes de LED. Toda inteligência fica na **Cabeça** (único ESP32).

## Especificação v1 (padrão de fábrica)

| Canal | LED padrão | Potência | Corrente típica |
|-------|------------|----------|-----------------|
| **A** | Warm white 3000 K | 10 W | ~900–1050 mA |
| **B** | Vermelho 620–630 nm | 10 W | ~900–1050 mA |

Potência máxima do módulo: **~20 W** (+ perdas driver ≈ 22–25 W do barramento 24 V → **~1,0–1,2 A** por módulo).

## Bloco funcional

```
IN (StageMod 5p) ──► pass-through OUT
         │
    ┌────┴────────────────────────────┐
    │  MAX485  ◄──► ATtiny (decoder)  │
    │     │              │            │
    │     │         PWM A, PWM B      │
    │     │              │            │
    │  Driver CC A   Driver CC B      │
    │     │              │            │
    │  LED socket A  LED socket B      │
    └─────────────────────────────────┘
```

### Por que um ATtiny no módulo (e não ESP)

| | ESP32 por módulo | ATtiny + MAX485 |
|---|------------------|-----------------|
| Custo | ~US$ 2,50+ | ~US$ 1,20 |
| Complexidade | Wi‑Fi, flash, antena | só PWM + UART |
| Função | excesso | suficiente |

Não é “cabeça duplicada” — é um **decoder de 2 canais** comparável a um receptor DMX de 2 slots.

## PCB universal — dois soquetes de LED

Mesma placa para todas as combinações futuras:

```
┌─────────────────────────────────────┐
│  [IN]              [OUT]            │
│                                     │
│  (A) ○ lens 20mm    (B) ○ lens 20mm │
│      star 10W           star 10W    │
│                                     │
│  DIP [ADDR 1-8]                     │
└─────────────────────────────────────┘
```

- Soquetes: padrão **star PCB 20 mm** (furo M3) ou solda direta.
- **1 lente PMMA Ø 20 mm** por canal (padrão **90°** wash) + holder no heatsink.
- Centros das ópticas: **~30 mm** um do outro.
- Trocar cor = trocar LED + atualizar config na Cabeça (lente reutiliza).
- Detalhes ópticos: [12-LENTE-20MM.md](12-LENTE-20MM.md).

## Drivers 10 W

| Canal | Vf @ 1 A | Driver sugerido |
|-------|----------|-----------------|
| Vermelho | 2,2–2,8 V | Buck CC **1 A** (XL6001 / PT4115 ajustado) |
| Warm white | 3,0–3,6 V | Idem |

Cada driver:

- Entrada: 24 V do barramento.
- Saída: corrente constante **900 mA** (ajuste uma vez).
- Dim: pino **EN/DIM** ligado ao PWM do ATtiny (ou MOSFET no enable).

**MOSFET IRLB8721** no canal de enable se o módulo buck não aceitar PWM direto no EN.

## Dissipação térmica

20 W contínuos exigem:

- Perfil alumínio **≥ 80 mm** ou carcaça em alumínio usinado.
- Pasta térmica em cada star.
- Lente com **folga de ar** — não transferir calor para PMMA.
- Face frontal da carcaça: orifícios Ø20 mm ou moldura aberta por lente.
- Em gabinete fechado: furos laterais no holder ou ventilação forçada opcional.

Teste de aceite: 30 min a 100 % em ambiente 25 °C → carcaça < 65 °C ao toque.

## Endereço físico

| Método | Bits | Módulos |
|--------|------|---------|
| DIP-3 | 3 | 1–7 (0 = não usar) |
| DIP-4 | 4 | 1–15 |

Endereço **não** define as cores — só a posição na cadeia lógica. Cores vêm da **config na Cabeça**.

## Configuração lógica (futuro)

Na Cabeça, arquivo `modules.json` (ou portal web):

```json
{
  "modules": [
    { "addr": 1, "ch_a": "warm_white", "ch_b": "red" },
    { "addr": 2, "ch_a": "warm_white", "ch_b": "warm_white" },
    { "addr": 3, "ch_a": "red", "ch_b": "amber" },
    { "addr": 4, "ch_a": "green", "ch_b": "red" }
  ]
}
```

### Tipos de canal suportados (planejado)

| ID | Cor | LED físico |
|----|-----|------------|
| `warm_white` | Branco quente 3000 K | Star 10 W WW |
| `cool_white` | Branco frio 6000 K | Star 10 W CW |
| `red` | Vermelho | Star 10 W R |
| `amber` | Âmbar | Star 10 W amber |
| `green` | Verde | Star 10 W G |
| `blue` | Azul | Star 10 W B |
| `off` | Desligado | — |

### MIDI → módulo

A Cabeça traduz:

- **Nota/CC “cor”** → intensidade por **tipo semântico** (ex. “red” acende todos os canais configurados como `red`).
- **CC por módulo** → `addr` + `ch_a` / `ch_b` direto (modo técnico).

Exemplo: Mod 3 = red + amber. Nota “Red” no DAW → só canal A; “Amber” → só canal B.

## Protocolo no barramento (2 canais)

Frame reduzido (Cabeça → módulo `addr`):

```
[SYNC][ADDR][CMD][CH_A][CH_B][CRC]
 0xAA   1-127  0x01  0-255 0-255  xor
```

| CMD | Função |
|-----|--------|
| 0x01 | SET_LEVELS imediato |
| 0x02 | FADE ( + 2 bytes tempo ms ) |
| 0x03 | BLACKOUT broadcast |
| 0x10 | PING |

Módulo só responde se `ADDR` = seu DIP ou broadcast `0xFF`.

## BOM por módulo Dual (estimativa)

| Item | Qtd | ~US$ |
|------|-----|------|
| ATtiny1614 ou ATtiny85 | 1 | 0,60 |
| MAX485 | 1 | 0,50 |
| Buck CC 1 A | 2 | 2,00 |
| IRLB8721 (se necessário) | 2 | 1,00 |
| LED 10 W WW + 10 W R | 1+1 | 2,00 |
| GX16-5 IN + OUT | 2 | 4,00 |
| Heatsink / carcaça Al | 1 | 3,00 |
| Lente PMMA 20 mm 90° | 2 | 0,60 |
| Holder lente 20 mm | 2 | 0,40 |
| PCB | 1 | 2,00 |
| **Total** | | **~16** |

Sem ESP, sem USB, sem Wi‑Fi — módulo **~40 % mais barato** que a versão anterior com ESP32-C3.
