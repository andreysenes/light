# Publicar no GitHub — `andreysenes/light`

Repositório: **https://github.com/andreysenes/light**

## Remote já configurado neste clone

```bash
git remote -v
# github  git@github.com:andreysenes/light.git
```

## Enviar o código (`main`)

### Opção A — sua máquina (SSH já no GitHub)

```bash
cd /caminho/do/projeto
git remote add github git@github.com:andreysenes/light.git   # se ainda não existir
git push -u github main
```

### Opção B — deploy key (Cloud Agent / CI)

1. Em GitHub → **Settings** → **Deploy keys** → **Add deploy key**
2. Título: `stagemod-light-deploy`
3. Cole a chave pública abaixo, marque **Allow write access**
4. No ambiente com a chave privada correspondente:

```bash
git push -u github main
```

Chave pública (deploy):

```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAICobvdZ+fGsXzpgxzBGd8n2IBgc9Vo86q4Yvb7GDAY9A stagemod-light-deploy
```

### Opção C — HTTPS + token

```bash
git push https://github.com/andreysenes/light.git main
# usuário: andreysenes | senha: Personal Access Token (repo scope)
```

## Espelhar `origin` (Cursor) e GitHub

```bash
git push origin main    # Cursor cloud
git push github main    # GitHub
```
