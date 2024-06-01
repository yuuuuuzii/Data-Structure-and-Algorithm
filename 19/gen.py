import random

def generate_test_data(max_n=10, max_t=10, max_value=10):
    n = random.randint(1, max_n)  # 生成1到max_n之间的随机整数作为序列长度
    t = random.randint(1, max_t)  # 生成1到max_t之间的随机整数作为操作数

    # 生成原始序列
    sequence = [random.randint(1, max_value) for _ in range(n)]
    
    print(n, t)
    print(" ".join(map(str, sequence)))  # 输出序列，元素之间用空格分隔

    current_n = n  # 当前序列长度初始化为n

    for _ in range(t):
        if current_n == 0:  # 如果当前序列为空，只允许插入操作
            op_type = 2
        else:
            op_type = random.randint(1, 3)  # 随机选择操作类型（1，2，3）

        if op_type == 1:  # 删除操作，要确保有元素可以删除
            k = random.randint(1, current_n)
            print(f"1 {k}")
            current_n -= 1  # 删除元素后，序列长度减少
        elif op_type == 2:  # 插入操作
            k = random.randint(1, current_n + 1)
            a = random.randint(1, max_value)
            print(f"2 {k} {a}")
            current_n += 1  # 插入新元素后，序列长度增加
        elif op_type == 3 and current_n > 1:  # 求和操作，确保至少有两个元素
            l = random.randint(1, current_n - 1)
            r = random.randint(l + 1, current_n)  # 确保 l < r
            print(f"3 {l} {r}")

# 调用函数生成测试数据
generate_test_data()