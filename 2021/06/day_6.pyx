from collections import Counter

def read_fish_age(input_file):
    with open(input_file, 'r') as f: 
        initial_state = {str(i): 0 for i in range(0, 9)}

        initial_line = f.readline().strip().split(',')

        for number in initial_line:
            initial_state[number] += 1

    return dict(initial_state)

def simulate_fish(input_file, print_state=True, simulation_length=18):
    initial_state = read_fish_age(input_file)
    if print_state: print(f'Initial state: {initial_state}')

    for day in range(simulation_length):
        # Use a second state to not start counting fish just born
        old_state = initial_state.copy()

        for timer in old_state.keys():
            if timer == '0' and old_state[timer]:
                print(old_state.values(), old_state[timer])
                # Spawn the younglings
                initial_state['8'] = old_state['8'] + old_state[timer]

                # Reset the timer to 6
                initial_state['6'] = old_state[timer]
                print(old_state == initial_state)

                # No zeroes left
                initial_state['0'] = 0
            else:
                # Move all to the next timer
                initial_state[str(int(timer)-1)] = old_state[timer] 

        if print_state: print(f'After {day+1}: {initial_state}')
    print(initial_state, sum(initial_state.values()))
    return sum(initial_state.values())


#################################################################################
# Test example
assert simulate_fish('example_input', False, 80) == 5934


#################################################################################
# Test part 1
assert simulate_fish('input', False, 80) == 385391


#################################################################################
# Test part 2
#assert len(simulate_fish('input', False, 256)) == 385391
