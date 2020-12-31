#!/usr/bin/env python3
import subprocess
import argparse


def qrencode(inp):
    proc = subprocess.run([
        "qrencode",
        inp,
        "-o-",
        "-m", "0",
        "-t", "ANSIUTF8",
        "--strict-version", "-v", "2",
    ], capture_output=True, text=True, check=True)
    return proc.stdout


def c_header(bits=False):
    yield '#ifndef _QR_DATA_H_'
    yield '#define _QR_DATA_H_'
    if bits:
        yield "static const unsigned char lut[] = {' ', '.', '*', '#'};"
    yield 'static const unsigned char qr_code[] = {'


def c_trailer():
    yield '};'
    yield ''
    yield '#endif'


def get_bits(cs):
    mapping = {
        ' ': 0b00,
        '▄': 0b01,
        '▀': 0b10,
        '█': 0b11,
    }
    bits = [mapping[c] for c in cs]

    return bits[0] | bits[1] << 2 | bits[2] << 4 | bits[3] << 6


def line_to_str(val, *, c_syntax):
    prefix = '    ' if c_syntax else '    db '
    suffix = ',' if c_syntax else ''
    return f"{prefix}0b{val:08b}{suffix}"


def lines_to_str(lines, *, c_syntax):
    if c_syntax:
        yield from c_header(bits=True)
        for line in lines:
            yield line_to_str(line, c_syntax=True)
        yield from c_trailer()
    else:
        for line in lines:
            yield line_to_str(line, c_syntax=False)


def convert_bits(stdout):
    cs = []
    for c in reversed(stdout):
        if c not in ' ▄▀█':
            continue
        cs.append(c)
        if len(cs) == 4:
            yield get_bits(cs)
            cs = []

    if cs:
        for _ in range(4 - len(cs) % 4):
            cs.append(' ')
        yield get_bits(cs)


def convert_hidden(qrdata, hiddenflag):
    for p, k in zip('\r\n' + hiddenflag, qrdata):
        yield ord(p) ^ k


def convert_bytes(stdout, *, inverted, c_syntax):
    # https://en.wikipedia.org/wiki/Code_page_437
    # https://upload.wikimedia.org/wikipedia/de/e/ef/Dosasciitable_CP437.png
    normal_mapping = {
        ' ': '0x20',
        '▄': '0xDC',
        '▀': '0xDF',
        '█': '0xDB',
    }
    inverted_mapping = {
        ' ': '0xDB',
        '▄': '0xDF',
        '▀': '0xDC',
        '█': '0x20',
    }
    mapping = inverted_mapping if inverted else normal_mapping

    if c_syntax:
        yield from c_header()

    lines = stdout.splitlines()
    for i, line in enumerate(lines):
        data = []
        data += [mapping[c] for c in line.strip() if c in mapping]
        if i != len(lines)-1:
            data += ['0x0D', '0x0A']
        else:
            data += ['0x00']
        prefix = '    ' if c_syntax else '    db '
        suffix = ',' if c_syntax else ''
        yield prefix + ', '.join(data) + suffix

    if c_syntax:
        yield from c_trailer()


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--inverted', action='store_true')
    parser.add_argument('-c', '--c-syntax', action='store_true')
    parser.add_argument('-b', '--bits', action='store_true')
    parser.add_argument('--hidden')
    parser.add_argument('password', nargs='?')
    return parser.parse_args()


def main():
    args = parse_args()
    stdout = qrencode(args.password)
    if args.bits:
        lines = convert_bits(stdout)
        if args.hidden:
            lines = convert_hidden(lines, args.hidden)
        converted = lines_to_str(lines, c_syntax=args.c_syntax)
    else:
        if args.hidden is not None:
            assert False, "--hidden is only supported with --bits"
        converted = convert_bytes(
            stdout,
            inverted=args.inverted,
            c_syntax=args.c_syntax,
        )
    print('\n'.join(converted))


if __name__ == "__main__":
    main()
