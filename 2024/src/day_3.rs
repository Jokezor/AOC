use std::fs;
use std::cmp::max;
use std::collections::{HashSet, HashMap};
use regex::Regex;


fn part_1(s : &str) -> i32 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();
    re.captures_iter(s)
        .map(|cap| cap[1].parse::<i32>().unwrap() * cap[2].parse::<i32>().unwrap())
        .sum()
}


fn part_2(s : &str) -> i32 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();
    let re_do = Regex::new(r"do\(\)").unwrap();
    let re_dont = Regex::new(r"don't\(\)").unwrap();

    let dos = re_do.find_iter(s).map(|m| m.start()).collect::<Vec<_>>();
    let donts = re_dont.find_iter(s).map(|m| m.start()).collect::<Vec<_>>();

    re.captures_iter(s).map(|cap| {
        let match_start = cap.get(0).unwrap().start();

        // Find do and donts before match_start.
        let last_do = dos.iter()
            .rev()
            .find(|&&pos| pos <= match_start)
            .cloned()
            .unwrap_or(0);

        let last_dont = donts.iter()
            .rev()
            .find(|&&pos| pos <= match_start)
            .cloned()
            .unwrap_or(0);

        //println!("do: {}, dont: {}", do_before, dont_before);
        if last_dont > last_do {
            0
        }
        else {
            cap[1].parse::<i32>().unwrap() * cap[2].parse::<i32>().unwrap()
        }
    }).sum()
}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(&example_contents);

    println!("ex1: {}", ex_1);

    assert!(ex_1 == 161);

    let example_contents_2 = fs::read_to_string("src/example_input_2.txt")
        .expect("Should have read file.");

    let ex_2 = part_2(&example_contents_2);

    println!("ex2: {}", ex_2);

    assert!(ex_2 == 48);

    /////////////////////////

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("ans1: {}", ans_1);

    assert!(ans_1 == 189527826);

    let ans_2 = part_2(&contents);
    println!("ans2: {}", ans_2);

    assert!(ans_2 == 63013756);
}
