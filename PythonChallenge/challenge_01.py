"""
    http://www.pythonchallenge.com/pc/def/map.html
"""


def shift_string(str_in: str, shift: int):
    """
        :param str_in:  input string
        :param shift:   how many places to shift
        :return:        output string
    """
    str_out = ""
    for char in str_in:
        if char.isalpha():
            char = chr(ord(char) + shift)
            if ord(char) > ord('z'):
                char = chr(ord(char) - (ord('z') - ord('a')) - 1)
        str_out += char
    return str_out


txt = "g fmnc wms bgblr rpylqjyrc gr zw fylb. \
            rfyrq ufyr amknsrcpq ypc dmp. \
            bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. \
            sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."

new_txt = shift_string(txt, 2)
solution = shift_string("map", 2)

print(new_txt)
print(solution)



