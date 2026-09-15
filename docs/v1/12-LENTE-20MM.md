# Lente óptica 20 mm v1 — um por LED

> **Planejado v1** — não implementado. v0 usa WS2812B sem lente dedicada.


Cada canal do módulo Dual usa **1 lente de 20 mm** sobre o star 10 W, para concentrar o fluxo útil na área iluminada e reduzir desperdício lateral.

## Por que lente em cada LED

| Sem lente (star nu) | Com lente 20 mm |
|---------------------|-----------------|
| Emissão ~120° Lambertiana — muita luz nas laterais e no gabinete | Feixe controlado **90°** |
| Mancha irregular a 1–2 m | Mancha mais uniforme no palco |
| Parede/gabinete aquece sem contribuir para o wash | Mais lm “úteis” na zona alvo |
| Dois pontos de cor muito separados visualmente | Cada cor com mancha definida; overlap configurável |

A potência elétrica é a mesma (10 W); o ganho é **eficiência óptica aparente** — mesma corrente, mais lux onde importa.

## Especificação StageMod v1

| Parâmetro | Valor recomendado |
|-----------|-------------------|
| Diâmetro lente | **20 mm** |
| Material | **PMMA** (acrílico óptico) |
| Ângulo de feixe | **90°** (fixo em todo o projeto) |
| Compatibilidade LED | Star **20 mm**, chip COB/LED central ~9–14 mm |
| Quantidade por módulo | **2** (uma em A, uma em B) |

### Busca para compra

| Item | Termos AliExpress / LCSC |
|------|--------------------------|
| Lente 90° | `20mm LED lens 90 degree PMMA` |
| Suporte | `20mm LED lens holder bracket` |
| Kit | `20mm lens + holder for 1W 3W 5W 10W LED` |

Verificar na ficha: diâmetro **20 mm**, altura total da lente **~10–12 mm**, diâmetro interno compatível com face emissiva do star 10 W.

## Montagem mecânica

### Stack típico (cada canal)

```
        ┌─────────────┐
        │ Lente 20 mm │  ← PMMA, face côncava/convexa para o LED
        ├─────────────┤
        │ Holder / anel│  ← nylon ou alumínio, prende na PCB ou heatsink
        ├─────────────┤
        │  Star 10 W  │  ← pasta térmica no heatsink
        ├─────────────┤
        │  Heatsink   │
        └─────────────┘
```

### Regras de montagem

| Regra | Motivo |
|-------|--------|
| **Folga 0,5–1,5 mm** entre dome do LED e lente | PMMA deforma > ~85 °C |
| Lente **não** encostar no phosphor/die | Hotspot e degradação |
| Holder fixado no **heatsink ou PCB**, não só na lente | Vibração em palco |
| Abertura frontal do módulo ≥ 20 mm por ótica | Não cortar o feixe |
| WW e Red podem usar **mesmo ângulo** (90°) | Simplifica estoque |

### Posição dos dois LEDs no módulo

```
Vista frontal (exemplo):

    ┌────────────────────────────┐
    │   (○) Lente A    (○) Lente B   │   ← centros ~28–32 mm
    │    WW 20mm        Red 20mm     │
    └────────────────────────────┘
```

- Centro a centro: **28–32 mm** (lentes 20 mm quase encostadas com borda mínima).
- Ambas as lentes em **90°**: overlap da mancha a **~1 m** ajuda wash unificado entre WW e vermelho.

## Ângulo de feixe: 90° (padrão único)

Todo módulo StageMod usa **somente lente 90°** nos canais A e B.

| Parâmetro | Valor |
|-----------|-------|
| Ângulo | **90°** |
| Uso | Wash largo, parede, palco pequeno/médio |
| Distância típica | 1–2,5 m do módulo à superfície iluminada |
| Estoque | Comprar **apenas 90°** — simplifica montagem e reposição |

## Compatibilidade térmica

| Material | Tmax contínuo | Notas |
|----------|---------------|-------|
| PMMA | ~80–90 °C | OK com folga de ar e heatsink adequado |
| Silicone óptico | ~150 °C | Alternativa se lente encostar perto do LED |
| Vidro | Alto | Pesado, raro em 20 mm DIY |

Teste de aceite: 30 min @ 100 % PWM — lente não deve amolecer nem embacar permanentemente.

## Efeito na dissipação

A lente **não reduz** calor no star; o heatsink deve ser dimensionado igual (10 W/canal).

O holder pode ter **furos de ventilação** laterais para convecção entre star e lente.

## BOM por módulo (óptica)

| Qty | Item | ~US$ |
|-----|------|------|
| 2 | Lente PMMA 20 mm 90° | 0,40–0,80 |
| 2 | Holder / anel 20 mm | 0,30–0,60 |
| — | Parafuso M3 ou clip (se holder exigir) | 0,10 |
| | **Subtotal óptica / módulo** | **~1,00** |

## Integração na PCB (fase KiCad)

- Furos de fixação do holder alinhados ao star (padrão 20 mm star: 2× furo M3 ou 1× central).
- Silkscreen: círculo **Ø20** = zona da lente.
- Keep-out: altura **12 mm** acima do star para carcaça frontal.

## Reposição

Lente danificada: trocar por outra **90°** idêntica. Não alterar `modules.json`.
