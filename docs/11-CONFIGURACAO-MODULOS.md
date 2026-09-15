# Configuração de módulos — combinações de cores

O hardware é **sempre o mesmo**: 2 canais × 10 W. O que muda entre módulos é **qual LED está soldado em cada soquete** e **como a Cabeça mapeia MIDI** para esse módulo.

## Modelo mental

```
         ┌────────────── Cabeça ESP32 ──────────────┐
         │  MIDI → lógica → RS-485                  │
         │  modules.json: addr → (tipo A, tipo B)   │
         └──────────────────┬───────────────────────┘
                            │ Cabo StageMod
         ┌──────────────────┼──────────────────────┐
         ▼                  ▼                      ▼
    Mod 1 (WW+R)      Mod 2 (WW+WW)         Mod 3 (R+Amb)
    DIP addr=1        DIP addr=2            DIP addr=3
```

- **Endereço físico** = DIP no módulo (posição na rede).
- **Perfil lógico** = tipos dos canais A e B (config na Cabeça).
- **LED físico** = deve corresponder ao tipo configurado.

## Exemplos de rig

| Módulo | Addr | Ch A | Ch B | Uso típico |
|--------|------|------|------|------------|
| 1 | 1 | warm_white | red | Wash quente + acento vermelho |
| 2 | 2 | warm_white | warm_white | Wash branco forte |
| 3 | 3 | red | amber | Sunset / fogo |
| 4 | 4 | green | red | Contraste cênico |
| 5 | 5 | red | red | Backlight vermelho duplo |
| 6 | 6 | warm_white | amber | Pele / warmth |

## Como reconfigurar um módulo

### Só software (mesmos LEDs)

Alterar `modules.json` na Cabeça — útil para renomear papéis MIDI sem abrir o módulo.

### Trocar cor física

1. Desligar fonte 24 V.
2. Substituir star LED no soquete A ou B.
3. Atualizar `ch_a` / `ch_b` na config.
4. Religar; Cabeça envia PING para validar presença do addr.

### EEPROM no módulo (fase futura)

Opcional: byte em ATtiny EEPROM `TYPE_A`, `TYPE_B` para o módulo reportar à Cabeça na boot:

```
PONG: [addr][type_a][type_b]
```

Cabeça sincroniza automaticamente — útil com muitos módulos.

## Paleta MIDI sugerida

### Modo Performance (por cor semântica)

| Nota MIDI | Ação |
|-----------|------|
| C3 | Todos os canais `red` → velocity |
| D3 | Todos os canais `warm_white` |
| E3 | Todos os canais `amber` |
| F3 | Todos os canais `green` |
| G3 | Blackout global |

### Modo Técnico (por módulo)

| CC | Função |
|----|--------|
| CC 20 | Selecionar addr 1–16 |
| CC 21 | Nível ch A |
| CC 22 | Nível ch B |

## Presets (Program Change)

| PC | Nome | Descrição |
|----|------|-----------|
| 0 | Blackout | Tudo zero |
| 1 | Warm wash | WW em todos os canais WW |
| 2 | Red mood | Red 80 %, WW 20 % nos módulos WW+R |
| 3 | Full warm | Todos WW 100 % |
| 4 | Fire | Amber+red nos módulos configurados |

Presets armazenados em flash da Cabeça.

## Regras de consistência

| Situação | Comportamento |
|----------|---------------|
| Config diz `green`, LED físico é red | Luz acende, cor errada — responsabilidade do instalador |
| Addr DIP duplicado | Dois módulos respondem ao mesmo frame — **evitar** |
| Módulo offline | Cabeça marca slot ausente após 3× PING falho |
| Canal `off` | Driver desligado, PWM 0 |

## Catálogo de LEDs 10 W (referência de compra)

| Tipo | Busca AliExpress/LCSC | Vf @ 1 A |
|------|----------------------|----------|
| warm_white | `10W warm white LED star 3000K` | 9–12 V* |
| red | `10W red LED star 620nm` | 6–9 V* |
| amber | `10W amber LED star 590nm` | 9–12 V* |
| green | `10W green LED star` | 9–12 V* |

\* Muitos stars 10 W são **3 chips em série** — usar driver **CC 900 mA**, não tensão fixa.

## Matriz de combinações válidas

Qualquer par `(tipo_A, tipo_B)` onde cada tipo ∈ catálogo acima. Total teórico: N² combinações; na prática 6–8 tipos cobrem palco pequeno.

**Padrão de estoque:** comprar módulos todos **WW + R**; comprar stars avulsas para conversão field.
