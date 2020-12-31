def bitstring_to_bytes(s):
    return int(s, 2).to_bytes(len(s) // 8, byteorder='big')

def byte_xor(ba1, ba2):
    return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])


dna1 = "CTGTCGCGAGCGGATACATTCAAACAATCCTGGGTACAAAGAATAAAACCTGGGCAATAATTCACCCAAACAAGGAAAGTAGCGAAAAAGTTCCAGAGGCCAAA"
dna2 = "ATATATAAACCAGTTAATCAATATCTCTATATGCTTATATGTCTCGTCCGTCTACGCACCTAATATAACGTCCATGCGTCACCCCTAGACTAATTACCTCATTC"

b = []

for c in dna1:
    if c == 'A':
        k = '00'
    elif c == 'C':
        k = '01'
    elif c == 'G':
        k = '10'
    elif c == 'T':
        k = '11'

    b.append(k)

dna1Bytes = bitstring_to_bytes("".join(b))

b = []

for c in dna2:
    if c == 'A':
        k = '00'
    elif c == 'C':
        k = '01'
    elif c == 'G':
        k = '10'
    elif c == 'T':
        k = '11'

    b.append(k)

dna2Bytes = bitstring_to_bytes("".join(b))

print()
print(byte_xor(dna1Bytes, dna2Bytes))
