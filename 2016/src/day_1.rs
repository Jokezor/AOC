use std::fs;
use std::collections::HashSet;

fn remove_ws(s: &String) -> String {
    s.chars().filter(|c| !c.is_whitespace()).collect()
}

fn part_1(clean_contents : String) -> i32 {

    let instructions = clean_contents.split(',');
    let mut pos = (0_i32, 0_i32);

    let mut dir_index = 0;
    let dir_vectors = [(0, 1), (1,0), (0, -1), (-1, 0)];

    for instruction in instructions {
        let mut chars = instruction.chars();
        let direction = chars.next().unwrap();

        // Parse entire substring which is left in chars.
        let steps = chars.as_str().to_string().parse::<i32>().unwrap();

        assert!(direction == 'L' || direction == 'R');

        if direction == 'L' {
            dir_index = (dir_index + 3) % 4;
        }
        else {
            dir_index = (dir_index +1) % 4;
        }

        let (dx, dy) = dir_vectors[dir_index];

        pos.0 += steps * dx;
        pos.1 += steps * dy;
    }

    pos.0.abs() + pos.1.abs()
}


fn insert_and_check(set : &mut HashSet<(i32, i32)>, pos: (i32, i32)) -> bool {
    if set.contains(&(pos.0, pos.1)) {
        return true;
    }
    else {
        set.insert((pos.0, pos.1));
    }
    return false;
}


fn part_2(clean_contents : String) -> i32 {

    let instructions = clean_contents.split(',');
    let mut pos = (0_i32, 0_i32);

    let mut dir_index = 0;
    let dir_vectors = [(0, 1), (1,0), (0, -1), (-1, 0)];
    let mut positions = HashSet::new();

    for instruction in instructions {
        let mut chars = instruction.chars();
        let direction = chars.next().unwrap();

        // Parse entire substring which is left in chars.
        let steps = chars.as_str().to_string().parse::<i32>().unwrap();

        assert!(direction == 'L' || direction == 'R');

        if direction == 'L' {
            dir_index = (dir_index + 3) % 4;
        }
        else {
            dir_index = (dir_index +1) % 4;
        }

        let (dx, dy) = dir_vectors[dir_index];

        for _ in 0..steps {
            pos.0 += dx;
            pos.1 += dy;
            if insert_and_check(&mut positions, pos) {
                return pos.0.abs() + pos.1.abs();
            }
        }
    }

    pos.0.abs() + pos.1.abs()
}

fn main() {
    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let clean_contents = remove_ws(&contents);

    let ans_1 = part_1(clean_contents.clone());
    let ans_2 = part_2(clean_contents.clone());

    assert!(ans_1 == 181);
    assert!(ans_2 == 140);


    println!("part 1: {}", ans_1);
    println!("part 2: {}", ans_2);

}
