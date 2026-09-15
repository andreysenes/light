# Arquitetura modular — cabeça única

## Princípio

| Peça | Inteligência | Função |
|------|--------------|--------|
| **Cabeça** | ESP32-S3 | MIDI, presets, config de módulos, mestre RS-485 |
| **Módulo Dual** | ATtiny (decoder) | 2× PWM → 2× driver 10 W → 2× LED |
| **Cabos P4 + RJ45** | — | Energia 24 V e dados RS-485 separados |

Não há ESP32 nos módulos. Isso reduz custo, calor e complexidade em cada ponto de luz.

## Diagrama do sistema

```mermaid
flowchart LR
    subgraph daw [DAW]
        MIDI[USB MIDI]
    end

    subgraph head [Cabeça — único ESP32]
        ESP[ESP32-S3]
        RS_M[MAX485]
        ESP --> RS_M
    end

    subgraph cable [P4 + RJ45]
        V24[P4 24V]
        DP[Cat5e RS-485]
    end

    subgraph mod [Módulo Dual — repetível]
        RS_S[MAX485]
        MCU[ATtiny]
        DRV[2× driver 10W]
        LED[LED A + LED B]
        RS_S --> MCU --> DRV --> LED
    end

    MIDI --> ESP
    RS_M --> cable
    cable --> mod
    mod --> cable
```

## Cabeça (Head Unit)

Caixa separada na mesa ou no rack — **não** compartilha dissipação com LEDs.

| Bloco | Componente |
|-------|------------|
| MCU | ESP32-S3 DevKit ou módulo USB |
| Barramento | MAX485 (half-duplex) |
| Entrada | P4 IN — fonte 24 V |
| **Proteção** | **P-MOS anti-reverso** no barramento → **P4 OUT** (única saída de energia) |
| Alimentação local | Buck 24→5 V (do barramento protegido) |
| Interface | USB MIDI para DAW |
| Armazenamento | `modules.json` em SPIFFS/LittleFS |

Saída: **P4** (24 V) + **RJ45** (dados) → primeiro módulo (ou distro + tronco).

### Funções firmware Cabeça

1. Receber MIDI (notas, CC, Program Change).
2. Resolver perfil de cada módulo (`ch_a`, `ch_b` por addr).
3. Enviar frames `SET_LEVELS` no RS-485.
4. Watchdog: blackout se USB desconectado (configurável).
5. (Futuro) Portal web para editar `modules.json`.

## Módulo Dual (satélite passivo)

Ver detalhes em [10-MODULO-DUAL.md](10-MODULO-DUAL.md).

Resumo:

- **2 canais × 10 W** — padrão warm white + vermelho.
- PCB **universal** — outras cores = trocar star LED + config na Cabeça.
- Endereço: **DIP switch** (3–4 bits).
- Conectores: **P4 IN/OUT** (pass-through 24 V) + **RJ45 IN/OUT** (pass-through dados).

## Cablagem

Especificação completa: [09-CABLAGEM.md](09-CABLAGEM.md).

| Chicote | Conector | Função |
|---------|----------|--------|
| Energia | **P4** 5,5×2,1 mm | 24 V, centro + |
| Dados | **RJ45** + Cat5e | RS-485 pin 4-5 |

## Por que RS-485 no cabo de palco

| Barramento | Cabeça única + módulos simples |
|------------|-------------------------------|
| I2C | Alcance curto, ruído |
| DMX512 | Viável (fase futura como modo compatível) |
| **RS-485** | **Cat5e + RJ45**, barato, 100 m+ |
| Wi‑Fi por módulo | Descartado (sem ESP no módulo) |

## Endereçamento e configuração

| Camada | Onde | O quê |
|--------|------|-------|
| Física | DIP no módulo | Addr 1–15 |
| Lógica | Cabeça `modules.json` | Tipo cor ch A, ch B |
| Física LED | Soquete star | LED 10 W correspondente |

Exemplos de perfis: [11-CONFIGURACAO-MODULOS.md](11-CONFIGURACAO-MODULOS.md).

## Split em T

```
[Cabeça]═══[M1]═══[M2]═══[M3]═══[M4]═══ ...
                              ├════ [M5]
                              ├════ [M6]
                              └════ [M9]═══[M10]═══ ...
```

- Adaptador **T-P4** + **T-RJ45** ou distro com várias saídas.
- RS-485 em derivação: OK até ~12 módulos em palco pequeno.
- Ramo com muitos módulos 10 W → **injeção V+** da fonte (ver [04-ALIMENTACAO.md](04-ALIMENTACAO.md)).

## Dimensionamento rápido

| Módulos | Potência LED máx. | Corrente 24 V (barramento)* | Fonte |
|---------|-------------------|----------------------------|-------|
| 4 | 80 W | ~4 A | 24 V / 6 A |
| 8 | 160 W | ~8 A | 24 V / 10 A |
| 12 | 240 W | ~12 A | 24 V / 15 A |

\* Com drivers buck eficientes; cada módulo ~1–1,2 A @ 24 V em full blast.

## Tamanho físico alvo

| Peça | Dimensão alvo |
|------|---------------|
| Cabeça | Caixa 120×80×40 mm |
| Módulo Dual | 100×100×45 mm (heatsink integrado) |
| Cabo patch | 0,3–0,8 m entre módulos |
