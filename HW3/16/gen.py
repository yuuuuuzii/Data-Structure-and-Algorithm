import random

def generate_random_string(min_length, max_length, characters='abc'):
    length = random.randint(min_length, max_length)
    return ''.join(random.choice(characters) for _ in range(length))


min_length = 5   
max_length = 10  


source_submission = generate_random_string(min_length, max_length)
copier_submission = generate_random_string(min_length, max_length)


print(source_submission)
print(copier_submission)