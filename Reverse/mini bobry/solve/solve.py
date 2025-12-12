# Часть 1. Декодируем содержимое между { и _

part1 = "C001M1n1B0br1k1W0oow".encode() # Делаем символы байтами с помощью encode()
constnant = b'\x14\x00G\x009\x00\x1dvsV\x164\x01\x19sgR\x1d^\x1c' # Это уже байты

res1 = "" # Строка для результата
for i in range(len(part1)):
    res1 += chr(part1[i] ^ constnant[i]) # Ксорим и конвертируем число в символ
    
# Часть 2. Декодируем содержимое между _ и }

part2 = "uuur1B0b1M1nrrssD0N0tHuu"
parts = [part2[i:i+4] for i in range(0, 24, 4)] # Разбиваем на части по 4 символа
indexes = [2, 4, 3, 5, 0, 1]
res2 = ["" for _ in range(6)] # Пустые 6 блоков - заготовка
for i in range(6):
    res2[indexes[i]] = parts[i]
    
res2 = "".join(res2)
    
# Часть 3. Формируем флаг
print("NMARK{" + res1 + "_" + res2 + "}")