# LEDs e óptica

## Sua ideia: 1 LED por cor

Está **correta** e é a abordagem mais usada em DIY e em fixtures profissionais de baixo custo.

### Comparação prática

| Item | RGB 10 W integrado | 3× mono 3 W | 3× mono 10 W |
|------|------------------|-------------|--------------|
| Preço unitário (AliExpress) | US$ 3–8 | US$ 0,15–0,50/LED | US$ 0,80–2/LED |
| Corrente típica/canal | ~300–350 mA | ~350 mA | ~900–1050 mA |
| Dissipação | Alta em 1 chip | Espalhada | Requer heatsink sério |
| Sourcing | Difícil 10 W com fios separados | Fácil | Fácil |
| Controle | 3 MOSFETs de qualquer forma | 3 MOSFETs | 3 MOSFETs + driver CC forte |

**Conclusão:** protótipo e primeiros 12 módulos com **3× 3 W mono**. Subir para 10 W só onde faltar luz.

## Part numbers / buscas

Pesquisar em AliExpress, LCSC ou Mouser:

| Cor | Busca típica | Vf @ 350 mA | Observação |
|-----|--------------|-------------|------------|
| Vermelho | `3W red LED star 620nm` | 2,0–2,4 V | ~400 mA máx. |
| Verde | `3W green LED star 520nm` | 3,0–3,4 V | Mais eficiente em lm |
| Azul | `3W blue LED star 460nm` | 3,0–3,4 V | Poucos lm; necessário para mistura |
| Branco quente | `3W warm white 3000K star` | 3,0–3,6 V | Canal WW opcional |

### Alternativa: star RGB 3 W com catodos separados

Produto tipo Adafruit #2530 / “SP3WRGB star PCB”:

- **1 chip**, mas **3 fios de catodo** + ânodo comum.
- Elétricamente idêntico a 3 LEDs mono no mesmo heatsink.
- Bom para protótipo rápido; menos flexível para posicionar óptica.

## Mistura de cores e branco

### RGB only

```
Branco "software" ≈ R: 90%, G: 70%, B: 55%  (ajustar a olho)
Branco frio      ≈ R: 40%, G: 60%, B: 100%
```

Limitações: bandas espectrais estreitas, sombras coloridas, CRI baixo.

### RGB + WW (recomendado para “branco de verdade”)

- Acrescentar 1 LED WW 3 W e 4º MOSFET.
- Branco = acender WW + pequena correção RGB.
- Firmware: modo `WHITE` usa WW; modo `COLOR` usa RGB.

## Óptica e montagem mecânica

| Elemento | Função | Sugestão |
|----------|--------|----------|
| Star PCB | Dissipação | Já vem no LED 3 W |
| Heatsink | 3 W contínuo precisa | Perfil alumínio 40×40 mm ou star com aleta |
| Difusor | Unificar 3 pontos de cor | Lente frosted 60–90° ou papel difusor resistente ao calor |
| Refletor | Direcionalidade | Refletor MR16 DIY ou cone alumínio |

**Regra térmica:** 3 W contínuo em LED star sem ventilação → temperatura de junção alta; em palco (horas ligado) usar pelo menos heatsink pequeno com ventilação passiva.

## Eficiência: não ligar LED direto em 24 V

LED 3 W não é “resistor + 12 V” como LED 5 mm.

Opções de driver (detalhes em [03-ELETRONICA.md](03-ELETRONICA.md)):

1. **Buck CC** (PT4115, XL6001 module) — eficiente, recomendado.
2. **Linear MOSFET + resistor** — simples, gera calor, OK para teste.
3. **Fonte ajustável por canal** — caro, não escalar.

## Quantos módulos para um palco pequeno?

| Cenário | Módulos Spot-S (3×3 W) | Notas |
|---------|------------------------|-------|
| Ensaio em quarto | 2–4 | Parede wash |
| Palco 3×4 m | 8–12 | 4 frente, 4 laterais, 4 trás |
| DJ / festa sala média | 12–16 | Complementar com moving head se necessário |

Luminância total 12× (3×3 W) ≈ 36 chips × ~40 lm ≈ ordem de grandeza de vários PAR64 LED baratos — suficiente para ambiente pequeno/médio.

## Upgrade path

```
Fase 1: 3× 3 W mono + difusor
Fase 2: + canal WW
Fase 3: trocar LEDs por 10 W (mesmo PCB driver com componentes recalculados)
Fase 4: tira LED 12 V 5050 RGB em perfil alumínio como módulo “Bar”
```
