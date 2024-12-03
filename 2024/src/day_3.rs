use std::fs;
use std::cmp::max;
use std::collections::{HashSet, HashMap};
use regex::Regex;


fn part_1(s : &str) -> i32 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();

    let mut ans : i32 = 0;
    let ans = re.captures_iter(s).map(|cap| {
        let x = cap.get(1).unwrap().as_str();
        let y = cap.get(2).unwrap().as_str();

        let x_num = x.parse::<i32>().unwrap();
        let y_num = y.parse::<i32>().unwrap();
        x_num * y_num
    }).sum();

    ans
}


fn part_2(s : &str) -> i32 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();
    let re_dos = Regex::new(r"do\(\)").unwrap();
    let re_donts = Regex::new(r"don't\(\)").unwrap();

    let dos : Vec<(usize, usize)> = re_dos.captures_iter(s).map(|cap| {
        let whole_match = cap.get(0).unwrap();
        let match_start = whole_match.start();
        let match_end = whole_match.end();
        (match_start, match_end)
    }).collect();

    let donts : Vec<(usize, usize)> = re_donts.captures_iter(s).map(|cap| {
        let whole_match = cap.get(0).unwrap();
        let match_start = whole_match.start();
        let match_end = whole_match.end();
        (match_start, match_end)
    }).collect();

    let mut ans : i32 = 0;
    let ans = re.captures_iter(s).map(|cap| {
        let whole_match = cap.get(0).unwrap();

        let match_start = whole_match.start();
        let match_end = whole_match.end();

        // println!("start: {}, end: {}", match_start, match_end);

        // Find do and donts before match_start.
        let mut do_before = 0;
        for do_ind in &dos {
            if do_ind.0 > match_start {
                break;
            }
            do_before = do_ind.0;
        }

        let mut dont_before = 0;
        for dont_ind in &donts {
            if dont_ind.0 > match_start {
                break;
            }
            dont_before = dont_ind.0;
        }

        //println!("do: {}, dont: {}", do_before, dont_before);
        if dont_before > do_before {
            0
        }
        else {
            let x = cap.get(1).unwrap().as_str();
            let y = cap.get(2).unwrap().as_str();

            let x_num = x.parse::<i32>().unwrap();
            let y_num = y.parse::<i32>().unwrap();
            x_num * y_num
        }
    }).sum();

    ans
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
