use std::fs;
use std::char;
use md5;
use std::fmt::format;


fn is_ok(s : &&[u8]) -> bool {
    s[0] == b'0' && s[1] == b'0' && s[2] == b'0' && s[3] == b'0' && s[4] == b'0'
}

fn part_1(door_id: &str) -> String {
    let mut ans = String::new();
    let mut index = 0;

    for _ in 0..8 {
        let mut not_ok = true;

        // Compute digest and increment index until 5 0s.
        while not_ok {
            index += 1;
            let key = door_id.to_owned() + &index.to_string();
            let digest = format!("{:x}", md5::compute(&key));
            let digest = digest.as_bytes();

            assert!(digest.len() == 32);

            if is_ok(&digest) {
                ans.push(digest[5] as char);
                not_ok = false;
            }
            if index % 100000 == 0 {
                println!("{}", index);
            }
        }
    }

    ans
}


fn part_2(door_id: &str) -> String {
    // Now I need to add 
    let mut ans = String::new();
    let mut index = 0;

    let mut ans_vec : Vec<char> = vec!['-'; 8];

    for _ in 0..8 {
        let mut not_ok = true;

        // Compute digest and increment index until 5 0s.
        while not_ok {
            index += 1;
            let key = door_id.to_owned() + &index.to_string();
            let digest = format!("{:x}", md5::compute(&key));
            let digest = digest.as_bytes();

            assert!(digest.len() == 32);

            if is_ok(&digest) {
                let pos = digest[5] - b'0' as u8;

                println!("{}", pos);

                if pos >= 0 && pos < 8 && ans_vec[pos as usize] == '-' {
                    ans_vec[pos as usize] = digest[6] as char;
                    not_ok = false;
                }
            }
            if index % 100000 == 0 {
                println!("{}", index);
            }
        }
    }

    for i in 0..8 {
        ans.push(ans_vec[i as usize]);
    }

    ans

}

fn main() {
    // First test with example
    let ex_1 = part_1("abc");

    println!("part 1 ex: {}", ex_1);

    assert!(ex_1 == "18f47a30");

    let ans_1 = part_1("abbhdwsy");

    println!("{}", ans_1);

    let ex_2 = part_2("abc");

    println!("part 2 ex: {}", ex_2);

    assert!(ex_2 == "05ace8e3");

    let ans_2 = part_2("abbhdwsy");

    println!("{}", ans_2); // 424a0197
}
