# LEDs e óptica — 2× 10 W por módulo

## Padrão do módulo Dual

| Soquete | LED padrão | Potência | Corrente driver |
|---------|------------|----------|-----------------|
| **A** | Warm white **3000 K** | 10 W | ~900 mA CC |
| **B** | Vermelho **620–630 nm** | 10 W | ~900 mA CC |

Um LED mono por canal — sem RGB integrado.

## Por que warm white + vermelho

| Uso em palco | Cor |
|--------------|-----|
| Wash / iluminação geral | Warm white |
| Clima, drama, backlight | Vermelho |
| “Branco” adicional | Segundo WW em módulo configurado WW+WW |

Combinação barata, LEDs fáceis de encontrar, bom para ensaio e shows pequenos.

## LEDs 10 W — o que comprar

Stars 10 W costumam ter **3 chips em série** no mesmo PCB:

| Cor | Busca | Vf total @ 900 mA | lm aprox. |
|-----|-------|-------------------|-----------|
| Warm white | `10W warm white LED star 3000K` | 9–12 V | 800–900 |
| Red | `10W red LED star 620nm` | 6–9 V | 300–400 |
| Amber | `10W amber LED star 590nm` | 9–12 V | 400–500 |
| Green | `10W green LED star` | 9–12 V | 600–700 |

**Nunca** ligar star 10 W direto em 24 V sem driver CC.

## Catálogo para módulos configuráveis

Mesmo soquete mecânico; estoque sugerido além do padrão:

| Tipo | Quando usar |
|------|-------------|
| `warm_white` | Wash, pele, ambiente |
| `cool_white` | Luz fria / industrial |
| `red` | Drama, alarme |
| `amber` | Sunset, fogo |
| `green` | Ambiente, terror, natureza |
| `blue` | Frio, night club (fase 2) |

Config na Cabeça: [11-CONFIGURACAO-MODULOS.md](11-CONFIGURACAO-MODULOS.md).

## Driver e elétrica

| Canal | Vf @ 900 mA | Potência LED |
|-------|-------------|--------------|
| Red | ~2,4–2,8 V × 3 chips | ~7–8 W útil |
| WW | ~3,2 V × 3 chips | ~9–10 W |

Módulo buck CC ajustado para **900 mA** (ou 1050 mA se star suportar).

PWM no pino EN/DIM do driver — ver [03-ELETRONICA.md](03-ELETRONICA.md).

## Óptica — lente 20 mm por LED

Cada star 10 W recebe **1 lente óptica de 20 mm** (PMMA) + holder, para dispersar o feixe de forma controlada e aproveitar melhor os lúmens na área do palco.

| Elemento | Especificação |
|----------|---------------|
| Lente | **Ø 20 mm PMMA**, feixe **90°** (padrão wash) ou 60° (frente estreita) |
| Holder | Anel 20 mm fixado no heatsink/PCB |
| Star PCB | 20 mm, furo M3 — compatível com kits lens+holder comuns |
| Folga LED–lente | 0,5–1,5 mm (PMMA não suporta contato quente) |
| Heatsink | Perfil Al ≥ 80 mm; lente não substitui dissipação |
| Centros A–B | 28–32 mm entre eixos das duas lentes |

Especificação completa: [12-LENTE-20MM.md](12-LENTE-20MM.md).

### Efeito prático

- Star nu ≈ 120° — muita luz perdida nas bordas do módulo.
- Lente 90° ≈ lux **2–4× maior** na mancha útil a 1–2 m (mesma potência elétrica).
- WW e Red mantêm manchas distintas mas com overlap ajustável pela distância entre lentes.

## Branco sem segundo canal RGB

- **Warm white** já entrega branco de qualidade (CRI melhor que RGB misturado).
- Módulo **WW + WW** = dobro de fluxo branco.
- Não é necessário RGB para o caso de uso atual.

## Potência e calor

| Cenário | Dissipação módulo |
|---------|-------------------|
| Só WW 100 % | ~12 W no heatsink |
| WW + Red 100 % | ~22–25 W |
| Red only | ~10 W |

Regra: se não aguenta toque prolongado, aumentar heatsink ou reduzir duty cycle no show.

## Upgrade por módulo

Trocar star 10 W por **20 W** no futuro exige novo driver (1,5 A+) e heatsink maior — manter 10 W na v1.
