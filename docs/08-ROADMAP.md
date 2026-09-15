# Roadmap

## Fase 0 — Decisões ✅

- [x] **Cabeça única** ESP32-S3
- [x] Cablagem **P4 + RJ45** (energia e dados separados)
- [x] Módulo **2× 10 W** — padrão WW + vermelho
- [x] Hardware universal + **config futura** de cores
- [x] Decoder **ATtiny** no módulo (não ESP)

## Fase 1 — Protótipo (atual)

| # | Tarefa | Aceite |
|---|--------|--------|
| 1.1 | Montar **Cabeça**: ESP32 + MAX485 + **anti-reverso IRF9540N** + MIDI USB | Envia frame teste; teste P4 invertido |
| 1.2 | Montar **1 módulo Dual** WW+R | 900 mA/canal medido |
| 1.3 | Fabricar **1 par cabos** 0,5 m: P4 + Cat5e/RJ45 | P4 centro +; pin 4-5 dados |
| 1.4 | **Anti-reverso P-MOS** no P4 IN | Cabo invertido não aquece placa |
| 1.5 | Protocolo SET_LEVELS addr=1 | Fade suave A e B |
| 1.6 | Montar **lentes 20 mm 90°** + holder em A e B | Folga 0,5–1,5 mm; feixe sem obstrução |
| 1.7 | Teste térmico 30 min 100 % | Heatsink < 65 °C; PMMA sem deformar |
| 1.8 | MIDI do DAW → ambos canais | Reaper ou Ableton |

## Fase 2 — Config e segundo módulo

| # | Tarefa |
|---|--------|
| 2.1 | `modules.json` na Cabeça |
| 2.2 | Segundo módulo (ex. WW+WW) |
| 2.3 | Cabos patch P4 + Cat5e × 3 |
| 2.4 | Modo Performance (notas por cor semântica) |
| 2.5 | Adaptadores T-P4 e T-RJ45 DIY |

## Fase 3 — PCB

| # | Tarefa |
|---|--------|
| 3.1 | KiCad: PCB módulo Dual |
| 3.2 | KiCad: PCB Cabeça (ou usar DevKit) |
| 3.3 | KiCad: adaptadores T-P4 e T-RJ45 |
| 3.4 | Carcaça alumínio com aberturas Ø20 mm |
| 3.5 | Validar mancha 90° a 1 m e 2 m de distância |

## Fase 4 — Rig 8+ módulos

| # | Tarefa |
|---|--------|
| 4.1 | Distro 24 V + fusíveis |
| 4.2 | Estoque stars amber/green |
| 4.3 | Presets Program Change |
| 4.4 | Documentar layout palco exemplo |

## Fase 5 — Opcional

- EEPROM tipo LED no módulo (auto-discovery)
- MIDI DIN na Cabeça
- DMX OUT da Cabeça
- Portal web config Wi‑Fi (só Cabeça)

## Estrutura de repositório

```
/
├── README.md
├── docs/
│   ├── 09-CABLAGEM.md
│   ├── 10-MODULO-DUAL.md
│   └── 11-CONFIGURACAO-MODULOS.md
├── firmware/
│   ├── head/          # ESP32-S3 MIDI + RS-485
│   └── module/        # ATtiny decoder
├── hardware/
│   ├── kicad/
│   └── cable/         # pinagem P4 + RJ45
└── config/
    └── modules.json.example
```

## Perguntas em aberto

1. Quantos módulos na **primeira compra** (4, 8, 12)?
2. **DAW** principal para mapear presets?
3. Cabeça em **caixa de mesa** ou montada no truss junto ao M1?
