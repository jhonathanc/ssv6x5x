# ssv6x5x

Wi-Fi driver `ssv6x5x` compiled for **Armbian sunxi kernel 5.15.93**.

<img width="1438" height="831" alt="image" src="https://github.com/user-attachments/assets/494f07c6-9f4a-4687-aa8c-9137f2ba990b" />

This repository contains an adaptation of the `ssv6x5x` driver for Wi-Fi chipsets from the SSV6x5x family, commonly found in some TV boxes and embedded devices.

Release `5.15.93` includes:

- Compiled Wi-Fi driver: `ssv6x5x-armbian-5.15.93-sunxi.tar.gz`
- Kernel headers installer: `armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz`
- `.sha256` files for integrity verification

## Compatibility

This release was prepared for:

```text
Kernel: 5.15.93-sunxi
Target distribution: Armbian / sunxi
```

Before installing, check the running kernel version:

```bash
uname -r
```

The expected result should be:

```text
5.15.93-sunxi
```

If your kernel is different, the module may fail to load with an error such as `invalid module format`.

## Download release 5.15.93

The fixed release is available at:

```text
https://github.com/jhonathanc/ssv6x5x/releases/tag/5.15.93
```

To download directly from the terminal:

```bash
mkdir -p ~/ssv6x5x-driver
cd ~/ssv6x5x-driver

wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

Optionally, also download the headers installer:

```bash
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

## Verify file integrity

After downloading, validate the checksums:

```bash
sha256sum -c ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

If you also downloaded the headers:

```bash
sha256sum -c armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

The expected output should indicate `OK`.

## Installing the precompiled driver

Extract the driver package:

```bash
tar -xzf ssv6x5x-armbian-5.15.93-sunxi.tar.gz
```

Enter the extracted directory, if one was created:

```bash
ls
```

Locate the module file:

```bash
find . -name "*.ko"
```

Install the module into the current kernel directory:

```bash
sudo mkdir -p /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x
sudo cp $(find . -name "*.ko" | head -n 1) /lib/modules/$(uname -r)/kernel/drivers/net/wireless/ssv6x5x/
sudo depmod -a
```

Load the driver:

```bash
sudo modprobe ssv6x5x
```

If the module name is different, check the `.ko` file name:

```bash
find . -name "*.ko"
```

Then load it using the correct name, without the `.ko` extension:

```bash
sudo modprobe MODULE_NAME
```

## Installing firmware/configuration files

If the extracted package includes firmware or configuration files, copy them to `/lib/firmware`:

```bash
sudo cp $(find . -name "*.bin") /lib/firmware/ 2>/dev/null || true
sudo cp $(find . -name "*.cfg") /lib/firmware/ 2>/dev/null || true
```

If the file `ssv6x5x-wifi.cfg` exists, copy it explicitly:

```bash
sudo cp ssv6x5x-wifi.cfg /lib/firmware/ 2>/dev/null || true
```

## Reboot the system

After installing the driver, reboot:

```bash
sudo reboot
```

After the reboot, check whether the Wi-Fi interface appeared:

```bash
ip link
```

It is also useful to check the kernel logs:

```bash
dmesg | grep -i ssv
```

or:

```bash
dmesg | grep -i wifi
```

## Installing kernel headers

Headers are required if you want to compile the driver manually or prepare the build environment.

Download and extract the package:

```bash
mkdir -p ~/ssv6x5x-headers
cd ~/ssv6x5x-headers

wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
tar -xzf armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
```

Check the extracted contents:

```bash
ls -la
```

If there is an installation script, grant permission and run it:

```bash
chmod +x *.sh
sudo ./*.sh
```

If there are `.deb` packages, install them with:

```bash
sudo dpkg -i *.deb
sudo apt -f install
```

Then confirm that the kernel build directory exists:

```bash
ls -la /lib/modules/$(uname -r)/build
```

## Manual compilation

If you want to compile the driver from source code, install the dependencies:

```bash
sudo apt update
sudo apt install -y build-essential git
```

Clone the repository:

```bash
git clone https://github.com/jhonathanc/ssv6x5x.git
cd ssv6x5x
```

Load the build variables, if necessary:

```bash
source ./vars
```

Compile:

```bash
make -j$(nproc)
```

Install:

```bash
sudo make install
sudo depmod -a
sudo modprobe ssv6x5x
```

Reboot:

```bash
sudo reboot
```

## Helper scripts

The repository may also include helper scripts:

- `load.sh`: loads the driver
- `unload.sh`: unloads the driver
- `remove_old_driver.sh`: removes old versions of the driver
- `vars` / `vars.sh`: configures environment variables for building

Example:

```bash
chmod +x load.sh unload.sh remove_old_driver.sh
sudo ./load.sh
```

## Troubleshooting

### Check whether the module was loaded

```bash
lsmod | grep ssv
```

### Check driver logs

```bash
dmesg | grep -i ssv
```

### `invalid module format` error

This error usually indicates that the driver was compiled for a different kernel version than the one currently running.

Check:

```bash
uname -r
modinfo ssv6x5x
```

Release `5.15.93` is intended for the kernel:

```text
5.15.93-sunxi
```

### Wi-Fi interface does not appear

Check whether the module was loaded:

```bash
lsmod | grep ssv
```

Check whether the firmware/configuration files were copied:

```bash
ls -la /lib/firmware | grep -i ssv
```

Check the kernel messages:

```bash
dmesg | grep -i firmware
dmesg | grep -i ssv
dmesg | grep -i wifi
```

## Credits

This repository is a fork/adaptation of the original project:

```text
https://github.com/paolosabatino/ssv6x5x
```

## License

See the license files included in this repository and in the original project.
