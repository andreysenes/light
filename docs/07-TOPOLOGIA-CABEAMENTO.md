# Topologia de cabeamento e acoplamento

## Padrão linear (simples)

```
[PSU]──[M1]──[M2]──[M3]──[M4]──[M5]── ...
```

- Um único cabo “mãe” sai da distro.
- Cada módulo: IN recebe, OUT repassa para o próximo.
- RS-485 e 24 V percorrem o **mesmo** caminho físico.

**Vantagem:** cabeamento mínimo, fácil de entender.  
**Limite:** comprimento total e queda de tensão no fim da cadeia.

## Padrão com splits (seu desenho)

```
                         ┌──[M5]
                         ├──[M6]
[PSU]──[M1]──[M2]──[M3]──[M4]──┤
                         ├──[M7]
                         └──[M8]

[M4]──[M9]──[M10]──[M11]──[M12]
```

### Como implementar fisicamente

**Opção 1 — Cabo T (Y)**  
Conector IN em M4; dois cabos OUT (um para ramo M5–M8, outro para M9–M12). Requer **adaptador T** com 1 IN + 2 OUT na distro ou em M4.

**Opção 2 — Dupla saída no módulo**  
PCB com 2 conectores OUT (paralelo elétrico V+/GND/A/B). Raro em produtos comerciais; útil em DIY.

**Opção 3 — Distro central + hastes**  
Todos os cabos voltam à caixa de distro (estrela elétrica). RS-485 ainda em daisy-chain lógica ou repetidor no master.

Para palco pequeno, **Opção 1** com cabos prontos de comprimento fixo (0,5 m / 1 m / 2 m) é a mais prática.

## Diagrama elétrico do cabo de módulo

```
Conector IN (macho/fêmea conforme padrão escolhido)
  Pin1 V+  ──────────────────────────────► Pin1 V+  OUT
  Pin2 GND ──────────────────────────────► Pin2 GND OUT
  Pin3 A   ──────────────────────────────► Pin3 A   OUT
  Pin4 B   ──────────────────────────────► Pin4 B   OUT
```

Par A/B: **cabo trançado** (par do ethernet ou fita 2 condutores).

## Comprimentos típicos

| Ligação | Comprimento | AWG V+/GND |
|---------|-------------|------------|
| PSU → M1 | 1–2 m | 16–18 |
| Módulo → módulo adjacente | 0,5–1 m | 18 |
| Split → ramo lateral | 1–2 m | 18 |
| Injeção distro → meio do ramo | conforme | 16 |

## Identificação

- Etiqueta em cada módulo: **ID** (1–12) + seta IN/OUT.
- Cabos codificados por cor ou comprimento (evita inverter IN/OUT).

## Terminação RS-485

- Jumper **120 Ω** entre A e B no **último** módulo de **cada** ramo lógico longo.
- Ramo curto (2 módulos): terminação opcional.

## Montagem em truss / palco

```
        [M1]   [M2]   [M3]   [M4]   ← frente
          \    /        \    /
           [PSU+Master na lateral]
```

- Fixar módulos em perfil 20×20 com inclinação ~30° para baixo (wash).
- Cabos presos com abraçadeira, folga para desmontagem.

## Ordem de ligação na instalação

1. Fonte **desligada**.
2. Montar cadeia mecânica IN→OUT sem LEDs ligados (só eletrônica).
3. Ligar fonte; medir 24 V em cada IN.
4. Ligar master USB; ping RS-485 módulo a módulo.
5. Conectar LEDs; testar canal a canal em baixa intensidade.

## Falhas comuns

| Sintoma | Causa provável |
|---------|----------------|
| Último módulo reinicia | Queda V+; injetar energia |
| Cor errática em um ramo | A/B invertidos ou falta terminação |
| Só módulo 1 responde | Endereço DIP igual em todos |
| Ruído MIDI | GND USB laptop ruim; usar hub alimentado |
