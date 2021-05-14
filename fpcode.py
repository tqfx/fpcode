#!/usr/bin/env python
import sys
import hmac


class fpcode:
    '''Flower Password generate

    Attributes:
        code:
        code1:
        code2:
    '''

    __table_char = "aAbBcCdDeEfFgGhHiIjJkKlLmM0123456789nNopPqQrRsStTuUvVwWxXyYzZ"

    __rule0 = None
    __rule1 = None
    __rule2 = None
    __rule3 = None

    def __init__(self, rule0, rule1, rule2, rule3) -> None:
        self.rule0 = str(rule0).strip().encode(encoding="utf-8")
        self.rule1 = str(rule1).strip().encode(encoding="utf-8")
        self.rule2 = str(rule2).strip().encode(encoding="utf-8")
        self.rule3 = str(rule3).strip().encode(encoding="utf-8")

    def __code__(self, password, key):
        '''
        Args:
            password: the password
            key: the key
        '''

        password = str(password).strip()
        key = str(key).strip()

        if (1 > len(password)) or (1 > len(key)):
            raise ValueError

        password = password.encode(encoding="utf-8")
        key = key.encode(encoding="utf-8")

        hmd5 = hmac.new(key, password, 'MD5').hexdigest()
        hmd5 = hmd5.encode(encoding="utf-8")

        self.__rule0 = hmac.new(self.rule0, hmd5, 'MD5').hexdigest()
        self.__rule1 = hmac.new(self.rule1, hmd5, 'MD5').hexdigest()
        self.__rule2 = hmac.new(self.rule2, hmd5, 'MD5').hexdigest()
        self.__rule3 = hmac.new(self.rule3, hmd5, 'MD5').hexdigest()

        return

    def debug(self):
        print(self.__rule0)
        print(self.__rule1)
        print(self.__rule2)
        print(self.__rule3)

    def code(self, password, key, length=16, table="", digit=False):
        '''
        Args:
            password: The password
            key: The key
            length: 1 ~ 32
            table: The table
            digit: The flag is digit
        Returns:
            str
        '''

        length = int(length)
        if (1 > length) or (length > 32):
            return None

        self.__code__(password, key)

        ret = ''
        count = 0
        mark = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        for i in range(length):
            i0 = int(self.__rule0[i], 16)
            i1 = int(self.__rule1[i], 16)
            i2 = int(self.__rule2[i], 16)
            i3 = int(self.__rule3[i], 16)
            if digit:
                j = i = (i0 + i1 + i2 + i3) % 10
                while mark[i] > count:
                    i += 1
                    if i >= 10:
                        i = 0
                    if i == j:
                        count += 1
                mark[i] += 1
                ret += str(i)
            else:
                i = i0 + i1 + i2 + i3
                ret += self.__table_char[i]

        if not digit:
            for i in range(min(len(table), length)):
                i0 = int(self.__rule0[i], 16)
                i1 = int(self.__rule1[i], 16)
                i2 = int(self.__rule2[i], 16)
                i3 = int(self.__rule3[i], 16)
                j = (i0 + i1 + i2 + i3) % length

                ret = list(ret)
                ret[j] = table[i]
                ret = ''.join(ret)

        return ret


fp = fpcode("", "", "", "")
table = "_"
password = ""
key = ""
length = 16
argc = len(sys.argv)
if argc > 3:
    length = int(sys.argv[3])
if argc > 2:
    password = sys.argv[1]
    key = sys.argv[2]
if argc == 2:
    length = int(sys.argv[1])
elif argc == 1:
    length = int(input("length:"))
if argc < 3:
    password = input("passwd:")
    key = input("key:")

print(fp.code(password, key, length))
print(fp.code(password, key, length, digit=True))
print(fp.code(password, key, length, table))
fp.debug()
