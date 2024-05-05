import random

def generate_random_string(min_length, max_length, characters='abc'):
    length = random.randint(min_length, max_length)
    return ''.join(random.choice(characters) for _ in range(length))

# 配置参数
min_length = 5   # 字符串的最小长度
max_length = 10  # 字符串的最大长度

# 生成字符串
source_submission = generate_random_string(min_length, max_length)
copier_submission = generate_random_string(min_length, max_length)

# 打印生成的字符串
print(source_submission)
print(copier_submission)