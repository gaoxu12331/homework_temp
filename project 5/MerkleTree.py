import hashlib

# hash函数，采用sh256进行计算

def Hash(str):
    return hashlib.sha256(str.encode('utf-8')).hexdigest()

# 标记最底层节点的数目
N = 16
value = []
for i in range(N):
    value.append(str(i+1))
# 保存数据为从1到N，每个节点保存一个数字
print("原本数据为：", value)

MerkleTree1 = [[]]
for i in range(N):
    MerkleTree1[0].append(Hash(value[i]))

count = 1
mark = 0
while N > 1:
    MerkleTree1.append([])
    mark = N % 2
    N = N // 2
    for i in range(N):
        tempstr = MerkleTree1[count-1][i*2]+MerkleTree1[count-1][i*2+1]
        MerkleTree1[count].append(Hash(tempstr))
    if mark == 1:
        MerkleTree1[count].append(MerkleTree1[count-1][2*N])
    count += 1

print("MerkleTree的结果为:",MerkleTree1)


# 以相同的方式生成一个类似的MerkleTree，用作后文比较
N = 16
MerkleTree2 = [[]]
value[3] = '5'
for i in range(N):
    MerkleTree2[0].append(Hash(value[i])) 


count = 1
mark = 0
while N > 1:
    MerkleTree2.append([])
    mark = N % 2
    N = N // 2
    for i in range(N):
        tempstr = MerkleTree2[count-1][i*2]+MerkleTree2[count-1][i*2+1]
        MerkleTree2[count].append(Hash(tempstr))
    if mark == 1:
        MerkleTree2[count].append(MerkleTree2[count-1][2*N])
    count += 1

print("MerkleTree的结果为:",MerkleTree2)


# MerkleTree的校验,即判断两MerkleTree的哪一个节点出现了错误
def judge(MerkleTree1, MerkleTree2):
    length = len(MerkleTree1)
    if(MerkleTree1[length-1] == MerkleTree2[length-1]):
        print("Same Tree")
    else:
        trace = -1
        if MerkleTree1[length-2][0] != MerkleTree2[length-2][0]:
            trace = 0
        elif MerkleTree1[length-2][1] != MerkleTree2[length-2][1]:
            trace = 1
        count = length-3
        while 1:
            if MerkleTree1[count][2*trace] != MerkleTree2[count][2*trace]:
                trace = 2*trace
            elif MerkleTree1[count][2*trace+1] != MerkleTree2[count][2*trace+1]:
                trace = 2*trace+1
            if count == 0:
                print("鉴定为:",trace,"位置异常")
                break
            count-=1

# 进行MerkleTree比较
judge(MerkleTree1,MerkleTree2)


    
        
     
    

