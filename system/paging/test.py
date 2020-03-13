import numpy as np

def get_phys(args, offset, CR3):
    cur = CR3
    for arg in args:
        key = cur + arg*8
        print(arg, np.binary_repr(arg))
        print(arg*8, np.binary_repr(arg*8))
        exit()
        try:
            value = memmap[key]
            if np.binary_repr(value)[-1] == 0:
                return 'fault'
            else:
                cur = np.binary_repr(value)
                cur = list(cur)
                for i in range(1, 13):
                    cur[-i] = '0'
                cur = ''.join(cur)
                cur = int(cur, 2)
        except Exception as e:
            return 'fault'
    cur += offset
    return cur

if __name__ == '__main__':
    handle_line = lambda line: [int(val) for val in line.replace('\n', '').split(" ")]
    f = open('dataset_44327_15.txt', 'r')
    m, q, r = handle_line(f.readline())
    CR3 = r
    memmap = {}
    for i in range(m):
        paddr, value = handle_line(f.readline())
        memmap[paddr] = value
    result = []
    cnt = 0
    for i in range(q):
        logAddress = np.binary_repr(handle_line(f.readline())[0], 64)
        PML4 = int(logAddress[-48:-39], 2)
        DP =   int(logAddress[-39:-30], 2)
        D  =   int(logAddress[-30:-21], 2)
        T  =   int(logAddress[-21:-12], 2)
        Offset11 =  int(logAddress[-12:], 2)
        physical = get_phys([PML4, DP, D, T], Offset11, CR3)
        result.append(physical)
    f.close()
    f = open('result.txt', 'w')
    for res in result:
        f.write(str(res)+'\n')
    f.close()
