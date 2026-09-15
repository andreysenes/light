# Resumo das decisões — leitura rápida

## Uma cabeça, módulos burros

```
DAW ──USB──► [ESP32 Cabeça] ═══ Cabo StageMod ═══ [Mod]──[Mod]──[Mod]
```

- **Só 1 ESP32** no sistema (na Cabeça).
- Módulos = **ATtiny** + 2 drivers + 2 LEDs (sem Wi‑Fi, sem USB).

## Cabo especial StageMod

**5 fios em um cabo** + conector **GX16-5**:

| Fio | Função |
|-----|--------|
| 1 | V+ 24 V |
| 2 | GND |
| 3 | D+ |
| 4 | D− |
| 5 | Shield |

Especificação: [09-CABO-STAGEMOD.md](09-CABO-STAGEMOD.md).

## Módulo: 2 cores × 10 W + lente 20 mm

| Canal | Padrão | Potência | Óptica |
|-------|--------|----------|--------|
| A | Warm white 3000 K | 10 W | Lente **20 mm 90°** |
| B | Vermelho | 10 W | Lente **20 mm 90°** |

- **1 lente por LED** — melhor dispersão e mais lux na mancha útil (mesma potência elétrica).
- Mesma placa para todas as combinações — troca LED, lente reaproveita.
- Detalhes: [12-LENTE-20MM.md](12-LENTE-20MM.md).

## Configuração futura (exemplos)

| Módulo | Ch A | Ch B |
|--------|------|------|
| 1 | verde | vermelho |
| 2 | warm white | warm white |
| 3 | vermelho | âmbar |

Arquivo `modules.json` na Cabeça — ver [11-CONFIGURACAO-MODULOS.md](11-CONFIGURACAO-MODULOS.md).

## Alimentação

- Fonte **24 V** central.
- ~**1,2 A por módulo** em carga máxima.
- 8 módulos → fonte **24 V / 10 A**.
- Fusível na entrada + polyfuse em cada módulo.

## Primeira compra (protótipo)

| Item | Qtd |
|------|-----|
| ESP32-S3 DevKit | 1 (Cabeça) |
| MAX485 | 2 (cabeça + 1 módulo) |
| ATtiny1614 | 1 |
| LED 10 W WW + 10 W red | 1+1 |
| Buck CC 1 A | 2 |
| GX16-5 macho+fêmea | 2 pares |
| Fonte 24 V 5 A | 1 |
| Heatsink alumínio | 1 |

~**US$ 45** para validar Cabeça + 1 módulo + 1 cabo.

## Próximo passo

[08-ROADMAP.md](08-ROADMAP.md) — Fase 1: Cabeça + 1 módulo Dual + cabo patch.
