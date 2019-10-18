# 用來驗證 response time有沒有錯
# 第一個 input write response file
# 第二個 input read response file
import sys
write_count = 0
write_time = 0
read_time = 0
read_count = 0
with open(sys.argv[1], 'r') as f:
    for line in f:
        t = line.split(',')[2]
        write_time += int(t)
        write_count += 1

with open(sys.argv[2], 'r') as f:
    for line in f:
        t = line.split(',')[2]
        read_time += int(t)
        read_count += 1

if read_count != 0:
    print("read average {}".format(read_time / read_count))
if write_count != 0:
    print("write average {}".format(write_time / write_count))
