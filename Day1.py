values_list = []
with open("Day1_input.txt", 'r') as file:
    for index, line in enumerate(file):
        character_holder = ''
        for character in line:
            if character.isdigit():
                character_holder += character
        if len(character_holder) == 1:
            character_holder += character_holder
        elif len(character_holder) > 2:
            character_holder = character_holder[0] + character_holder[-1]
        values_list.append(int(character_holder))
        character_holder = ''
print(sum(values_list))
