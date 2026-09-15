# Alimentação segura, barata e prática

## Estratégia geral

**Uma fonte central 24 V DC** alimenta todos os módulos em paralelo no barramento, com pass-through IN→OUT em cada módulo.

Por que **24 V** e não 12 V?

| Tensão | Corrente para ~200 W | Queda em cabo 5 m AWG18 (2 A) |
|--------|----------------------|-------------------------------|
| 12 V | ~17 A | ~0,5 V (4 % útil) |
| 24 V | ~8 A | ~0,5 V (2 % útil) |

24 V permite cabos mais finos e splits mais longos antes de injeção.

## Dimensionamento da fonte

Estimativa: **módulo Spot-S** ≈ 12–18 W nos LEDs + 1 W eletrônica ≈ **15–20 W** no pior caso.

| Módulos | Potência LED | Fonte 24 V sugerida | Margem |
|---------|--------------|---------------------|--------|
| 4 | ~60–80 W | 24 V / **5 A** (120 W) | OK |
| 8 | ~120–160 W | 24 V / **10 A** (240 W) | OK |
| 12 | ~180–240 W | 24 V / **15 A** (360 W) | OK |
| 16 | ~240–320 W | 24 V / **20 A** (480 W) | + injeção |

**Regra:** fonte a **≥ 125 %** da carga contínua máxima.

## Fontes recomendadas (BOM)

| Tipo | Exemplo | Preço ref. | Notas |
|------|---------|------------|-------|
| Mean Well CLG-150-24 | 24 V 6,3 A | US$ 25–35 | IP67, confiável |
| Mean Well LRS-200-24 | 24 V 8,5 A | US$ 20–30 | Bancada / rack |
| Genérica 24 V 10 A | “24V 10A switching” | US$ 12–18 | Testar ripple; OK protótipo |
| Notebook + boost | — | — | **Não** recomendado > 50 W |

Entrada: **100–240 V AC** com cabo IEC com terra.

## Distribuição no palco

```
                    ┌──── injeção V+ (cabo grosso AWG14)
                    │
[Fonte 24V]───[Distro box]───┬── tronco ── M1─M2─M3─M4
                             │
                             └── ramo ── M9─M10─M11
```

### Distro box (barato, DIY)

Caixa com:

- Entrada: IEC + **fusível 10–20 A** + interruptor.
- Saídas: 2–4× XT60 ou bornes 24 V.
- **Barramento GND** comum.
- Opcional: voltímetro barato.

Custo: < R$ 50 em peças.

## Pass-through no módulo

Cada módulo:

```
IN V+ ── polyfuse 1.5A ──┬── buck local (ESP/drivers)
                         └── OUT V+ (sem queda intencional)
IN GND ──────────────────┬── GND placa
                         └── OUT GND
```

**Não** usar trilha fina de PCB para passar 5 A; no protótipo usar fio AWG18 entre conectores.

## Injeção de energia — quando?

Injetar V+ de novo da distro quando:

- Queda medida **> 1 V** no último módulo do ramo, ou
- Mais de **4 módulos Spot-S** em série no mesmo cabo fino, ou
- Ramo > **5 m** de cabo total.

Injeção = segundo cabo 24 V do distro ao conector IN do módulo intermediário (só V+ e GND; RS-485 continua em série).

## Fusíveis e proteção

| Local | Valor | Tipo |
|-------|-------|------|
| Entrada fonte | 10–20 A | Fusível de vidro / automotivo |
| Cada módulo | 1,5–2 A | Polyfuse recuperável |
| Cada ramo distro | 5 A | Automotivo |

## Aterramento

- **Terra da rede** → carcaça da fonte (se metálica).
- **GND 24 V** é retorno de corrente; não flutuar.
- Conectores metálicos: shell ligado ao GND **em um ponto** (fonte), não em todos os módulos (evita loop).

## O que NÃO fazer

| Erro | Risco |
|------|-------|
| Alimentar 10 W LED pelo pin 5 V do ESP | Queima ESP e USB do PC |
| Fonte 12 V 1 A para 8 módulos | Queda, reset, fogo no cabo |
| Sem fusível por módulo | Falha em um módulo derruba barramento |
| Polaridade invertida em XT30 | Destrói drivers |

## Custo alimentação (12 módulos, exemplo)

| Item | Qtd | ~US$ |
|------|-----|------|
| Fonte 24 V 15 A | 1 | 25 |
| Distro + fusíveis | 1 | 10 |
| Cabo silicone 2× AWG18 20 m | 1 | 15 |
| Conectores XT30 par | 15 | 10 |
| **Total** | | **~60** |

(LEDs e MCUs são custo separado na BOM principal.)

## Alternativa ultra-barata (ensaio em casa)

- Fonte **12 V 5 A** de câmera/CFTV.
- Máximo **2–3 módulos** Spot-S com buck local.
- Migrar para 24 V antes de montar rig completo.
