use md5;
use rayon::prelude::*;


fn is_valid_hash(digest: &[u8; 16]) -> bool {
    digest[0] == 0 && digest[1] == 0 && digest[2] & 0xF0 == 0
}

fn get_hex_char(nibble: u8) -> char {
    match nibble {
        0..=9 => (b'0' + nibble) as char,
        10..=15 => (b'a' + (nibble - 10)) as char,
        _ => panic!("Invalid nibble"),
    }
}


fn write_index(buffer: &mut Vec<u8>, mut index: u64) {

    if index == 0 {
        buffer.push(b'0');
    }
    else {
        let mut digits = [0u8; 20];
        let mut i = 0;

        while index > 0 {
            digits[i] = (index % 10) as u8;
            index /= 10;
            i += 1;
        }

        for &digit in digits[..i].iter().rev() {
            buffer.push(b'0' + digit);
        }
    }
}

fn part_1(door_id: &str) -> String {
    let mut password = String::with_capacity(8);
    let mut index = 0_u64;

    let door_id_bytes = door_id.as_bytes();
    let mut buffer = Vec::with_capacity(door_id_bytes.len() + 20);
    buffer.extend_from_slice(door_id_bytes);

    while password.len() < 8 {
        buffer.truncate(door_id_bytes.len());
        write_index(&mut buffer, index);

        let digest = md5::compute(&buffer);

        if is_valid_hash(&digest) {
            let sixth_nibble = digest[2] & 0x0F;
            password.push(get_hex_char(sixth_nibble));
        }

        index += 1;
    }

    password
}

fn part_2(door_id: &str) -> String {
    let mut password = vec!['-'; 8];
    let mut index = 0u64;
    let door_id_bytes = door_id.as_bytes();
    let mut buffer = Vec::with_capacity(door_id_bytes.len() + 20);
    buffer.extend_from_slice(door_id_bytes);
    let mut filled_positions = 0;

    while filled_positions < 8 {
        buffer.truncate(door_id_bytes.len());
        write_index(&mut buffer, index);

        let digest = md5::compute(&buffer);

        if is_valid_hash(&digest) {
            let position = (digest[2] & 0x0F) as usize; // Bits 20-23

            if position < 8 && password[position] == '-' {
                let seventh_nibble = (digest[3] & 0xF0) >> 4; // Bits 24-27
                password[position] = get_hex_char(seventh_nibble);
                filled_positions += 1;
            }
        }

        index += 1;
    }

    password.into_iter().collect()
}



// Example for Part 2
fn part_2_parallel(door_id: &str) -> String {
    use std::sync::{Arc, Mutex};
    let password = Arc::new(Mutex::new(vec!['-'; 8]));
    let door_id = door_id.to_string();
    let mut index = 0u64;

    while password.lock().unwrap().contains(&'-') {
        let door_id_clone = door_id.clone();
        let password_clone = Arc::clone(&password);

        (index..index + 10000).into_par_iter().for_each(|i| {
            let mut buffer = Vec::with_capacity(door_id_clone.len() + 20);
            buffer.extend_from_slice(door_id_clone.as_bytes());
            write_index(&mut buffer, i);

            let digest = md5::compute(&buffer);

            if is_valid_hash(&digest) {
                let position = (digest[2] & 0x0F) as usize;

                if position < 8 {
                    let mut pwd = password_clone.lock().unwrap();
                    if pwd[position] == '-' {
                        let seventh_nibble = (digest[3] & 0xF0) >> 4;
                        pwd[position] = get_hex_char(seventh_nibble);
                    }
                }
            }
        });

        index += 10000;
    }

    Arc::try_unwrap(password).unwrap().into_inner().unwrap().into_iter().collect()
}


fn main() {
    // First test with example
    //let ex_1 = part_1("abc");
    //
    //println!("part 1 ex: {}", ex_1);
    //
    //assert!(ex_1 == "18f47a30");
    //
    //let ans_1 = part_1("abbhdwsy");
    //
    //println!("{}", ans_1);
    //
    let ex_2 = part_2_parallel("abc");

    println!("part 2 ex: {}", ex_2);

    assert!(ex_2 == "05ace8e3");

    let ans_2 = part_2_parallel("abbhdwsy");

    println!("{}", ans_2); // 424a0197
}
