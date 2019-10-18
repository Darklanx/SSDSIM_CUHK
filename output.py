import sys
file = str(sys.argv[1])
n = int(sys.argv[2])
new_file = '{}_{}'.format(file, n)
with open(file, 'r') as file:
    with open(new_file, 'w+') as write_file:
        for x in range(n):
            line = next(file)
            #if x == n - 1:
            #    line = line.strip('\n')
            write_file.write(str(x) + " " + line)
