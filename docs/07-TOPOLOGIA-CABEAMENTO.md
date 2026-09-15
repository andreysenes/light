# Topologia de cabeamento

## Elementos

| Peça | Conector | Função |
|------|----------|--------|
| Fonte | Bornes / IEC / P4 | 24 V AC-DC |
| Cabeça | P4 + RJ45 OUT | MIDI + mestre RS-485 |
| Módulo | P4 IN/OUT + RJ45 IN/OUT | Pass-through energia e dados |
| Cabos | P4 + patch Cat5e | Dois chicotes por salto |

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

Adaptadores **T-P4** e **T-RJ45**: derivação de energia e dados em paralelo.

## Ordem de montagem

1. Fonte **off**.
2. Cabeça na distro; USB no laptop.
3. Par de cabos Cabeça → M1 → M2 … (P4 + Cat5e; LEDs em baixa potência).
4. Medir 24 V em cada IN.
5. Configurar DIP addrs únicos.
6. Upload `modules.json` na Cabeça.
7. Teste MIDI canal a canal.

## Identificação

| Etiqueta | Conteúdo |
|----------|----------|
| Módulo | `StageMod #3 — WW+R — IN← OUT→` |
| Cabo P4 | fita vermelha = lado fonte |
| Cabo Cat5e | azul ou etiqueta `DADOS` |

## RS-485 em split

- D+ e D− em paralelo no T — funciona para ≤ 12 módulos típico.
- Terminação 120 Ω no **último** módulo de **cada** ramo longo.
- Se falhas intermitentes: reduzir splits ou baud 57600.

## Montagem física

- Módulos em perfil 20×20, inclinação 20–35° para wash.
- Cabos com folga; não pendurar peso nos P4/RJ45.
- Cabeça na mesa técnica — USB curto ao laptop.

## Falhas comuns

| Sintoma | Causa |
|---------|-------|
| Módulo 5+ não responde | Addr errado ou terminação faltando no ramo |
| Queda de brilho no fim da cadeia | V+ baixo — injeção |
| Dados OK, LED fraco | Driver mal ajustado (< 900 mA) |
| Um canal sempre off | LED invertido A/B ou perfil JSON errado |
