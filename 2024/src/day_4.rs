use std::fs;
use std::cmp::max;
use std::collections::{HashSet, HashMap};
use regex::Regex;


fn is_xmas(candidate: &[char]) -> bool {
    if candidate[0] == 'X' && candidate[1] == 'M' && candidate[2] == 'A' && candidate[3] == 'S' {
        return true;
    }
    //let rev_candidate : Vec<&char> = candidate.iter().rev().collect();
    //if *rev_candidate[0] == 'X' && *rev_candidate[1] == 'M' && *rev_candidate[2] == 'A' && *rev_candidate[3] == 'S' {
    //    return true;
   // }
    return false;
}

fn part_1(s : &str) -> i32 {
    // Add each 8 directions starting at the index

    // Convert string to vector of strings.
    let mut words : Vec<Vec<char>> = s.split_whitespace().map(|word| word.chars().collect()).collect();

    // Now we can index word and get the row.
    let m : usize = words.len();
    let n : usize = words[0 as usize].len();

    let mut ans = 0;
    // Instead convert to vector of vector of chars.
    for i in 0..m {
        for j in 0..n {
            // Now to check 3 chars extra in each direction.

            // Right
            {
                if j < n-3 {
                    let candidate = &words[i][j..j+4];
                    if candidate.len() == 4 && is_xmas(candidate) {
                        ans += 1;
                    }
                }
            }
            // Left
            {
                if j > 2 {
                    let candidate = &words[i][j-3..j+1];
                    if candidate.len() == 4 && is_xmas(candidate) {
                        ans += 1;
                    }
                }
            }
            // down
            {
                if i < m - 3 {
                    let candidate : Vec<char> = words[i..i+4].iter().map(|row| row[j]).collect();
                    if candidate.len() == 4 && is_xmas(&candidate) {
                        ans += 1;
                    }
                }
            }
            // up
            {
                if i > 2 {
                    let candidate : Vec<char> = words[i-3..i+1].iter().rev().map(|row| row[j]).collect();
                    if candidate.len() == 4 && is_xmas(&candidate) {
                        ans += 1;
                    }
                }
            }
            // Right up diagonally.
            {
                if i > 2 && j < n - 3 {
                    let sliced_words : Vec<&Vec<char>> = words[i-3..i+1].iter().rev().collect();
                    let mut candidate : Vec<char> = Vec::new();

                    let mut word_ind = 0;
                    for k in j..j+4 {
                        candidate.push(sliced_words[word_ind as usize][k as usize]);
                        word_ind += 1;
                    }

                    if candidate.len() == 4 && is_xmas(&candidate) {
                        ans += 1;
                    }
                }
            }

            // Left up diagonally.
            {
                if i > 2 && j > 3 {
                    let sliced_words : Vec<&Vec<char>> = words[i-3..i+1].iter().rev().collect();
                    let mut candidate : Vec<char> = Vec::new();

                    let mut word_ind = 0;
                    for k in (j-3..j+1).rev() {
                        candidate.push(sliced_words[word_ind as usize][k as usize]);
                        word_ind += 1;
                    }

                    if candidate.len() == 4 && is_xmas(&candidate) {
                        ans += 1;
                        println!("WOT");
                    }
                }
            }

            // Left down diagonally
            {
                if i < m-3 && j > 2 {
                    let sliced_words : Vec<&Vec<char>> = words[i..i+4].iter().collect();
                    let mut candidate : Vec<char> = Vec::new();

                    let mut word_ind = 0;
                    for k in (j-3..j+1).rev() {
                        candidate.push(sliced_words[word_ind as usize][k as usize]);
                        word_ind += 1;
                    }

                    if candidate.len() == 4 && is_xmas(&candidate) {
                        //println!("WOT");
                        ans += 1;
                    }
                }
            }

            // Right down diagonally
            {
                if i < m-3 && j < n-3 {
                    let sliced_words : Vec<&Vec<char>> = words[i..i+4].iter().collect();
                    let mut candidate : Vec<char> = Vec::new();

                    let mut word_ind = 0;
                    for k in j..j+4 {
                        candidate.push(sliced_words[word_ind as usize][k as usize]);
                        word_ind += 1;
                    }

                    if candidate.len() == 4 {
                        if is_xmas(&candidate) {
                            //println!("WOT");
                            ans += 1;
                        }
                    }
                }
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

    // 5 horizontal + 1 down + 2 up + 4 right up diagonal + 4 left up diagonal + 1 left down
    //   diagonal + 1 right down diagonal
    assert!(ex_1 == 18);

    //let ex_2 = part_2(&example_contents);

    //println!("ex2: {}", ex_2);

    //assert!(ex_2 == 48);

    /////////////////////////

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("ans1: {}", ans_1);

    //assert!(ans_1 == 189527826);

    //let ans_2 = part_2(&contents);
    //println!("ans2: {}", ans_2);

    //assert!(ans_2 == 63013756);
}
