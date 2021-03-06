#!/usr/bin/env python
import sys
import hmac


class fpcode:
    '''Flower Password generate

    Attributes:
        `code`: Calculate the password
    '''

    # character table
    __table_char = "aAbBcCdDeEfFgGhHiIjJkKlLmM0123456789nNopPqQrRsStTuUvVwWxXyYzZ"
    __table_len = len(__table_char)

    # Calculated rule
    __x = None
    __rule0 = None
    __rule1 = None
    __rule2 = None
    __rule3 = None

    def __init__(self, rule0, rule1, rule2, rule3) -> None:
        '''Initialization of rules

        Args:
            `rule0`: The first rule
            `rule1`: The second rule
            `rule2`: The third rule
            `rule3`: The fourth rule

        Returns:
            None
        '''
        self.rule0 = str(rule0).strip().encode(encoding="utf-8")
        self.rule1 = str(rule1).strip().encode(encoding="utf-8")
        self.rule2 = str(rule2).strip().encode(encoding="utf-8")
        self.rule3 = str(rule3).strip().encode(encoding="utf-8")

    def __code__(self, password, key) -> None:
        '''Calculation of rules

        Args:
            `password`: A password to remember
            `key`: The corresponding keyword

        Returns:
            `None`
        '''

        # Remove the blank space
        password = str(password).strip()
        key = str(key).strip()

        # Check the value
        if (1 > len(password)) or (1 > len(key)):
            raise ValueError

        # Gets the initial value of the rule
        password = password.encode(encoding="utf-8")
        key = key.encode(encoding="utf-8")
        hmd5 = hmac.new(key, password, 'MD5').hexdigest()
        hmd5 = hmd5.encode(encoding="utf-8")

        # Calculate by rule
        self.__rule0 = list(hmac.new(self.rule0, hmd5, 'MD5').hexdigest())
        self.__rule1 = list(hmac.new(self.rule1, hmd5, 'MD5').hexdigest())
        self.__rule2 = list(hmac.new(self.rule2, hmd5, 'MD5').hexdigest())
        self.__rule3 = list(hmac.new(self.rule3, hmd5, 'MD5').hexdigest())
        self.__x = []
        for i in range(len(self.__rule0)):
            i0 = int(self.__rule0[i], 16)
            i1 = int(self.__rule1[i], 16)
            i2 = int(self.__rule2[i], 16)
            i3 = int(self.__rule3[i], 16)
            i = i0 + i1 + i2 + i3
            self.__x.append(i)

    def debug(self) -> None:
        '''Output debugging information

        Args:
            `None`

        Returns:
            `None`
        '''
        print(''.join(self.__rule0))
        print(''.join(self.__rule1))
        print(''.join(self.__rule2))
        print(''.join(self.__rule3))

    def code(self, password, key, length=16, table="", digit=False):
        '''Calculate the password

        Args:
            `password`: A password to remember
            `key`: The corresponding keyword
            `length`: The length of the computed password ( 1 ~ 32 )
            `table`: New character table
            `digit`: `True` Output pure number

        Returns:
            character string
        '''

        # Check the length
        length = int(length)
        if (1 > length) or (length > 32):
            return None

        # Calculated rule
        self.__code__(password, key)

        ret = []  # String returned
        count = 0  # round
        mark = None  # The number of times a number appears
        if digit:
            mark = [0] * 10
        else:
            mark = [0] * self.__table_len
        for i in range(length):
            i = self.__x[i]
            if digit:
                j = i = i % 10
                # Do not repeat each round
                while mark[i] > count:
                    i += 1
                    if i >= 10:
                        i = 0
                    if i == j:
                        count += 1
                mark[i] += 1
                i = str(i)
            else:
                while mark[i]:
                    i += 1
                    if i == self.__table_len:
                        i = 0
                mark[i] = 1
                i = self.__table_char[i]
            ret.append(i)

        if not digit:
            # Add a new character
            for i in range(min(len(table), length)):
                ret[self.__x[i] % length] = table[i]

        ret = ''.join(ret)

        return ret


if __name__ == "__main__":
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

    fp = fpcode("0", "1", "2", "3")
    print(fp.code(password, key, length))
    print(fp.code(password, key, length, digit=True))
    print(fp.code(password, key, length, table))
    fp.debug()
