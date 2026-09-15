# Alimentação — v0 (5V)

## Fonte

| Item | Especificação |
|------|----------------|
| Tensão | **5 V DC** |
| Corrente mínima | **1 A** (recomendado **2 A**) |
| Tipo | USB charger, buck 5V, fonte bench |

## Dimensionamento

| Carga | Corrente |
|-------|----------|
| 4× WS2812B branco 100% | ~**240 mA** |
| Pro Micro | ~**50 mA** |
| 4 módulos apenas | ~300 mA |
| + tubo 30 LED | ~**2 A** |
| + tubo 60 LED | ~**3,5 A** |
| + tubo 4 m (200 LED) | ~**12 A** pico branco total / **~2,5 A** nominal (manual: 3,1 W/m) |

| Config | Fonte 5V |
|--------|------------|
| Só 4 módulos | **1 A** |
| Módulos + tubo curto (≤1 m) | **3 A** |
| Módulos + tubo **4 m** (D15) | **5 A** mínimo / **10 A** se branco alto + injeção 5V a cada ~2 m |

## Como ligar

```
[Fonte 5V] ──┬── (+) Pro Micro VCC
             ├── (+) Módulo1…4 VCC (em paralelo ou cadeia)
             └── (−) GND comum a todos
```

### USB do PC

- OK para **programar** e testar **1 LED**
- **Não** recomendado para 4 LEDs full white contínuo (limite ~500 mA do USB com risco de queda)

## Limitação de módulos @ 5V

| Fator | Limite v0 |
|-------|-----------|
| Firmware | **4 módulos** (`NUM_MODULES`) |
| Corrente | Escala linear — 8 LEDs ≈ 500 mA → fonte 1A ainda OK |
| Queda de tensão | AWG fino longo → cores instáveis no fim da cadeia |

Para **mais brilho** ou **muitos módulos**, planejar **v1** com 24V — [v1/README.md](v1/README.md).

## Tabela rápida

| LEDs WS2812 @ 5V | Corrente max ~ | Fonte sugerida |
|------------------|----------------|----------------|
| 4 | 0,25 A | 1 A |
| 8 | 0,5 A | 1 A |
| 16 | 1 A | 2 A |
| 32 | 2 A | 3 A |

## Erros a evitar

| Erro | Consequência |
|------|--------------|
| Ligar 24V nos WS2812B | Destrói LEDs |
| GND desconectado | Comportamento errático / sem comunicação |
| Sem capacitor no 1º LED | Piscadas aleatórias |
