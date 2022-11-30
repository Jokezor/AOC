import functools


def read_file(file_name: str) -> list:
    return [line.strip('\n') for line in open(file_name, 'r')]


def calc_num_questions(question_answers: list, part: str) -> list:
    group_answer = ''
    group_answers = []

    for ind, line in enumerate(question_answers):
        if line != '' and ind < len(question_answers) - 1:
            group_answer += ' ' + line
        else:
            if ind == len(question_answers) - 1:
                group_answer += ' ' + line
            unique_chars = []
            for char in group_answer.replace(' ', ''):
                if part == 'part1':
                    if char not in unique_chars:
                        unique_chars.append(char)
                elif part == 'part2':
                    if char not in unique_chars and all([char in answer for answer in group_answer.split(' ')[1:]]):
                        unique_chars.append(char)
            group_answers.append(len(unique_chars))
            group_answer = ''
    return group_answers


def reduce_array(num_questions: list) -> int:
    return functools.reduce(lambda x, y: x + y, num_questions)


if __name__ == '__main__':
    file_name = 'input.txt'
    question_answers = read_file(file_name)
    num_questions_part_1 = calc_num_questions(question_answers, 'part1')
    num_questions_part_2 = calc_num_questions(question_answers, 'part2')
    questions_answered_part_1 = reduce_array(num_questions_part_1)
    questions_answered_part_2 = reduce_array(num_questions_part_2)
    print(questions_answered_part_1, questions_answered_part_2)


