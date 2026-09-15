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

## Óptica e mecânica

| Elemento | Especificação |
|----------|---------------|
| Star PCB | 20 mm padrão, furo M3 |
| Heatsink | Perfil Al ≥ 80 mm ou carcaça inteira em Al |
| Difusor | Lente 60–90° frosted ou PMMA opal (cuidado com calor) |
| Beam | 120° típico em star — aceitável para wash |

Dois pontos de luz (A e B) próximos (~15–25 mm) + difusor comum unificam a mancha.

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
