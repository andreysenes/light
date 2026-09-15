# Roadmap

## Fase 0 — Decisões (atual) ✅

- [x] Arquitetura modular RS-485 + 24 V
- [x] LED: 3× mono 3 W (não RGB 10 W integrado)
- [x] Controle: MIDI USB via ESP32-S3 master
- [x] BOM e topologia documentados

## Fase 1 — Protótipo único (próximo)

| # | Tarefa | Critério de aceite |
|---|--------|-------------------|
| 1.1 | Breadboard 1× R, G, B com MOSFET + PT4115 | 350 mA/canal estável |
| 1.2 | Firmware PWM manual (serial) | Fade suave sem flicker |
| 1.3 | USB MIDI → 3 canais | DAW controla R,G,B |
| 1.4 | Teste térmico 1 h @ 80 % PWM | Heatsink < 70 °C |

**Entregável:** pasta `firmware/prototype-single/` (futuro).

## Fase 2 — Dois módulos + barramento

| # | Tarefa |
|---|--------|
| 2.1 | Adicionar MAX485 em dois ESP32 |
| 2.2 | Implementar protocolo SET_RGBW |
| 2.3 | Cabo 4 pinos 2 m entre módulos |
| 2.4 | Endereçamento DIP |

## Fase 3 — PCB e mecânica

| # | Tarefa |
|---|--------|
| 3.1 | Esquemático KiCad módulo satélite |
| 3.2 | PCB 80×80 mm, revisão térmica |
| 3.3 | Carcaça impressa 3D ou perfil alumínio |
| 3.4 | Difusor |

## Fase 4 — Rig 8–12 módulos

| # | Tarefa |
|---|--------|
| 4.1 | Distro 24 V + fusíveis |
| 4.2 | Cabos padronizados 0,5 / 1 / 2 m |
| 4.3 | Presets MIDI no master |
| 4.4 | Documentar layout de palco exemplo |

## Fase 5 — Opcional

- Canal WW em módulos selecionados
- MIDI DIN IN
- Portal web de configuração
- Saída DMX512 do master (para integrar com mercado pro)
- Art-Net para controle sem cabo USB

## Perguntas em aberto (decidir na Fase 1)

1. **Brilho alvo:** 3 W basta ou já projetar PCB para 10 W?
2. **Form factor:** spot quadrado vs barra linear?
3. **Quantos módulos** na primeira compra de componentes?
4. **DAW principal** para testes de mapeamento?

## Estrutura de repositório prevista

```
/
├── README.md
├── docs/           # especificação (atual)
├── firmware/
│   ├── master/     # ESP32-S3 MIDI + RS-485
│   └── satellite/  # ESP32-C3 PWM
├── hardware/
│   ├── kicad/      # esquemático + PCB
│   └── mechanical/ # STL, perfis
└── tools/
    └── midi-test/  # scripts Python para teste sem DAW
```
