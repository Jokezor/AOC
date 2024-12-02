use std::fs;
use std::cmp::max;
use std::collections::{HashSet, HashMap};


fn part_1(s : &str) -> i32 {
    let mut rows = Vec::<Vec<i32>>::new();
    for row in s.split("\n") {
        let mut num_string = String::new();
        let mut row_nums = Vec::<i32>::new();

        for c in row.chars() {
            if !c.is_whitespace() {
                num_string.push(c);
            }
            else {
                if num_string.len() > 0 {
                    let num_int = num_string.parse::<i32>().unwrap();
                    row_nums.push(num_int);
                    num_string.clear();
                }
            }
        }
        if num_string.len() > 0 {
            let num_int = num_string.parse::<i32>().unwrap();
            row_nums.push(num_int);
            rows.push(row_nums);
        }
    }

    let mut ans : i32 = 0;
    for row in &rows {
        // Check if increasing.
        // Check if decreasing
        // Record max diff of elements.
        // If either both increasing and decreasing or max_diff > 4, then return 0.
        if is_good_report(row) {
            ans += 1;
        }
    }
    ans
}

fn is_good_report(row: &Vec<i32>) -> bool {
    let mut increasing = false;
    let mut decreasing = false;
    let mut max_diff = 0;

    for i in 0..row.len()-1 {
        let diff : i32 = row[i+1 as usize] - row[i as usize];
        if diff > 0 {
            increasing = true;
        }
        else if diff < 0 {
            decreasing = true;
        }
        else {
            decreasing = true;
            increasing = true;
        }
        max_diff = max(max_diff, diff.abs());
    }

    if (increasing && decreasing) || max_diff > 3 {
        false
    }
    else {
        true
    }
}


fn part_2(s : &str) -> i32 {
    let mut rows = Vec::<Vec<i32>>::new();
    for row in s.split("\n") {
        let mut num_string = String::new();
        let mut row_nums = Vec::<i32>::new();

        for c in row.chars() {
            if !c.is_whitespace() {
                num_string.push(c);
            }
            else {
                if num_string.len() > 0 {
                    let num_int = num_string.parse::<i32>().unwrap();
                    row_nums.push(num_int);
                    num_string.clear();
                }
            }
        }
        if num_string.len() > 0 {
            let num_int = num_string.parse::<i32>().unwrap();
            row_nums.push(num_int);
            rows.push(row_nums);
        }
    }

    let mut ans : i32 = 0;
    for row in &rows {
        // Check if increasing.
        // Check if decreasing
        // Record max diff of elements.
        // If either both increasing and decreasing or max_diff > 4, then return 0.

        // Can simply try by trying for each combination of skipping an entry in the row.
        // Then if any do match, then add and skip the row.
        if is_good_report(row) {
            ans += 1;
            continue;
        }
        // Now there was not a good initial, skip each level.

        for skipped in 0..row.len() {
            let mut new_row = Vec::<i32>::new();
            for i in 0..row.len() {
                if i != skipped {
                    new_row.push(row[i as usize]);
                }
            }
            if is_good_report(&new_row) {
                ans += 1;
                break;
            }
        }
    }
    ans
}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(&example_contents);

    println!("ex1: {}", ex_1);

    assert!(ex_1 == 2);

    let ex_2 = part_2(&example_contents);

    println!("ex2: {}", ex_2);

    assert!(ex_2 == 4);

    /////////////////////////

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("ans1: {}", ans_1);

    let ans_2 = part_2(&contents);
    println!("ans2: {}", ans_2);
}
