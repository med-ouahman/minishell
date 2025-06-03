import shlex

command = input("$ ")
while command != 'exit':

    tokens = list(shlex.split(command))
    for i in range(0, len(tokens)):
        print(tokens[i])
    command = input("$ ")

