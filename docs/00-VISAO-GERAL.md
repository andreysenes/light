# Visão geral do projeto StageMod

## Objetivo

Construir módulos de iluminação para palco/ensaio que:

- Sejam **acopláveis** em cadeia ou com derivações em T.
- Respondam a **MIDI** de uma DAW.
- Usem **um único ESP32** como cabeça de controle.
- Levem **energia e dados no mesmo cabo** (Cabo StageMod).
- Sejam **simples por módulo**: 2 cores × 10 W (padrão warm white + vermelho).
- Permitam **reconfiguração futura** de combinações de cor (verde+vermelho, WW×2, vermelho+âmbar, …).

## Arquitetura resumida

```
┌─────────────┐     Cabo StageMod        ┌──────────────────┐
│ Cabeça      │  (24V + GND + D+ + D−)   │ Módulo Dual      │
│ ESP32-S3    │ ═══════════════════════► │ ATtiny + 2×10W   │
│ MIDI USB    │                          │ WW + Red (padrão)│
└─────────────┘                          └────────┬─────────┘
                                                  │ OUT
                                                  ▼
                                            próximo módulo ...
```

## O que cada peça faz

| Peça | Tem ESP? | Função |
|------|----------|--------|
| **Cabeça** | Sim (único) | MIDI, presets, RS-485 master, `modules.json` |
| **Módulo** | Não (só ATtiny) | Decodifica addr, PWM em 2 canais, acende LEDs |
| **Cabo StageMod** | — | Alimenta e comunica |
| **Fonte 24 V** | — | Energia de todo o rig |

## Módulo padrão vs configurável

**Hardware sempre igual:** 2 drivers, 2 soquetes star 10 W, IN/OUT StageMod.

**O que varia:**

| Variável | Como mudar |
|----------|------------|
| Cores | Trocar LED no soquete A ou B |
| Papel MIDI | Editar `modules.json` na Cabeça |
| Posição na rede | DIP addr no módulo |

Exemplos:

| Módulo | Ch A | Ch B |
|--------|------|------|
| 1 | warm_white | red |
| 2 | warm_white | warm_white |
| 3 | red | amber |
| 4 | green | red |

Detalhes: [11-CONFIGURACAO-MODULOS.md](11-CONFIGURACAO-MODULOS.md).

## LEDs — 10 W por cor

- **1 LED mono por canal** (não RGB integrado).
- Padrão: **warm white 3000 K** + **vermelho 620 nm**.
- Driver **corrente constante ~900 mA** por canal.
- Dissipação: **~20 W** por módulo → heatsink obrigatório.

## Potência e barramento

| Grandeza | Valor típico |
|----------|--------------|
| Por canal | 10 W |
| Por módulo (2 ch) | ~20 W LED + perdas |
| Corrente @ 24 V / módulo | ~1,0–1,2 A |
| 8 módulos full | ~8–10 A → fonte 24 V / 10 A |

## Glossário

| Termo | Significado |
|-------|-------------|
| Cabeça | Única unidade com ESP32 |
| Cabo StageMod | Cabo 5 vias energia + RS-485 |
| Módulo Dual | Bloco 2× 10 W com IN/OUT |
| Addr | Endereço DIP no módulo |
| Perfil | Par (tipo_A, tipo_B) na config da Cabeça |

## Riscos e mitigação

| Risco | Mitigação |
|-------|-----------|
| Superaquecimento 10 W | Heatsink, teste 30 min @ 100 % |
| Curto no cabo StageMod | Conector keyed, fusível por módulo |
| Addr duplicado | Etiquetar módulos na montagem |
| Cabeça offline | Blackout automático nos módulos (fade local opcional) |
