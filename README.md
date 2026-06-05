ssv6x5x

Driver Wi-Fi "ssv6x5x" adaptado para uso em sistemas Linux embarcados, com foco em placas/TV boxes que utilizam chipsets da família SSV6x5x.

Este repositório é baseado no projeto original de adaptação do driver para kernels Rockchip Linux 4.4, especialmente para SoCs RK322x, e também disponibiliza builds pré-compilados na página de releases do projeto.

Sobre

O "ssv6x5x" é um driver para chipsets Wi-Fi da família SSV6x5x, comuns em algumas TV boxes e dispositivos embarcados.

Este projeto pode ser usado de duas formas:

1. Instalando um driver pré-compilado disponível em Releases.
2. Compilando o driver manualmente no próprio dispositivo.

Compatibilidade

O suporte depende da versão do kernel, da arquitetura e do hardware utilizado.

Antes de instalar, confira a versão do kernel do seu sistema:

uname -r

Baixe somente um driver compatível com a sua versão de kernel. Um módulo compilado para outro kernel normalmente não será carregado corretamente.

Instalação usando a página de Releases

A forma mais simples de instalar é baixar o driver já compilado a partir da página de releases deste repositório:

https://github.com/jhonathanc/ssv6x5x/releases

1. Baixe os arquivos da release

Acesse a página de releases:

https://github.com/jhonathanc/ssv6x5x/releases/latest

Baixe os arquivos disponíveis na seção Assets da release correspondente ao seu kernel.

Você também pode baixar via terminal usando "wget" ou "curl". Exemplo:

mkdir -p ~/ssv6x5x-driver
cd ~/ssv6x5x-driver

# Substitua a URL abaixo pelo link do arquivo disponível em Assets
wget https://github.com/jhonathanc/ssv6x5x/releases/latest/download/NOME_DO_ARQUIVO

Ou, caso use GitHub CLI:

mkdir -p ~/ssv6x5x-driver
cd ~/ssv6x5x-driver

gh release download --repo jhonathanc/ssv6x5x --latest

2. Extraia os arquivos, se necessário

Se o arquivo baixado estiver compactado:

tar -xvf NOME_DO_ARQUIVO.tar.gz

ou:

unzip NOME_DO_ARQUIVO.zip

3. Instale o módulo do driver

Se a release incluir um arquivo ".ko", instale-o no diretório de módulos do kernel atual:

sudo mkdir -p /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x
sudo cp *.ko /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x/
sudo depmod -a

Carregue o módulo:

sudo modprobe ssv6x5x

Se o nome do módulo for diferente, verifique com:

ls *.ko

e carregue usando o nome correto, sem a extensão ".ko":

sudo modprobe NOME_DO_MODULO

4. Instale o arquivo de configuração/firmware

Caso a release inclua arquivos como "ssv6x5x-wifi.cfg", copie-os para "/lib/firmware":

sudo cp ssv6x5x-wifi.cfg /lib/firmware/

Se houver arquivos ".bin" de firmware, copie-os também:

sudo cp *.bin /lib/firmware/

5. Reinicie ou recarregue o driver

Depois da instalação, reinicie o sistema:

sudo reboot

Ou tente recarregar o módulo manualmente:

sudo modprobe -r ssv6x5x
sudo modprobe ssv6x5x

6. Verifique se o Wi-Fi foi detectado

Após reiniciar, verifique se a interface Wi-Fi apareceu:

ip link

Também é útil conferir as mensagens do kernel:

dmesg | grep -i ssv

ou:

dmesg | grep -i wifi

Compilando no próprio dispositivo

Caso não exista uma release compatível com o seu kernel, você pode tentar compilar o driver manualmente.

Dependências

Instale os pacotes necessários:

sudo apt update
sudo apt install -y build-essential git linux-headers-$(uname -r)

Em sistemas Armbian, os headers podem ter um nome específico. Verifique os pacotes disponíveis para o seu kernel caso o comando acima não funcione.

Clonar o repositório

git clone https://github.com/jhonathanc/ssv6x5x.git
cd ssv6x5x

Compilar

source ./vars
make -j$(nproc)

Instalar

sudo make install
sudo depmod -a
sudo modprobe ssv6x5x

Depois, reinicie:

sudo reboot

Integração na árvore do kernel

Outra opção é integrar o driver diretamente na árvore do kernel.

Copie este diretório para:

drivers/net/wireless/ssv6x5x

Depois, adapte os arquivos "Kconfig" e "Makefile" do kernel para incluir o driver e compile o kernel normalmente.

Solução de problemas

O módulo não carrega

Verifique a mensagem de erro:

dmesg | tail -n 100

Confira também se o módulo foi compilado para o mesmo kernel em execução:

uname -r
modinfo ssv6x5x

A interface Wi-Fi não aparece

Verifique se o driver foi carregado:

lsmod | grep ssv

Confira os logs:

dmesg | grep -i ssv

Verifique também se os arquivos de configuração e firmware estão em "/lib/firmware".

Erro de versão do kernel

Se aparecer erro como "invalid module format", o driver foi compilado para uma versão diferente do kernel.

Nesse caso, use uma release compatível com o seu kernel ou compile o driver diretamente no dispositivo.

Estrutura útil do projeto

Alguns arquivos importantes:

- "vars" / "vars.sh": variáveis usadas no processo de build.
- "Makefile": regras principais de compilação.
- "ssv6x5x-wifi.cfg": configuração do driver/firmware.
- "load.sh": script auxiliar para carregar o driver.
- "unload.sh": script auxiliar para descarregar o driver.
- "remove_old_driver.sh": script auxiliar para remover versões antigas do driver.

Créditos

Este repositório é um fork/adaptação do projeto original:

https://github.com/paolosabatino/ssv6x5x

Licença

Consulte os arquivos de licença presentes no repositório original e neste fork.