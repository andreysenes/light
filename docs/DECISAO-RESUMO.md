# Resumo das decisões — leitura rápida

## Uma cabeça, módulos burros

```
DAW ──USB──► [ESP32 Cabeça] ── P4 + RJ45 ── [Mod]──[Mod]──[Mod]
```

- **Só 1 ESP32** no sistema (na Cabeça).
- Módulos = **ATtiny** + 2 drivers + 2 LEDs (sem Wi‑Fi, sem USB).

## Cabos baratos (sem chicote especial)

| Chicote | Conector | Função |
|---------|----------|--------|
| **Energia** | **P4** (5,5×2,1 mm, centro +) | 24 V + GND |
| **Dados** | **RJ45** + Cat5e | RS-485 (pin 4-5) |

Dois cabos por salto — muito mais barato que conector aviação. Detalhes: [09-CABLAGEM.md](09-CABLAGEM.md).

## Módulo: 2 cores × 10 W + lente 20 mm

| Canal | Padrão | Potência | Óptica |
|-------|--------|----------|--------|
| A | Warm white 3000 K | 10 W | Lente **20 mm 90°** |
| B | Vermelho | 10 W | Lente **20 mm 90°** |

- **1 lente 90° por LED** — feixe fixo em todo o rig; melhor dispersão e mais lux na mancha útil.
- Mesma placa para todas as combinações — troca LED, lente reaproveita.
- Detalhes: [12-LENTE-20MM.md](12-LENTE-20MM.md).

## Configuração futura (exemplos)

| Módulo | Ch A | Ch B |
|--------|------|------|
| 1 | verde | vermelho |
| 2 | warm white | warm white |
| 3 | vermelho | âmbar |

Arquivo `modules.json` na Cabeça — ver [11-CONFIGURACAO-MODULOS.md](11-CONFIGURACAO-MODULOS.md).

## Alimentação e proteção

- Fonte **24 V** → **Cabeça P4 IN** → **P4 OUT** alimenta todo o rig (única fonte).
- **Anti-reverso na Cabeça:** P-MOS **IRF9540N** no barramento de saída — cabo invertido não queima módulos.
- ~**1,2 A por módulo**; 8 módulos → fonte **24 V / 10 A**.
- Polyfuse **10 A** na Cabeça + **2 A** em cada módulo.

## Primeira compra (protótipo)

| Item | Qtd |
|------|-----|
| ESP32-S3 DevKit | 1 (Cabeça) |
| MAX485 | 2 (cabeça + 1 módulo) |
| ATtiny1614 | 1 |
| LED 10 W WW + 10 W red | 1+1 |
| Buck CC 1 A | 2 |
| IRF9540N anti-reverso (Cabeça) | 1 |
| Plug P4 + patch Cat5e | 1 par de cabos |
| Fonte 24 V 5 A | 1 |
| Heatsink alumínio | 1 |

~**US$ 42** para validar Cabeça + 1 módulo + par de cabos P4/Cat5e.

## Próximo passo

[08-ROADMAP.md](08-ROADMAP.md) — Fase 1: Cabeça + 1 módulo Dual + cabo patch.
