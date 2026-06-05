# Release 5.15.93 — ssv6x5x for Armbian sunxi

This release provides the `ssv6x5x` Wi‑Fi driver compiled for the **Armbian sunxi 5.15.93-sunxi** kernel, along with a package containing the matching kernel headers used during the build process.

## Main changes

- Compiled the `ssv6x5x` Wi‑Fi module for the **Armbian sunxi 5.15.93-sunxi** kernel.
- Added a precompiled driver package to simplify installation without requiring users to rebuild the module on the device.
- Added `.sha256` files so users can verify the integrity of the published packages.
- Added a separate package with the `5.15.93-sunxi` kernel headers, required for rebuilding the driver and for environments where the original headers are no longer available.
- Updated the installation documentation to point directly to the files from this release.

## Kernel headers

While preparing this version, the headers matching the **5.15.93-sunxi** kernel were no longer available from the usual Armbian sources/repositories.

Because the driver module must be built against the exact headers for the running kernel, it was necessary to rebuild/compile and package the headers used for this release.

For that reason, this release includes the following file:

```text
armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
```

This package was included so other users can prepare a compatible build environment even when the matching headers can no longer be installed through the package manager.

## Release assets

The following files are available in this release:

```text
ssv6x5x-armbian-5.15.93-sunxi.tar.gz
ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

## Compatibility

This release is intended for systems running:

```text
5.15.93-sunxi
```

Check your running kernel before installing:

```bash
uname -r
```

If your kernel version is different, the module may fail to load with an error such as `invalid module format`.

## Download

Release page:

```text
https://github.com/jhonathanc/ssv6x5x/releases/tag/5.15.93
```

Direct driver download:

```bash
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

Optional kernel headers download:

```bash
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz
wget https://github.com/jhonathanc/ssv6x5x/releases/download/5.15.93/armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

## Verify package integrity

```bash
sha256sum -c ssv6x5x-armbian-5.15.93-sunxi.tar.gz.sha256
```

For the headers package:

```bash
sha256sum -c armbian-sunxi-5.15.93-sunxi-headers-installer.tar.gz.sha256
```

The expected result is `OK`.

## Notes

Use this release only with the matching `5.15.93-sunxi` kernel. For other kernel versions, the driver should be rebuilt using the corresponding kernel headers.
