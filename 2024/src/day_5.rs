use std::fs;
use std::cmp::max;
use std::collections::{HashSet, HashMap};
use regex::Regex;


fn get_orderings(s : &str) -> HashMap<i32, HashSet<i32>> {
    let re = Regex::new(r"(\d+)\|(\d+)").unwrap();
    let mut orderings : HashMap<i32, HashSet<i32>> = HashMap::new();
    for rule in re.captures_iter(s) {
        let key = rule[1].parse::<i32>().unwrap();
        let val = rule[2].parse::<i32>().unwrap();
        if orderings.contains_key(&key) {
            orderings.entry(key).and_modify(|values| { values.insert(val); });
        }
        else {
            let mut new_set : HashSet<i32> = HashSet::new();
            new_set.insert(val);
            orderings.insert(key, new_set);
        }
    }
    orderings
}


fn get_updates(s : &str) -> Vec<Vec<i32>> {
    let re = Regex::new(r"(.*,.*)").unwrap();
    let re_digit = Regex::new(r"\d+").unwrap();

    let mut updates : Vec<Vec<i32>> = Vec::new();
    for capt in re.captures_iter(s) {
        let mut update_vec : Vec<i32> = Vec::new();
        let update = capt[0].parse::<String>().unwrap();
        for num in re_digit.captures_iter(&update) {
            let update_num = num[0].parse::<i32>().unwrap();
            update_vec.push(update_num);
        }
        updates.push(update_vec);
    }

    updates
}


fn is_correct_update(update : &Vec<i32>, orderings : &HashMap<i32, HashSet<i32>>) -> bool {

    // Check for each update_num if any prior to it is in its set.
    for (ind, update_num) in update.iter().enumerate() {
        let prior_nums = match orderings.get(update_num) {
            Some(set) => set,
            _ => &HashSet::<i32>::new(),
        };
        for i in 0..ind+1 {
            let prior_update = update[i as usize];
            if prior_update == *update_num {
                continue;
            }
            if prior_nums.contains(&prior_update) {
                return false;
            }
        }
    }

    true
}

fn part_1(s : &str) -> i32 {
    // Build the ordering rules
    // Get the correct updates (Follows ordering rules)
    // Get the middle page number of correct updates.
    let orderings = get_orderings(&s);
    let updates = get_updates(s);

    let correct_updates : Vec<Vec<i32>> = updates.iter().cloned().filter(|update| is_correct_update(&update, &orderings)).collect();

    let ans = correct_updates.iter().map(|update| update[update.len()/2 as usize]).sum();

    println!("{}", correct_updates.len());

    // Coolest would be to get some sort of tree.
    // But simple could be to have a hashmap of each updates requirement for it to be before.
    // {47: {53, 13, 29}, 97: {13, 61, 47, 29, 53, 75}

    // Then simply check for each position, is there any of these items
    // earlier than itself? If so, not valid.
    // O(N^2).

    ans

}

fn fix_incorrect_update(update : &Vec<i32>, orderings : &HashMap<i32, HashSet<i32>>) -> Vec<i32> {

    // Check for each update_num if any prior to it is in its set.
    let mut correct_update : Vec<i32> = update.clone();

    let mut ind = 0;
    while ind < correct_update.len() {
        let update_num = correct_update[ind as usize];
        let prior_nums = match orderings.get(&update_num) {
            Some(set) => set,
            _ => &HashSet::<i32>::new(),
        };
        for i in 0..ind+1 {
            let prior_update = correct_update[i as usize];
            if prior_update == update_num {
                continue;
            }
            if prior_nums.contains(&prior_update) {
                // Here we should fix the wrong thing.
                correct_update.swap(ind, i);

                // restart since it was wrong.
                // This is obviously not optimal?
                // Or is it?
                //
                ind = 0;
                break;
            }
        }
        ind += 1;
    }

    correct_update
}

fn part_2(s : &str) -> i32 {
    let orderings = get_orderings(&s);
    let updates = get_updates(s);

    let incorrect_updates : Vec<Vec<i32>> = updates.iter().cloned().filter(|update| !is_correct_update(&update, &orderings)).collect();

    println!("{}", incorrect_updates.len());

    // Now to fix these incorrect updates.
    let mut corrected_updates : Vec<Vec<i32>> = incorrect_updates.
        iter()
        .map(|update| {
            fix_incorrect_update(update, &orderings)
        })
        .collect();
    
    let ans = corrected_updates.iter().map(|update| update[update.len()/2 as usize]).sum();


    ans

}


fn main() {
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(&example_contents);

    println!("ex1: {}", ex_1);

    assert!(ex_1 == 143);

    let ex_2 = part_2(&example_contents);

    println!("ex2: {}", ex_2);
    assert!(ex_2 == 123);

    /////////////////////////

    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(&contents);

    println!("ans1: {}", ans_1);
    assert!(ans_1 == 5087);

    let ans_2 = part_2(&contents);

    println!("ans2: {}", ans_2);

}
