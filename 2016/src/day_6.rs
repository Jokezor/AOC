use std::fs;
use std::cmp::max;


fn part_1(s: &str) -> String {
    let mut parts : Vec<&str> = s.lines().collect();
    
    // Map each column to 26 char vector
    let mut column_score : Vec<Vec<u32>> = Vec::new();

    let column_length = parts[0 as usize].len();

    for i in 0..column_length {
        column_score.push(vec![0_u32; 26]);
    }

    for row_str in parts.into_iter() {
        for (col, c) in row_str.chars().enumerate() {
            column_score[col as usize][(c as u8 - b'a') as usize] += 1;
        }
    }


    // Add back the most common chars in column to ans
    let mut ans = String::new();

    for column in column_score.into_iter() {
        let max_val = column.iter().max().unwrap();
        let max_index = column.iter().position(|element| element == max_val).unwrap();
        ans.push((max_index as u8 + b'a') as char);
    }

    ans
}


fn part_2(s: &str) -> String {
    let mut parts : Vec<&str> = s.lines().collect();
    
    // Map each column to 26 char vector
    let mut column_score : Vec<Vec<u32>> = Vec::new();

    let column_length = parts[0 as usize].len();

    for i in 0..column_length {
        column_score.push(vec![0_u32; 26]);
    }

    for row_str in parts.into_iter() {
        for (col, c) in row_str.chars().enumerate() {
            column_score[col as usize][(c as u8 - b'a') as usize] += 1;
        }
    }


    // Add back the most common chars in column to ans
    let mut ans = String::new();

    // Now its the least common non zero.
    for column in column_score.into_iter() {
        let mut min_val = 100000000;
        let mut min_index = 1000;

        // Take out the min, nonzero
        for i in 0..26 {
            let val = column[i as usize];

            if val <= min_val && val > 0 {
                min_val = val;
                min_index = i;
            }
        }
        ans.push((min_index as u8 + b'a') as char);
    }

    ans
}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    // First test with example
    let ex_1 = part_1(&example_contents);

    println!("part 1 ex: {}", ex_1);

    assert!(ex_1 == "easter");

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");
    let ans_1 = part_1(&contents);

    println!("{}", ans_1);

    assert!(ans_1 == "xdkzukcf");

    // Part 2:

    let ex_2 = part_2(&example_contents);

    println!("part 2 ex: {}", ex_2);

    assert!(ex_2 == "advent");

    let ans_2 = part_2(&contents);

    println!("{}", ans_2);
}
