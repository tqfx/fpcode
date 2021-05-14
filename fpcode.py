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

    def __init__(self, rule0, rule1, rule2, rule3, debug=False) -> None:
        self.rule0 = str(rule0).encode(encoding="utf-8")
        self.rule1 = str(rule1).encode(encoding="utf-8")
        self.rule2 = str(rule2).encode(encoding="utf-8")
        self.rule3 = str(rule3).encode(encoding="utf-8")
        self.debug = debug

    def __code(self, password, key):
        '''
        Args:
            password: the password
            key: the key
        '''

        password = str(password)
        key = str(key)

        if (1 > len(password.strip())) or (1 > len(key.strip())):
            raise ValueError
            return

        password = password.encode(encoding="utf-8")
        key = key.encode(encoding="utf-8")

        hmd5 = hmac.new(key, password, 'MD5').hexdigest()
        hmd5 = hmd5.encode(encoding="utf-8")

        self.__rule0 = hmac.new(self.rule0, hmd5, 'MD5').hexdigest()
        self.__rule1 = hmac.new(self.rule1, hmd5, 'MD5').hexdigest()
        self.__rule2 = hmac.new(self.rule2, hmd5, 'MD5').hexdigest()
        self.__rule3 = hmac.new(self.rule3, hmd5, 'MD5').hexdigest()

        if self.debug:
            print(hmd5.decode(encoding="utf-8"))
            print(self.__rule0)
            print(self.__rule1)
            print(self.__rule2)
            print(self.__rule3)

        return

    def code(self, password, key, length=16):
        '''
        Args:
            password: The password
            key: The key
            length: 1 ~ 32
        Returns:
            str
        '''

        if (1 > length) or (length > 32):
            return None

        self.__code(password, key)

        ret = ''
        for i in range(length):
            i0 = int(self.__rule0[i], 16)
            i1 = int(self.__rule1[i], 16)
            i2 = int(self.__rule2[i], 16)
            i3 = int(self.__rule3[i], 16)
            ret += self.__table_char[i0 + i1 + i2 + i3]

        return ret

    def code1(self, password, key, length=16):
        '''
        Args:
            password: The password
            key: The key
            length: 1 ~ 32
        Returns:
            str
        '''

        if (1 > length) or (length > 32):
            return None

        self.__code(password, key)

        ret = ''
        count = 0
        mark = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        for i in range(length):
            i0 = int(self.__rule0[i], 16)
            i1 = int(self.__rule1[i], 16)
            i2 = int(self.__rule2[i], 16)
            i3 = int(self.__rule3[i], 16)
            i = (i0 + i1 + i2 + i3) % 10
            j = i
            while mark[i] > count:
                i += 1
                if i >= 10:
                    i = 0
                if i == j:
                    count += 1
            mark[i] += 1
            ret += str(i)

        return ret

    def code2(self, password, key, table, length=16):
        '''
        Args:
            password: The password
            key: The key
            table: The table
            length: 1 ~ 32
        Returns:
            str
        '''
        symbol = ''.join(set(table))

        ret = self.code(password, key, length)
        if ret == None:
            return None

        l = len(table)
        l = min(l, length)
        for i in range(l):
            i0 = int(self.__rule0[i], 16)
            i1 = int(self.__rule1[i], 16)
            i2 = int(self.__rule2[i], 16)
            i3 = int(self.__rule3[i], 16)
            j = (i0 + i1 + i2 + i3) % length
            ret = list(ret)
            ret[j] = table[i]
            ret = ''.join(ret)

        return ret


fp = fpcode("0000", "1111", "2222", "3333")
table = "_"
if len(sys.argv) == 4:
    print(fp.code(sys.argv[1], sys.argv[2], int(sys.argv[3])))
    print(fp.code1(sys.argv[1], sys.argv[2], int(sys.argv[3])))
    print(fp.code2(sys.argv[1], sys.argv[2], table, int(sys.argv[3])))
elif len(sys.argv) == 3:
    print(fp.code(sys.argv[1], sys.argv[2]))
    print(fp.code1(sys.argv[1], sys.argv[2]))
    print(fp.code2(sys.argv[1], sys.argv[2], table))
else:
    password = input("passwd:")
    key = input("key:")
    length = int(input("length:"))
    print(fp.code(password, key, length))
    print(fp.code1(password, key, length))
    print(fp.code2(password, key, table, length))
