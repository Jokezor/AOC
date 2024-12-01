use std::fs;
use std::collections::{HashSet, HashMap};

fn part_1(s : &str) -> i32 {
    let mut left : Vec<i32> = Vec::new();
    let mut right : Vec<i32> = Vec::new();
    for row in s.split("\n") {
        let mut num_string = String::new();
        for c in row.chars() {
            if !c.is_whitespace() {
                num_string.push(c);
            }
            else {
                if num_string.len() > 0 {
                    let index_int = num_string.parse::<i32>().unwrap();
                    left.push(index_int);
                    num_string.clear();
                }
            }
        }
        if num_string.len() > 0 {
            let index_int = num_string.parse::<i32>().unwrap();
            right.push(index_int);
        }
    }

    // Now sort and compare each one by one.
    left.sort();
    right.sort();

    let mut ans : i32 = 0;

    for i in 0..left.len() {
        let diff = (left[i as usize] - right[i as usize]);
        ans += diff.abs();
    }

    ans
}


fn part_2(s : &str) -> i32 {
    let mut left : Vec<i32> = Vec::new();
    let mut right : Vec<i32> = Vec::new();
    for row in s.split("\n") {
        let mut num_string = String::new();
        for c in row.chars() {
            if !c.is_whitespace() {
                num_string.push(c);
            }
            else {
                if num_string.len() > 0 {
                    let index_int = num_string.parse::<i32>().unwrap();
                    left.push(index_int);
                    num_string.clear();
                }
            }
        }
        if num_string.len() > 0 {
            let index_int = num_string.parse::<i32>().unwrap();
            right.push(index_int);
        }
    }

    let mut counter = HashMap::<i32, i32>::new();

    for num in &right {
        counter.entry(*num).and_modify(|count| *count += 1).or_insert(1);
    }

    let mut ans : i32 = 0;
    // Check occurance score for each entry
    for num in &left {
        ans += match counter.get(num) {
            Some(count) => count * num,
            None => 0
        };
    }

    ans
}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(&example_contents);

    println!("ex1: {}", ex_1);

    assert!(ex_1 == 11);

    let ex_2 = part_2(&example_contents);

    println!("ex2: {}", ex_2);

    assert!(ex_2 == 31);

    /////////////////////////

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("ans1: {}", ans_1);

    let ans_2 = part_2(&contents);
    println!("ans2: {}", ans_2);

}
