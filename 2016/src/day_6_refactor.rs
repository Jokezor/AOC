use std::fs;
use std::cmp::Ordering;

const ALPHABET_SIZE: usize = 26;

fn calculate_column_scores(input: &str) -> Vec<[u32; ALPHABET_SIZE]> {
    let mut column_score = vec![[0; ALPHABET_SIZE]; input.lines().next().unwrap().len()];

    for row in input.lines() {
        for (col, c) in row.chars().enumerate() {
            let index = (c as u8 - b'a') as usize;
            column_score[col][index] += 1;
        }
    }

    column_score
}

fn find_common_chars<F>(column_score: Vec<[u32; ALPHABET_SIZE]>, cmp_fn: F) -> String
where
    F: Fn(&u32, &u32) -> Ordering,
{
    column_score
        .into_iter()
        .map(|column| {
            column
                .iter()
                .enumerate()
                .filter(|&(_, &count)| count > 0) // Ignore zero counts
                .max_by(|&(_, a), &(_, b)| {
                    let order = cmp_fn(a, b);
                    if order == Ordering::Equal {
                        // Tie-breaker: choose the earlier letter
                        Ordering::Less
                    } else {
                        order
                    }
                })
                .unwrap()
                .0
        })
        .map(|index| (index as u8 + b'a') as char)
        .collect()
}

fn part_1(input: &str) -> String {
    let column_score = calculate_column_scores(input);
    find_common_chars(column_score, |a, b| a.cmp(b))
}

fn part_2(input: &str) -> String {
    let column_score = calculate_column_scores(input);
    find_common_chars(column_score, |a, b| a.cmp(b).reverse())
}

fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Failed to read src/example_input.txt. Ensure the file exists and is readable.");
    let contents = fs::read_to_string("src/input.txt")
        .expect("Failed to read src/input.txt. Ensure the file exists and is readable.");

    // Part 1
    let ex_1 = part_1(&example_contents);
    println!("Part 1 example: {}", ex_1);
    assert_eq!(ex_1, "easter");

    let ans_1 = part_1(&contents);
    println!("Part 1 answer: {}", ans_1);
    assert_eq!(ans_1, "xdkzukcf");

    // Part 2
    let ex_2 = part_2(&example_contents);
    println!("Part 2 example: {}", ex_2);
    assert_eq!(ex_2, "advent");

    let ans_2 = part_2(&contents);
    println!("Part 2 answer: {}", ans_2);
}

