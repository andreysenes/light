# Conectores XLR — v0

Conectores **XLR 3 pinos** para ligar o **tubo neon** e os **módulos WS2812B** com cabo de palco (desmontagem rápida, padrão familiar).

## O que vai em cada XLR (3 fios)

| Pino XLR | Sinal | Função |
|----------|-------|--------|
| **1** | **GND** | Terra comum (shell do XLR também ligado ao GND) |
| **2** | **+5V** | Alimentação DC |
| **3** | **DATA** | Linha addressable (DIN / DOUT) |

**Não é áudio:** não ligar em mesa/microfone. Etiquetar cabos: `5V PIXEL — NÃO PHANTOM`.

### Convenção IN / OUT (módulos)

| Conector no módulo | Tipo | Ligação interna |
|--------------------|------|-----------------|
| **Entrada** | XLR **fêmea** (painel) | 5V/GND passam; **DATA → [470Ω] → DIN**; **cap** 5V/GND no LED |
| **Saída** | XLR **macho** (painel) | 5V/GND passam; **DOUT → DATA** do cabo |

Os módulos ligam em **cadeia na DATA** (série lógica), não em paralelo na linha de dados:

```
Cabeça ──DATA──► Mod1 ──DATA──► Mod2 ──DATA──► Mod3 ──DATA──► Mod4
         5V/GND em paralelo em todos os pontos (mesma fonte)
```

**5V e GND** são **paralelos** em todo o rig (fonte, tubo, cada módulo). Só a **DATA** “salta” de módulo em módulo via DOUT→DIN.

## Cabeça (Pro Micro)

Montagem recomendada: caixa **Medusa** com XLR no painel — [17-CABECA-MEDUSA.md](17-CABECA-MEDUSA.md).

Dois ramos de dados no firmware:

| Ramo | Pino MCU | Destino |
|------|----------|---------|
| Módulos | **D6** | XLR → entrada do **Módulo 1** |
| Tubo | **D5** | XLR → entrada do **tubo** (único conector hoje) |

```
                    ┌── XLR OUT "MÓDULOS" (D6 + 5V + GND) ──► Mod1 IN
[Fonte 5V]──┬──[Pro Micro]
            └── XLR OUT "TUBO"   (D5 + 5V + GND) ──► Tubo IN
```

Resistor **470Ω** entre **D6** e o pino 3 do XLR dos módulos; outro **470Ω** entre **D5** e o pino 3 do XLR do tubo (pode ficar na cabeça ou no primeiro centímetro do cabo).

## Tubo (4 m, um XLR hoje)

| Situação | Ligação |
|----------|---------|
| **Agora** | Um cabo XLR da cabeça **TUBO** → XLR do tubo (5V, GND, DATA no D5) |
| **Futuro: 4× 1 m** | Cada metro com **IN + OUT** XLR; DATA em cadeia: Cabeça → T1 → T2 → T3 → T4 |

```
Hoje:
  Cabeça (D5) ──XLR──► [ Tubo 4 m ]

Futuro (4 segmentos):
  Cabeça (D5) ──► [T1] ──► [T2] ──► [T3] ──► [T4]
                  IN/OUT   IN/OUT   IN/OUT   IN/OUT
```

- `NUM_TUBE_LEDS` continua **200** (50 LED/m × 4 m) se a cadeia DATA for contínua.
- Com **4 m**, injete **+5V e GND** de novo no **meio** do tubo (e opcionalmente em cada segmento de 1 m), mesmo usando XLR — o pino 2/1 carregam corrente; fio fino no cabo XLR longo pode aquecer.

## Diagrama módulos (XLR)

```
     XLR IN (F)              WS2812B              XLR OUT (M)
  Pin1 GND ──────────────── GND ───────────────── Pin1 GND
  Pin2 5V  ────┬─────────── 5V  ───────────────── Pin2 5V
               │ [470µF–1000µF]
  Pin3 DATA ──[470Ω]──► DIN    DOUT ───► Pin3 DATA
```

Ordem na cadeia: **Mod1** (C3) → **Mod2** (D3) → **Mod3** (E3) → **Mod4** (F3).

## Cabos

| Cabo | Comprimento típico | Observação |
|------|-------------------|------------|
| Cabeça → Mod1 | 0,5–2 m | DATA = saída D6 |
| Mod → Mod | 0,3–1 m | Macho do anterior → fêmea do próximo |
| Cabeça → tubo | 1–5 m | DATA = saída D5 |
| Segmento tubo → tubo | 0,2–0,5 m | Só ao dividir em 1 m |

Use condutor **AWG 18–20** no par 5V/GND se o cabo alimentar trecho longo de LED; AWG 22–24 basta para DATA curta.

## O que comprar (AliExpress)

| Item | Busca |
|------|-------|
| XLR 3 pinos fêmea painel | `XLR 3 pin female panel mount connector` |
| XLR 3 pinos macho painel | `XLR 3 pin male panel mount connector` |
| Cabo microfone (para montar) | `microphone cable 2 core + shield` — usar condutores para 5V e DATA; malha = GND |

Marcas de palco (Neutrik, etc.) aguentam melhor corrente e encaixe; clones baratos servem para protótipo com corrente moderada.

## Limitações

| Tema | Detalhe |
|------|---------|
| Corrente no XLR | Contatos típicos **≤ 5–8 A** por par; tubo 4 m: preferir **fonte na cabeça** + **injeção 5V** no tubo com cabo mais grosso, não só pelo XLR longo |
| Dois DATA | Tubo (D5) e módulos (D6) **não** compartilham o mesmo pino 3 — são **dois cabos XLR** da cabeça (ou um cabo 5 pinos, se padronizar depois) |
| Mistura com áudio | Pinagem parecida com alguns usos, mas tensão é **5 V DC** — risco se plugar em entrada de linha |

## Checklist de montagem

1. Definir pinagem **1=GND, 2=+5V, 3=DATA** em todos os conectores.
2. Shell do XLR ligado ao **GND** em ambos os lados.
3. Testar continuidade antes de ligar a fonte.
4. Primeiro teste: **1 módulo** + cabo XLR; depois cadeia completa + tubo.
5. Etiquetas: `MOD`, `TUBO`, `D5`, `D6`, direção **IN → OUT**.

## Referências

- Cabos gerais: [07-CABLAGEM.md](07-CABLAGEM.md)
- Tubo D15 / 200 LEDs: [14-TUBO-FLEX.md](14-TUBO-FLEX.md)
- Firmware D5/D6: [firmware/promicro-4mod/](../firmware/promicro-4mod/)
