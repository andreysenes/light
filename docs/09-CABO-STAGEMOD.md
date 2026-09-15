# Cabo StageMod — energia + dados em um só chicote

O **Cabo StageMod** é o elemento que une todos os módulos: transporta **24 V + GND** e o barramento de **dados RS-485** no mesmo cabo blindado, com conector padronizado em cada ponta.

## Por que um cabo dedicado

| Abordagem | Problema |
|-----------|----------|
| Fonte + cabo de dados separados | Dois chicotes por ligação, erro de montagem |
| RJ45 só dados + XT30 só energia | Conectores diferentes IN/OUT, frágil em palco |
| **StageMod 5 condutores** | **Um plug, uma direção, energia + dados** |

## Especificação elétrica

### Condutores (5 vias)

| Via | Sinal | Seção AWG | Função |
|-----|-------|-----------|--------|
| 1 | **V+** 24 V DC | **16** (tronco) / **18** (patch 0,5–1 m) | Alimentação módulos |
| 2 | **GND** | 16 / 18 | Retorno + referência RS-485 |
| 3 | **D+** (RS-485 A) | 24 AWG trançado | Dados diferencial + |
| 4 | **D−** (RS-485 B) | 24 AWG trançado | Dados diferencial − |
| 5 | **Shield** | malha | Blindagem; ligar ao GND **só na cabeça** |

Par D+/D−: **par trançado** com twist ~15–30 twists/m dentro do cabo.

### Conector — padrão StageMod (proposta)

| Pino | Sinal | Tipo fêmea IN | Tipo macho OUT |
|------|-------|---------------|----------------|
| 1 | V+ 24 V | socket (recebe) | pin |
| 2 | GND | pin | socket |
| 3 | D+ | pin | socket |
| 4 | D− | socket | pin |
| 5 | Shield | NC ou shell | shell |

**Chave de polaridade:** pino 1 em V+ no lado que recebe da fonte evita ligar cabo invertido com curto (keyed connector).

#### Opções mecânicas

| Fase | Conector | Custo par | Notas |
|------|----------|-----------|-------|
| Protótipo | **GX16-5** aviação | ~US$ 2 | 5 pinos, robusto, fácil |
| Produção | **Amphenol LPTC 5 pos** ou **Molex Mini-Fit Jr 5p** | US$ 4–8 | Melhor ciclo de vida |
| DIY rápido | 2× **XT30** (V+/GND) + 1× **RJ45** (dados only) | ~US$ 1,50 | Não é cabo único — só para teste |

**Recomendação:** GX16-5 (M16 5 pinos) como padrão StageMod v1.

### Pinagem GX16-5 (fixa no projeto)

```
Vista frontal (plug macho, pinos numerados sentido horário a partir do keyway):

        [1 V+]
    [5 SH]   [2 GND]
        [4 D−]
        [3 D+]
```

Documentar em etiqueta em cada módulo: **IN ← cabo da cabeça / OUT → próximo módulo**.

## Tipos de cabo na instalação

| Nome | Comprimento | AWG V+/GND | Uso |
|------|-------------|------------|-----|
| **Tronco** | 1–3 m | 16 | Cabeça → primeiro módulo, injeção distro |
| **Patch** | 0,3–0,8 m | 18 | Módulo adjacente |
| **Ramo** | 1–2 m | 18 | Split em T para lateral |
| **Injeção** | conforme | 16 | Distro → meio do ramo (só V+/GND ou cabo completo) |

## Montagem do cabo (DIY)

Materiais por cabo patch 0,5 m:

1. Cabo **5 condutores** + malha (ex. `LiYCY 5×0.75 mm²` ou AWG18 + par 24 AWG).
2. 2× conector GX16-5 (macho + fêmea).
3. Termorretrátil + capa de nylon opcional.

Passos:

1. Crimpar/soldar pinos; D+ e D− mantidos como par até o conector.
2. Shield cortado no módulo (não continuar shield módulo a módulo em cadeia longa).
3. Testar continuidade e **ausência de curto V+ ↔ GND** antes de ligar fonte.

## Pass-through no módulo

```
IN GX16 ──┬── V+ ── polyfuse ──┬── drivers LED
          ├── GND ─────────────┤
          ├── D+ ── MAX485 A ──┼── OUT GX16 (mesmos pinos)
          └── D− ── MAX485 B ──┘
```

Trilhas de V+ no PCB: largura ≥ 2 mm ou fio AWG18 entre conectores (até ~2 A contínuo por módulo).

## Split em T

Adaptador **T-StageMod** (peça separada ou PCB):

```
        OUT ramo A
            │
IN ─────────┼──────── OUT tronco
            │
        OUT ramo B
```

V+, GND, D+, D− em paralelo nos três conectores. RS-485 em estrela funciona para < 12 módulos em palco pequeno.

## Limites elétricos

| Parâmetro | Valor |
|-----------|-------|
| Tensão máx. V+ | 28 V DC |
| Corrente contínua por cabo patch 18 AWG | 3 A |
| Corrente tronco 16 AWG | 10 A |
| Baud RS-485 | 115200 (padrão) / 250000 (futuro) |

## Identificação visual

- Cabos **pretos** = patch curto.
- Cabos **cinza** = tronco longo.
- Ponta com **anel vermelho** = lado V+ (cabeça/fonte).

## Checklist antes do primeiro energizar

- [ ] Ohmímetro: V+ ↔ GND > 10 kΩ sem LEDs quentes
- [ ] D+ ↔ D−: ~60–120 Ω só no último módulo da linha (terminação ligada)
- [ ] Shield ligado em **um** ponto (caixa cabeça)
- [ ] Pinagem IN/OUT não invertida
