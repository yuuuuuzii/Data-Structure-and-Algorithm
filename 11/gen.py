import random

# Set the constraints for the test case
MAX_N = 1000  # Maximum value for N
MAX_M = MAX_N - 1  # Maximum value for M
MAX_Q = 1000  # Maximum value for Q
MAX_L = 1000000 # Maximum value for L
MAX_T = 1000000000000000  # Maximum value for t
MAX_P = 1000000000000000 # Maximum value for p

# Function to generate the test case
def generate_test_case():
    # Generate N, M, Q within the constraints
    N = random.randint(2, min(1000 , MAX_N))  # N capped at 100 for simplicity
    M = random.randint(0, min(N - 1, MAX_M))
    Q = random.randint(1, min(1000, MAX_Q))  # Q capped at 100 for simplicity

    # Initialize the list of connections and used 'v' values
    connections = []
    used_v = set()

    # Ensure that 0 is only a source, not a destination
    used_v.add(0)

    # Generate M unique pathways
    for _ in range(M):
        u = random.randint(0, N - 2)  # u can be from 0 to N-2
        v = random.choice([x for x in range(1, N) if x not in used_v])
        l = random.randint(1, MAX_L)
        connections.append((u, v, l))
        used_v.add(v)

    # Generate Q instructions with their respective ti or pi values
    instructions = []
    for _ in range(Q):
        instruction_type = random.choice([1, 2, 4])  # Instruction types 1 through 5
        if instruction_type == 3:  # ti is required for instruction 3
            ti = random.randint(0, MAX_T)
            instructions.append((3, ti))
        elif instruction_type == 5:  # pi is required for instruction 5
            pi = random.randint(0, MAX_P)
            instructions.append((5, pi))
        else:  # Only the instruction type is needed for types 1, 2, and 4
            instructions.append((instruction_type,))

    return N, M, Q, connections, instructions

# Generate a test case
N, M, Q, connections, instructions = generate_test_case()

# Display the test case
print(f"{N} {M} {Q}")
for u, v, l in connections:
    print(f"{u} {v} {l}")
for instruction in instructions:
    print(*instruction)  # Unpack the instruction tuple
