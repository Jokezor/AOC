use std::fs;
use std::cmp::max;



fn part_1(s: &str) -> u32 {
    let mut ips : Vec<&str> = s.lines().collect();


    let mut ans = 0;

    // Lets first do simple for loop, then do map.
    for ip in ips.iter() {
        let mut brackets = 0;
        let mut found = false;
        let mut abba : Vec<char> = Vec::new();

        for c in ip.chars() {
            if c == '[' {
                brackets += 1;
                abba.clear();
            }
            else if c == ']' {
                brackets -= 1;
                abba.clear();
            }
            else {
                // Add into abba at the end, pop beginning if more than 4.
                abba.push(c);

                if abba.len() > 4 {
                    abba.remove(0);
                }

                // Check if forming valid, if so set found = true.
                if abba.len() == 4 && (abba[0] == abba[3] && abba[1] == abba[2] && abba[0] != abba[1]) {
                    found = true;
                    if brackets > 0 {
                        break;
                    }
                }
            }
        }

        if found && brackets == 0 {
            println!("{}", ip);
            ans += 1;
        }
    }
    ans
}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    // First test with example
    let ex_1 = part_1(&example_contents);

    println!("part 1 ex: {}", ex_1);

    assert!(ex_1 == 2);

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("part 1: {}", ans_1);
}
