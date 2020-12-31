start = 0x124B
len_block = 0x14
char_offset = 0xD
next_char_relative_offset = 0x10
chunks = {}
doWork = True
with open("padawanlock", "rb") as file:
    file.read(start)
    while doWork:
        position = file.tell()
        chunk = file.read(len_block)
        if chunk[0] != 0xB9:
            doWork = False
        char = chr(chunk[char_offset])
        next_char_address = int.from_bytes(chunk[next_char_relative_offset:next_char_relative_offset+4], byteorder='little', signed=True) + file.tell()
        test = ""



        chunks[position] = (char, next_char_address)

final_position = 0
for position, chunk in chunks.items():
    try:
        if chunk[0] == "H":
            next_chunk = chunks[chunk[1]]
            if  next_chunk[0] == "V":
                print(position)
                final_position = position
                break
    except:
        pass


def print_next_chunk(chunk):
    try:
        print(chunk[0], end='')
        print_next_chunk(chunks[chunk[1]])
    except:
        pass

chunk = chunks[final_position]

print_next_chunk(chunk)
