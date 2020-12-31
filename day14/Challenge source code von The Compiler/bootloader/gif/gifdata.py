#!/usr/bin/python3

import pfp

dom = pfp.parse(data_file='file.gif', template_file='GIF.bt')
#data = dom.Data.ImageDescriptor._pfp__build()
data = dom.Data.ImageData._pfp__build()

print('    db ' + ', '.join(f'0x{b:02x}' for b in data))
