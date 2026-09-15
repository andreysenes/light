# Visão geral do projeto StageMod

## Objetivo

Construir módulos de iluminação para palco/ensaio que:

- Sejam **acopláveis** em cadeia (daisy-chain) ou com derivações em T.
- Respondam a **MIDI** vindos de uma DAW (ou controlador hardware).
- Usem **alimentação segura, barata e prática** (uma fonte central, não um transformador por módulo).
- Permitem **mistura de cores** sem depender de LED RGB 10 W caro ou de difícil sourcing.

## O que NÃO é (ainda)

- Produto comercial certificado (sem norma EN/ABNT nesta fase).
- Sistema DMX profissional (pode ser evolução futura).
- Painel LED de vídeo / pixel mapping denso.

## Princípio de cada módulo

Cada módulo é uma **unidade luminosa endereçável**:

```
┌─────────────────────────────────────────┐
│  IN (24V, GND, RS485 A/B)               │
│       │                                 │
│  ┌────┴────┐    ┌──────────┐           │
│  │ ESP32   │───►│ 3–4 ch.  │──► LEDs   │
│  │ (C3/S3) │    │ driver   │    R G B  │
│  └────┬────┘    └──────────┘    (WW)  │
│       │                                 │
│  OUT (24V, GND, RS485 A/B)              │
└─────────────────────────────────────────┘
```

- **Master** (primeiro módulo ou caixa separada): recebe MIDI USB, traduz para comandos no barramento RS-485.
- **Satélites**: recebem comando “módulo #N, R=, G=, B=” e aplicam PWM nos MOSFETs.

## Decisão sobre LEDs (sua dúvida)

| Abordagem | Prós | Contras |
|-----------|------|---------|
| **1× LED RGB 10 W integrado** | Menos LEDs físicos | Caro, dissipação concentrada, canais acoplados termicamente |
| **3× LED mono 3 W (R, G, B)** | Barato (~US$ 0,15–0,50/cor), fácil de repor, controle independente | 3 pontos de luz (pode usar difusor) |
| **1× star RGB 3 W (ânodo comum, 3 fios catodo)** | Barato (~US$ 2–3), já montado em star | Mesmas limitações de mistura de branco |
| **RGB + WW 3 W** | Branco quente/neutro de qualidade | +1 canal driver + LED |

**Recomendação:** começar com **3× LED mono 3 W** (ou 1 star RGB 3 W com catodos separados — é o mesmo elétrico). Escalar para **3× 10 W mono** só se a luminância de 3 W for insuficiente após testes.

### Branco

- **Branco por software:** R+G+B (~70–80 % de cada canal) — funciona, mas cor do branco é “fria” e CRI baixo.
- **Branco melhor:** adicionar LED **warm white 3000 K** ou **neutral white 4000 K** 3 W como 4º canal.
- Para wash de palco pequeno, RGB puro costuma bastar; para câmera/gravação, vale o canal WW.

## Potência por módulo (estimativa)

| Configuração | Corrente máx. @ 24 V barramento* | Observação |
|--------------|----------------------------------|------------|
| 3× 3 W RGB | ~0,5–0,7 A no barramento** | Com drivers buck CC eficientes |
| 3× 10 W RGB | ~1,5–2 A | Requer heatsink maior |

\* O barramento alimenta os drivers; a corrente no barramento é menor que a soma dos LEDs se usar conversão buck.

\** Cada canal ~350 mA @ 2,2–3,4 V nos LEDs; perdas nos drivers.

## Glossário

| Termo | Significado |
|-------|-------------|
| Daisy-chain | Módulos ligados IN → OUT → IN → OUT em série |
| Split / T | Derivação do barramento para ramos paralelos |
| Injeção de energia | Reconectar V+ em ponto intermediário para compensar queda de cabo |
| CC constante | Driver que mantém corrente no LED (recomendado > 1 W) |
| RS-485 | Barramento serial diferencial, robusto em cabos longos |

## Riscos e mitigação

| Risco | Mitigação |
|-------|-----------|
| Alimentar LED de alto watt pelo ESP | Fonte 24 V externa; ESP só com 5 V derivado |
| MOSFET errado (não logic-level) | IRLB8721 / AO3400A; verificar curva @ Vgs=3,3 V |
| Cabo fino + muitos módulos | 24 V, AWG 18–16 no tronco, fusível por módulo |
| MIDI apenas por Wi‑Fi instável | USB MIDI no master como padrão; Wi‑Fi opcional |
