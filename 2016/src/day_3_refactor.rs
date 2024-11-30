use std::fs;

fn remove_ws(s: &String) -> String {
    s.chars().filter(|c| !c.is_whitespace()).collect()
}

fn is_triangle(a : i32, b : i32, c : i32) -> bool {
    a + b > c && a + c > b && c + b > a
}

fn part_1(contents : String) -> i32 {
    contents
        .lines()
        .map(|line| {
            let sides: Vec<i32> = line
                .split_whitespace()
                .map(|s| s.parse::<i32>().unwrap())
                .collect();
            if sides.len() >= 3 && is_triangle(sides[0], sides[1], sides[2]) {
                1
            }
            else {
                0
            }
        })
        .sum()
}


fn part_2(contents: String) -> i32 {
    contents
        .lines()
        .map(|line| {
            line.split_whitespace()
                .map(|s| s.parse::<i32>().unwrap())
                .collect::<Vec<i32>>()
        })
        .collect::<Vec<Vec<i32>>>()
        .chunks(3)
        .map(|chunk| {
            if chunk.len() < 3 {
                0
            } else {
                (0..3)
                    .filter(|&col| is_triangle(chunk[0][col], chunk[1][col], chunk[2][col]))
                    .count() as i32
            }
        })
        .sum()
}


fn main() {
    // First test with example
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(example_contents.clone());
    println!("part 1 ex: {}", ex_1);

    assert!(ex_1 == 2);

    // Now run with input
    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(contents.clone());
    println!("part 1: {}", ans_1);

    // Part 2
    let example_contents_2 = fs::read_to_string("src/example_input_2.txt")
        .expect("Should have read file.");

    let ex_2 = part_2(example_contents_2.clone());

    println!("part 2 ex: {}", ex_2);
    assert!(ex_2 == 6);

    let ans_2 = part_2(contents.clone());
    println!("part 2: {}", ans_2);

}
