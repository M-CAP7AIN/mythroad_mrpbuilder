t = []
t.append("Hello")

for s in t:
  uni = s.decode("cp936")
  u = ''
  for c in uni:
    c = ord(c)
    u = u + '\\' + hex(c / 256)[1:] + '\\' + hex(c % 256)[1:]
  print(s)
  print(u)