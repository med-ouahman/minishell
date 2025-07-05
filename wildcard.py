def print_table(table):
    len_table = len(table)
    len_str = 0
    i = 0

    while i < len_table:
        j = 0
        len_str = len(table[i])
        while j < len_str:
            print(table[i][j])
            if i < len_table - 1:
                print(' ', end='', sep='')
            else:
                print('\n', end='', sep='')
            j +=1
        i +=1
        





def create_array(l):
    array = []
    i = 0
    while i < l:
        array.append('0')
        i += 1
    return array

def create_match_table(patt, s_match):
    l1, l2 = len(patt), len(s_match)
    table = []
    i = 0
    while i < (l1 + 1):
        table.append(create_array(l2 + 1))
        i += 1
    return table

def main():
    patt, str_to_match = '', ''
    while True:
        patt = input("Pattern: ")
        str_to_match = input("String to match: ")
        table = create_match_table(patt, str_to_match)
        print_table(table)

main()
