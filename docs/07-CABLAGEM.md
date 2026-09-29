# Cablagem — v0

**Conectores XLR (opcional):** pinagem e cadeia módulos + tubo — [16-XLR-CONECTORES.md](16-XLR-CONECTORES.md).

Cada ligação entre módulos usa **3 fios** (ou **XLR 3 pinos** com a mesma função):

| Fio | Função |
|-----|--------|
| **Vermelho** | 5V |
| **Preto** | GND |
| **Branco/verde** | DATA (WS2812B) |

## Diagrama completo

```
[Fonte 5V] ──┬── VCC Pro Micro
             ├── VCC ──┬── Mod1 ──┬── Mod2 ──┬── Mod3 ──┬── Mod4
             └── GND ──┴── GND ───┴── GND ───┴── GND ───┴── GND

Pro Micro D6 ──[470Ω]──► DATA IN Mod1 ──► OUT ──► IN Mod2 ──► ... ──► Mod4
Pro Micro D5 ──[470Ω]──► DATA tubo neon (cabo XLR separado dos módulos)
```

## Por módulo (padrão StageMod)

**Cada um dos 4 módulos** leva **470 Ω** na entrada de DATA e **capacitor** na alimentação do LED.

```
     XLR IN (ou chicote IN)
  Pin3 DATA ──[470Ω]──► DIN    DOUT ───► DATA OUT (→ próximo módulo)
  Pin2 5V  ──┬── VCC LED
  Pin1 GND ──┴── GND LED
              │
         [470µF–1000µF]
         entre 5V e GND
              │
  Pin2/1 pass-through ───────► XLR OUT (5V/GND)
```

| Componente | Onde no módulo |
|------------|----------------|
| **470 Ω** | Entre **DATA IN** (pino 3 do XLR) e **DIN** do WS2812B |
| **470 µF–1000 µF** (≥ 6,3 V) | Entre **5 V** e **GND** do LED (o mais perto possível do chip) |

A **Medusa** mantém capacitor no barramento 5 V e **470 Ω** nas saídas **D5** e **D6** antes dos XLR MOD/TUBO — ver [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md).

## Ordem da cadeia

| Posição | Índice | Nota MIDI |
|---------|--------|-----------|
| Mais perto do Pro Micro | 0 | C3 |
| 2º | 1 | D3 |
| 3º | 2 | E3 |
| Último | 3 | F3 |

**Importante:** DATA sai do **DOUT** de um módulo e entra no **DIN** do próximo.

## Comprimentos sugeridos

| Trecho | Comprimento |
|--------|-------------|
| Pro Micro → Mod 1 | 10–30 cm |
| Mod → Mod | 20–50 cm |
| DATA total | < 1 m ideal |

## Identificação

| Etiqueta | Significado |
|----------|-------------|
| `MOD 1` … `MOD 4` | Ordem na cadeia |
| Seta no DATA | IN → OUT |

## Montagem — ordem

1. Fonte **desligada**
2. Soldar GND comum em todos
3. Soldar 5V em todos
4. Ligar DATA: D6 → Mod1 → Mod2 → Mod3 → Mod4
5. Em **cada** módulo: soldar **470 Ω** (DATA IN → DIN) e **cap** (5V/GND no LED)
6. Ligar fonte; verificar boot RGB

## Splits / topologia

v0 usa **uma linha** apenas:

```
[Pro Micro]──[M1]──[M2]──[M3]──[M4]
```

Splits em T na linha DATA **não** são suportados sem repetidor — planejado para v1.

## v1 cablagem

P4 + RJ45 — [v1/09-CABLAGEM.md](v1/09-CABLAGEM.md).
