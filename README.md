# ssv6x5x

Driver Wi‑Fi `ssv6x5x` compilado para **Armbian sunxi kernel 5.15.93**.

Este repositório contém uma adaptação do driver `ssv6x5x` para chipsets Wi‑Fi da família SSV6x5x, comuns em algumas TV boxes e dispositivos embarcados.

A release `5.15.93` inclui:

- Driver Wi‑Fi compilado: `ssv6x5x-armbian-5.15.93-sunxi.tar.gz`
- Instalador dos headers do kernel: `armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz`
- Arquivos `.sha256` para verificação de integridade

## Compatibilidade

Esta release foi preparada para:

```text
Kernel: 5.15.93-sunxi
Distribuição alvo: Armbian / sunxi
```

Antes de instalar, confira a versão do kernel em execução:

```bash
uname -r
```

O resultado esperado deve ser:

```text
5.15.93-sunxi
```

Se o seu kernel for diferente, o módulo pode falhar ao carregar com erro como `invalid module format`.

## Download da release 5.15.93

A release fixa está disponível em:

```text
https://github.com/jhonathanc/ssv6x5x/releases/tag/5.15.93
```

Para baixar diretamente pelo terminal:

```bash
mkdir -p ~/ssv6x5x-driver
cd ~/ssv6x5x-driver

wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

Opcionalmente, baixe também o instalador dos headers:

```bash
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

## Verificar integridade dos arquivos

Depois do download, valide os checksums:

```bash
sha256sum -c ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

Se também baixou os headers:

```bash
sha256sum -c armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

A saída esperada deve indicar `OK`.

## Instalação do driver pré-compilado

Extraia o pacote do driver:

```bash
tar -xzf ssv6x5x-armbian-5.15.93-sunxi.tar.gz
```

Entre no diretório extraído, se ele tiver sido criado:

```bash
ls
```

Localize o arquivo do módulo:

```bash
find . -name "*.ko"
```

Instale o módulo no diretório do kernel atual:

```bash
sudo mkdir -p /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x
sudo cp $(find . -name "*.ko" | head -n 1) /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x/
sudo depmod -a
```

Carregue o driver:

```bash
sudo modprobe ssv6x5x
```

Caso o nome do módulo seja diferente, verifique o nome do arquivo `.ko`:

```bash
find . -name "*.ko"
```

E carregue usando o nome correto, sem a extensão `.ko`:

```bash
sudo modprobe NOME_DO_MODULO
```

## Instalação de arquivos de firmware/configuração

Se o pacote extraído incluir arquivos de firmware ou configuração, copie-os para `/lib/firmware`:

```bash
sudo cp $(find . -name "*.bin") /lib/firmware/ 2>/dev/null || true
sudo cp $(find . -name "*.cfg") /lib/firmware/ 2>/dev/null || true
```

Se existir o arquivo `ssv6x5x-wifi.cfg`, copie-o explicitamente:

```bash
sudo cp ssv6x5x-wifi.cfg /lib/firmware/ 2>/dev/null || true
```

## Reiniciar o sistema

Após instalar o driver, reinicie:

```bash
sudo reboot
```

Depois do reboot, verifique se a interface Wi‑Fi apareceu:

```bash
ip link
```

Também é útil conferir os logs do kernel:

```bash
dmesg | grep -i ssv
```

ou:

```bash
dmesg | grep -i wifi
```

## Instalação dos headers do kernel

Os headers são necessários caso você queira compilar o driver manualmente ou preparar o ambiente de build.

Baixe e extraia o pacote:

```bash
mkdir -p ~/ssv6x5x-headers
cd ~/ssv6x5x-headers

wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
tar -xzf armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
```

Verifique o conteúdo extraído:

```bash
ls -la
```

Se houver um script de instalação, dê permissão e execute:

```bash
chmod +x *.sh
sudo ./*.sh
```

Se houver pacotes `.deb`, instale com:

```bash
sudo dpkg -i *.deb
sudo apt -f install
```

Depois, confirme se o diretório de build do kernel existe:

```bash
ls -la /lib/modules/$(uname -r)/build
```

## Compilando manualmente

Caso queira compilar o driver a partir do código-fonte, instale as dependências:

```bash
sudo apt update
sudo apt install -y build-essential git
```

Clone o repositório:

```bash
git clone https://github.com/jhonathanc/ssv6x5x.git
cd ssv6x5x
```

Carregue as variáveis de build, se necessário:

```bash
source ./vars
```

Compile:

```bash
make -j$(nproc)
```

Instale:

```bash
sudo make install
sudo depmod -a
sudo modprobe ssv6x5x
```

Reinicie:

```bash
sudo reboot
```

## Scripts auxiliares

O repositório também pode incluir scripts auxiliares:

- `load.sh`: carrega o driver
- `unload.sh`: descarrega o driver
- `remove_old_driver.sh`: remove versões antigas do driver
- `vars` / `vars.sh`: configura variáveis de ambiente para build

Exemplo:

```bash
chmod +x load.sh unload.sh remove_old_driver.sh
sudo ./load.sh
```

## Solução de problemas

### Verificar se o módulo foi carregado

```bash
lsmod | grep ssv
```

### Verificar logs do driver

```bash
dmesg | grep -i ssv
```

### Erro `invalid module format`

Esse erro normalmente indica que o driver foi compilado para uma versão de kernel diferente da que está em execução.

Confira:

```bash
uname -r
modinfo ssv6x5x
```

A release `5.15.93` é destinada ao kernel:

```text
5.15.93-sunxi
```

### Interface Wi‑Fi não aparece

Confira se o módulo foi carregado:

```bash
lsmod | grep ssv
```

Confira se os arquivos de firmware/configuração foram copiados:

```bash
ls -la /lib/firmware | grep -i ssv
```

Confira as mensagens do kernel:

```bash
dmesg | grep -i firmware
dmesg | grep -i ssv
dmesg | grep -i wifi
```

## Créditos

Este repositório é um fork/adaptação do projeto original:

```text
https://github.com/paolosabatino/ssv6x5x
```

## Licença

Consulte os arquivos de licença presentes neste repositório e no projeto original.