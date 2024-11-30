use std::fs;
use std::char;

fn remove_ws(s: &String) -> String {
    s.chars().filter(|c| !c.is_whitespace()).collect()
}

fn is_real_room(computed_checksum : &String, checksum : &String) -> bool {
    computed_checksum == checksum
}


fn create_checksum(counter: Vec<(i32, usize)>) -> String {
    let mut counter = counter;
    counter.sort_by(|a, b| {
        b.0.cmp(&a.0).then_with(|| a.1.cmp(&b.1))
    });
    counter.iter()
        .take(5)
        .map(|&(_, index)| (index as u8 + b'a') as char)
        .collect()
}


fn decrypt_name(names: &[String], sector_id: i32) -> String {
    let shift = (sector_id % 26) as u8;
    names.iter()
        .filter(|name| name != &&sector_id.to_string())
        .map(|name| {
            name.chars()
                .map(|c| {
                    if c == '-' {
                        ' '
                    } else {
                        let shifted = ((c as u8 - b'a' + shift) % 26) + b'a';
                        shifted as char
                    }
                })
                .collect::<String>()
        })
        .collect::<Vec<_>>()
        .join(" ")
}


fn part_1(contents : &str) -> i32 {
    contents
        .lines()
        .map(|line| {
            let first = line.split('[').next().unwrap();
            let checksum = line.split('[').last().unwrap().split(']').next().unwrap().to_string();
            let sector_id = first.split('-').last().unwrap();

            let rest = first.split('-');

            // index 2nd
            let mut counter = vec![(0, 0); 26];

            for i in 0..26 {
                counter[i as usize].1 = i;
            }

            // Instead take all if not int?
            for name in rest {
                if name != sector_id {
                    for c in name.chars() {
                        let index = (c as u8 - 'a' as u8) as usize;
                        counter[index] = (counter[index].0 + 1, counter[index].1);
                    }
                }
            }
            // Construct checksum from counter
            let computed_checksum = create_checksum(counter);

            if is_real_room(&computed_checksum, &checksum) {
                sector_id.parse::<i32>().unwrap()
            }
            else {
                0
            }
        })
        .sum()
}

fn part_2(contents : &str) -> i32 {
    contents
        .lines()
        .map(|line| {
            let first = line.split('[').next().unwrap();
            let checksum = line.split('[').last().unwrap().split(']').next().unwrap().to_string();
            let sector_id = first.split('-').last().unwrap();

            let rest : Vec<String> = first.split('-').map(str::to_string).collect();

            // index 2nd
            let mut counter = vec![(0, 0); 26];

            for i in 0..26 {
                counter[i as usize].1 = i;
            }

            // Instead take all if not int?
            for name in &rest {
                if name != sector_id {
                    for c in name.chars() {
                        let index = (c as u8 - 'a' as u8) as usize;
                        counter[index] = (counter[index].0 + 1, counter[index].1);
                    }
                }
            }
            let computed_checksum = create_checksum(counter);

            println!("{}", computed_checksum);


            if is_real_room(&computed_checksum, &checksum) {
                // Now decrypt the room name
                let sector_id = sector_id.parse::<i32>().unwrap();
                let decrypted_name = decrypt_name(&rest, sector_id);
                println!("{}, {}", decrypted_name, sector_id);
                sector_id
            }
            else {
                0
            }
        })
        .sum()
}


fn main() {
    // First test with example
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(&example_contents);
    let ex_2 = part_2(&example_contents);

    //assert!(ex_1 == 1514);
    println!("part 2 ex: {}", ex_2);

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);
    println!("part 1: {}", ans_1);

    assert!(ans_1 == 158835);

    let ans_2 = part_2(&contents);
    println!("part 1: {}", ans_2);

}
