import re

f = open('input.txt', 'r')
lines = [line.strip('\n') for line in f]


# Part 1
valid_pass = True
validate_parameters = ['pid:', 'byr:', 'iyr:', 'eyr:', 'hgt:', 'hcl:', 'ecl:']
valid_passwords = 0
new_pass = ''

for line in lines:
    if line != '':
        new_pass += ' ' + line
    else:
        if all(parameter in new_pass for parameter in validate_parameters):
            valid_passwords += 1
        new_pass = ''
        valid_pass = True

print(valid_passwords)

# Part 2

valid_pass = True
rules = {'byr': [1920, 2002], 'iyr': [2010, 2020], 'eyr': [2020, 2030], 'hgt': {'cm': [150, 193], 'in': [59, 76]},
         'hcl': re.compile('^#[0-9a-f]{6}$'), 'ecl': ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'], 'pid': re.compile('^[0-9]{9}$')}
valid_passwords = 0
new_pass = ''

for line in lines:
    if line != '':
        new_pass += ' ' + line
    else:
        fields = {field.split(':')[0]: field.split(':')[1] for field in new_pass.split(' ') if (field != '' and 'cid' not in field)}
        # Need to also track to make sure all parameters are only entered one time
        if all(len([[m.start(), m.end()] for m in re.finditer(parameter, new_pass)]) == 1 for parameter in validate_parameters):
            for field in fields:
                if field == 'hcl':
                    if not re.search(rules['hcl'], fields['hcl']):
                        valid_pass = False
                elif field == 'pid':
                    if not re.search(rules['pid'], fields['pid']):
                        valid_pass = False
                elif field == 'hgt':
                    if 'cm' in fields['hgt']:
                        if int(fields['hgt'].split('cm')[0]) not in range(rules['hgt']['cm'][0], rules['hgt']['cm'][1]+1):
                            valid_pass = False
                    elif 'in' in fields['hgt']:
                        if int(fields['hgt'].split('in')[0]) not in range(rules['hgt']['in'][0], rules['hgt']['in'][1]+1):
                            valid_pass = False
                    else:
                        valid_pass = False
                elif field == 'ecl':
                    if not any(fields['ecl'] == eye_color for eye_color in rules['ecl']):
                        valid_pass = False
                elif int(fields[field]) not in range(rules[field][0], rules[field][1]+1):
                    valid_pass = False
        else:
            valid_pass = False
        if valid_pass:
            valid_passwords += 1
        new_pass = ''
        valid_pass = True

print(valid_passwords)
