# SSV6X5X on Armbian sunxi 5.15.93

This fork is configured for an Allwinner H3 board that boots the Orange Pi PC Plus Armbian kernel `5.15.93-sunxi` and uses an SV6256P/SSV6x5x SDIO Wi-Fi chip.

## Files to install on the board

The GitHub Actions artifact contains:

- `lib/modules/5.15.93-sunxi/extra/ssv6x5x.ko`
- `lib/firmware/ssv6x5x-sw.bin`
- `lib/firmware/ssv6x5x-wifi.cfg`

The workflows also upload a separate `armbian-sunxi-5.15.93-sunxi-headers-installer` artifact. It contains the generated or downloaded `linux-headers` `.deb` and an installer script. In the from-source workflow, this artifact is uploaded immediately after the headers are generated and validated, before the driver module build starts.

```sh
tar -xzf armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
cd armbian-sunxi-5.15.93-sunxi-headers-installer
./install-headers.sh
```

Install them from the artifact root:

```sh
sudo cp -a lib/modules/5.15.93-sunxi/extra/ssv6x5x.ko /lib/modules/5.15.93-sunxi/extra/
sudo cp -a lib/firmware/ssv6x5x-sw.bin lib/firmware/ssv6x5x-wifi.cfg /lib/firmware/
sudo depmod -a 5.15.93-sunxi
sudo modprobe ssv6x5x
```

The wrapper does not call old vendor power/card-detect symbols. On mainline Armbian, SDIO power and card detection should come from the board device tree and MMC stack.

If the workflow cannot find `linux-headers-current-sunxi=23.02.2` in the live Armbian APT index, run it again with `headers_deb_url` pointing to the exact `.deb` for your `5.15.93-sunxi` image.

After the headers artifact has been published, use the `Build Armbian sunxi 5.15.93 module` workflow for faster driver-only builds. Its default `headers_installer_url` points to:

```text
https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.zip
```

That workflow extracts the `linux-headers` `.deb` from the release artifact and builds only `ssv6x5x.ko`, without rebuilding the Armbian kernel.

If you cannot find the headers `.deb` anywhere, use the `Build Armbian sunxi kernel and driver` workflow. It rebuilds the Armbian sunxi kernel/headers package from `armbian/build`, verifies that the generated headers contain `/usr/src/linux-headers-5.15.93-sunxi`, and then builds this driver against that generated tree.

The defaults are aimed at the `Armbian_23.02.2_Orangepipcplus_jammy_current_5.15.93_minimal.img` image:

```text
kernel_release: 5.15.93-sunxi
armbian_build_ref: 1a8daf0
armbian_lib_tag:
board: orangepipcplus
kernel_branch: current
release: jammy
```

The from-source workflow passes `EXTRAWIFI=no` internally so Armbian does not fetch and patch unrelated in-tree Realtek Wi-Fi drivers while generating the kernel headers.

If the generated kernel is not exactly `5.15.93-sunxi`, check `/etc/armbian-release` on the board and use its `BUILD_REPOSITORY_COMMIT` and `BOARD` values as the workflow inputs. The `release` input should match the image userspace, which is `jammy` for this image filename.

On the board, collect the exact build metadata with:

```sh
cat /etc/armbian-release
uname -r
dpkg -l | grep -E 'linux-(image|dtb|headers)-current-sunxi'
```

## Useful checks on the board

```sh
uname -r
lsmod | grep ssv6x5x
dmesg | grep -iE 'ssv|sdio|firmware'
ip link
```
