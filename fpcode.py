#!/usr/bin/env python
import sys
import hmac

def generateFPCode(password, key, length=16):
    if (1 > len(password.strip())) or (1 > len(key.strip())) or (1 > length) or (length > 32):
        return

    rulekey = "qwertyuiop"
    sourcekey = "asdfghjkl"
    chartable = "aAbBcCd0DeEf1FgGh2HiIj3JkKl4LmMn5NopP6qQrR7sStT8uUvV9wWxXyYzZ"

    password = password.encode(encoding="utf-8")
    key = key.encode(encoding="utf-8")
    hmd5 = hmac.new(key, password, 'MD5').hexdigest().encode(encoding="utf-8")
    rule = hmac.new(rulekey.encode(encoding="utf-8"), hmd5, 'MD5').hexdigest()
    source = hmac.new(sourcekey.encode(encoding="utf-8"), hmd5, 'MD5').hexdigest()

    code = ''
    for i in range(0, min(length, 64)):
        code += chartable[3 * int(rule[i], 16) + int(source[i], 16)]

    return code

if len(sys.argv) == 4:
    print(generateFPCode(sys.argv[1], sys.argv[2], int(sys.argv[3])))
elif len(sys.argv) == 3:
    print(generateFPCode(sys.argv[1], sys.argv[2]))
else:
    password = input("passwd:")
    key = input("key:")
    length = int(input("length:"))
    print(generateFPCode(password, key, length))
