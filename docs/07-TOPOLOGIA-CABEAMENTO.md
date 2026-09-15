# Topologia de cabeamento

## Elementos

| Peça | Conector | Função |
|------|----------|--------|
| Fonte | Bornes / IEC | 24 V AC-DC |
| Cabeça | GX16 IN (fonte) + GX16 OUT (StageMod) | MIDI + mestre RS-485 |
| Módulo | GX16 IN + OUT | Pass-through energia + dados |
| Cabo | StageMod 5 vias | Liga tudo |

## Linear simples

```
[Fonte]──[Cabeça]═══[M1]═══[M2]═══[M3]═══[M4]═══ ...
```

## Split (layout de palco)

```
[Fonte]──[Cabeça]═══[M1]═══[M2]═══[M3]═══[M4]═══┬═══[M5]
                                                  ├═══[M6]
                                                  ├═══[M7]
                                                  ├═══[M8]
                                                  └──═[M9]═══[M10]═══ ...
```

Adaptador **T-StageMod**: 1 IN, 2 OUT — pinos 1–4 em paralelo.

## Ordem de montagem

1. Fonte **off**.
2. Cabeça na distro; USB no laptop.
3. Cabo tronco Cabeça → M1 → M2 … (só eletrônica, LEDs em baixa potência).
4. Medir 24 V em cada IN.
5. Configurar DIP addrs únicos.
6. Upload `modules.json` na Cabeça.
7. Teste MIDI canal a canal.

## Identificação

| Etiqueta | Conteúdo |
|----------|----------|
| Módulo | `StageMod #3 — WW+R — IN← OUT→` |
| Cabo patch | comprimento + `StageMod` |
| Cabo tronco | anel vermelho no lado V+ |

## RS-485 em split

- D+ e D− em paralelo no T — funciona para ≤ 12 módulos típico.
- Terminação 120 Ω no **último** módulo de **cada** ramo longo.
- Se falhas intermitentes: reduzir splits ou baud 57600.

## Montagem física

- Módulos em perfil 20×20, inclinação 20–35° para wash.
- Cabos com folga; não pendurar peso no GX16.
- Cabeça na mesa técnica — USB curto ao laptop.

## Falhas comuns

| Sintoma | Causa |
|---------|-------|
| Módulo 5+ não responde | Addr errado ou terminação faltando no ramo |
| Queda de brilho no fim da cadeia | V+ baixo — injeção |
| Dados OK, LED fraco | Driver mal ajustado (< 900 mA) |
| Um canal sempre off | LED invertido A/B ou perfil JSON errado |
