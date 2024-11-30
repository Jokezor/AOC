use std::collections::HashMap;
use std::fs;

fn get_keypad_part1() -> (HashMap<(i32, i32), char>, (i32, i32)) {
    let mut keypad = HashMap::new();
    keypad.insert((0, 0), '1');
    keypad.insert((0, 1), '2');
    keypad.insert((0, 2), '3');
    keypad.insert((1, 0), '4');
    keypad.insert((1, 1), '5');
    keypad.insert((1, 2), '6');
    keypad.insert((2, 0), '7');
    keypad.insert((2, 1), '8');
    keypad.insert((2, 2), '9');
    let start_pos = (1, 1);
    (keypad, start_pos)
}

fn get_keypad_part2() -> (HashMap<(i32, i32), char>, (i32, i32)) {
    let mut keypad = HashMap::new();
    keypad.insert((0, 2), '1');
    keypad.insert((1, 1), '2');
    keypad.insert((1, 2), '3');
    keypad.insert((1, 3), '4');
    keypad.insert((2, 0), '5');
    keypad.insert((2, 1), '6');
    keypad.insert((2, 2), '7');
    keypad.insert((2, 3), '8');
    keypad.insert((2, 4), '9');
    keypad.insert((3, 1), 'A');
    keypad.insert((3, 2), 'B');
    keypad.insert((3, 3), 'C');
    keypad.insert((4, 2), 'D');
    let start_pos = (2, 0);
    (keypad, start_pos)
}

fn get_code(
    contents: &str,
    keypad: &HashMap<(i32, i32), char>,
    start_pos: (i32, i32),
) -> String {
    let mut code = String::new();
    let mut pos = start_pos;

    for line in contents.lines() {
        for c in line.chars() {
            let (dx, dy) = match c {
                'U' => (-1, 0),
                'D' => (1, 0),
                'L' => (0, -1),
                'R' => (0, 1),
                _ => continue, // Skip invalid directions
            };
            let new_pos = (pos.0 + dx, pos.1 + dy);
            if keypad.contains_key(&new_pos) {
                pos = new_pos;
            }
        }
        code.push(*keypad.get(&pos).unwrap());
    }

    code
}

fn main() {
    let contents = fs::read_to_string("src/input.txt").expect("Should have read file.");

    let (keypad1, start_pos1) = get_keypad_part1();
    let ans_1 = get_code(&contents, &keypad1, start_pos1);

    let (keypad2, start_pos2) = get_keypad_part2();
    let ans_2 = get_code(&contents, &keypad2, start_pos2);

    assert_eq!(ans_1, "36629");
    assert_eq!(ans_2, "99C3D");

    println!("part 1: {}", ans_1);
    println!("part 2: {}", ans_2);
}
