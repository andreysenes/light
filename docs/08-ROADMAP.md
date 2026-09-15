# Roadmap

## v0 — atual ✅ / em montagem

| # | Tarefa | Status |
|---|--------|--------|
| 0.1 | Documentação v0 | ✅ |
| 0.2 | Firmware `promicro-4mod` + RGB CC 1–14 | ✅ |
| 0.2b | Tubo flex D5 + gradient wave / chase | ✅ |
| 0.3 | Montar 4 módulos WS2812B + fonte 5V | 🔲 |
| 0.4 | Upload + boot test (R,G,B,W) | 🔲 |
| 0.5 | MIDI no DAW — CC cores + notas C3–F3 | 🔲 |
| 0.6 | Presets PC 0–6 testados | 🔲 |
| 0.7 | Carcaça mecânica básica (opcional) | 🔲 |

## v0.1 — melhorias opcionais

| # | Tarefa |
|---|--------|
| 0.8 | Fade suave entre cores (no firmware) |
| 0.9 | Aumentar para 6–8 módulos (`NUM_MODULES`) |
| 0.10 | Salvar presets em EEPROM |

## v1 — rig de palco (planejado)

Migrar conceito MIDI validado na v0 para hardware de palco:

| # | Marco |
|---|--------|
| 1.1 | Cabeça **ESP32-S3** + MIDI USB |
| 1.2 | Barramento **P4 (24V) + RJ45 (RS-485)** |
| 1.3 | Módulo **Dual 2× 10W** (WW + vermelho) + ATtiny |
| 1.4 | Lente **20mm 90°** |
| 1.5 | Anti-reverso **IRF9540N** na Cabeça |
| 1.6 | `modules.json` — perfis por módulo |

Especificação completa: [v1/README.md](v1/README.md).

## Estrutura do repositório

```
/
├── README.md                 # v0
├── docs/
│   ├── 00–08, DECISAO        # documentação v0
│   └── v1/                   # especificação futura
├── firmware/
│   └── promicro-4mod/        # firmware v0
└── (v1: head/, module/, kicad/ — ainda não criados)
```

## Critério para iniciar v1

- [ ] v0 controla 4 módulos de forma estável no DAW por 1+ ensaio
- [ ] Mapa MIDI (CC + notas) validado
- [ ] Decisão: quantos módulos 10W no rig final (4, 8, 12)
