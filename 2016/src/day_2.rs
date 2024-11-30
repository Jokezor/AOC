use std::fs;

fn remove_ws(s: &String) -> String {
    s.chars().filter(|c| !c.is_whitespace()).collect()
}

fn part_1(contents : String) -> String {

    let clean_contents = contents.lines();

    let key_pad = [["1", "2", "3"], ["4", "5", "6"], ["7", "8", "9"]];
    let mut ans : String = "".to_string();

    let mut pos = (1_i32, 1_i32);

    for content in clean_contents {
        for c in content.chars() {
            pos = match c {
                'L' => (pos.0, pos.1-1),
                'R' => (pos.0, pos.1+1),
                'U' => (pos.0-1, pos.1),
                'D' => (pos.0+1, pos.1),
                _ => panic!("Unexpected char! {}", c),
            };
            pos = (pos.0.clamp(0, 2), pos.1.clamp(0, 2));
        }
        ans += &key_pad[pos.0 as usize][pos.1 as usize];
    }

    ans
}


fn part_2(contents : String) -> String {

    let clean_contents = contents.lines();

    let key_pad = [["X", "X", "1", "X", "X"], ["X", "2", "3", "4", "X"], ["5", "6", "7", "8", "9"], ["X", "A", "B", "C", "X"], ["X", "X", "D", "X", "X"]];
    let mut ans : String = "".to_string();

    let mut pos = (2_i32, 0_i32);

    for content in clean_contents {
        for c in content.chars() {
            let mut new_pos = match c {
                'L' => (pos.0, pos.1-1),
                'R' => (pos.0, pos.1+1),
                'U' => (pos.0-1, pos.1),
                'D' => (pos.0+1, pos.1),
                _ => panic!("Unexpected char! {}", c),
            };
            new_pos = (new_pos.0.clamp(0, 4), new_pos.1.clamp(0, 4));

            if key_pad[new_pos.0 as usize][new_pos.1 as usize] != "X" {
                pos = new_pos;
            }
        }
        ans += &key_pad[pos.0 as usize][pos.1 as usize];
    }

    ans
}


fn main() {
    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    //let clean_contents = remove_ws(&contents);
    let ans_1 = part_1(contents.clone());

    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_2 = part_2(example_contents.clone());
    let ans_2 = part_2(contents.clone());

    assert!(ans_1 == "36629");
    assert!(ex_2 == "5DB3");

    println!("part 1: {}", ans_1);
    println!("part 2: {}", ans_2);

}
