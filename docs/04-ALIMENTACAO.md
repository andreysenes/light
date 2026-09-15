# Alimentação — 24 V, módulos 2× 10 W

## Carga por módulo Dual

| Estado | Potência LED | Corrente barramento 24 V* |
|--------|--------------|---------------------------|
| 1 canal 100 % | ~10 W | ~0,5–0,6 A |
| 2 canais 100 % | ~20 W | ~1,0–1,2 A |
| Standby (PWM 0) | < 1 W | ~0,05 A |

\* Com drivers buck ~90 % eficiência.

## Dimensionamento fonte

| Módulos | Corrente máx. estimada | Fonte 24 V |
|---------|------------------------|------------|
| 4 | ~5 A | 6 A (150 W) |
| 8 | ~10 A | 10 A (240 W) |
| 12 | ~15 A | 15 A (360 W) |

Margem: **125 %** da carga contínua.

A **Cabeça** consome < 0,5 A adicional (ESP + buck).

## Onde ligar a fonte

```
[Fonte 24V] ──► [Distro] ──┬──► [Cabeça] (alimenta ESP + passa V+ ao cabo OUT)
                           │
                           └──► [Injeção opcional em ramos longos]
```

A Cabeça **não precisa** estar no caminho de corrente dos LEDs — pode ser derivação curta da distro. O cabo StageMod da Cabeça leva V+ em paralelo ao barramento dos módulos.

## Cabo StageMod e corrente

| AWG V+/GND | Corrente contínua segura | Uso |
|------------|--------------------------|-----|
| 18 | ~3 A | Patch entre módulos |
| 16 | ~10 A | Tronco da distro à Cabeça / injeção |

Queda de tensão alvo: **< 0,5 V** no pior módulo.

## Injeção de energia

Necessária quando:

- Mais de **4 módulos** num ramo com cabo 18 AWG, ou
- Ramo > **5 m** de comprimento total de V+.

Segundo cabo 16 AWG da distro ao IN de um módulo intermediário (V+ e GND; dados continuam em série).

## Proteção

| Local | Proteção |
|-------|----------|
| Entrada fonte | Fusível 10–20 A + interruptor |
| Cada módulo IN | Polyfuse **2 A** |
| Cabeça IN | Polyfuse 3 A |
| TVS | SMBJ24A em cada módulo |

## Aterramento e shield

- Shield do Cabo StageMod: ligar ao GND **na Cabeça** (um ponto).
- Nos módulos: shield não continuar em cadeia longa (evitar loop).
- Terra da rede (IEC) na carcaça da fonte.

## Distro box (DIY)

- IEC + fusível + 2–4 saídas GX16 ou XT60.
- Voltímetro opcional.
- ~US$ 10–12 em peças.

## Erros a evitar

| Erro | Consequência |
|------|--------------|
| Fonte 12 V 5 A para 8 módulos 10 W | Queda, reset, cabo quente |
| Sem fusível por módulo | Um curto derruba o rig |
| GX16 subdimensionado na corrente | Conector derrete @ 2 A contínuo — usar pinos V+/GND AWG16 no tronco |
