#!/usr/bin/env python3
# trunk-ignore-all(ruff/F821)
# trunk-ignore-all(flake8/F821): For SConstruct imports

import sys
from os.path import basename, dirname, join
from intelhex import IntelHex
Import("env")


# Custom HEX from ELF
# Convert hex to uf2 for nrf52
def nrf52_hex_to_uf2(source, target, env):
    hex_path = target[0].get_abspath()

    ih = IntelHex(hex_path)

    # 获取所有地址并排序
    addresses = sorted(ih.addresses())

    if not addresses:
        print("No data in HEX, skip UF2 generation")
        return

    segments = []
    seg_start = addresses[0]
    seg_last = addresses[0]

    for addr in addresses[1:]:
        if addr != seg_last + 1:
            # 出现不连续
            segments.append((seg_start, seg_last))
            seg_start = addr
        seg_last = addr

    segments.append((seg_start, seg_last))

    print(f"Detected {len(segments)} HEX segment(s):")
    for i, (s, e) in enumerate(segments):
        print(f"  [{i}] 0x{s:08X} - 0x{e:08X} ({e - s + 1} bytes)")

    out_dir = dirname(hex_path)
    base = basename(hex_path).replace(".hex", "")

    for idx, (start, end) in enumerate(segments):
        seg_hex = IntelHex()
        for addr in range(start, end + 1):
            seg_hex[addr] = ih[addr]

        seg_hex_path = join(out_dir, f"{base}.seg{idx}.hex")
        seg_uf2_path = join(out_dir, f"{base}.seg{idx}.uf2")

        seg_hex.write_hex_file(seg_hex_path)

        env.Execute(
            env.VerboseAction(
                f'"{sys.executable}" ./bin/uf2conv.py "{seg_hex_path}" '
                f'-c -f 0xADA52840 -o "{seg_uf2_path}"',
                f"Generating UF2 [{idx}] from 0x{start:08X}",
            )
        )


def nrf52_mergehex(source, target, env):
    hex_path = target[0].get_abspath()
    merged_hex_path = hex_path.replace(".hex", ".merged.hex")
    merge_with = None
    if "wio-sdk-wm1110" == str(env.get("PIOENV")):
        merge_with = env.subst("$PROJECT_DIR/bin/s140_nrf52_7.3.0_softdevice.hex")
    else:
        print("merge_with not defined for this target")

    if merge_with is not None:
        env.Execute(
            env.VerboseAction(
                f'"$PROJECT_DIR/bin/mergehex" -m "{hex_path}" "{merge_with}" -o "{merged_hex_path}"',
                "Merging HEX with SoftDevice",
            )
        )
        print(f'Merged file saved at "{basename(merged_hex_path)}"')
        nrf52_hex_to_uf2([hex_path, merge_with], [env.File(merged_hex_path)], env)


# if WM1110 target, merge hex with softdevice 7.3.0
if "wio-sdk-wm1110" == env.get("PIOENV"):
    env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", nrf52_mergehex)
else:
    env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", nrf52_hex_to_uf2)
